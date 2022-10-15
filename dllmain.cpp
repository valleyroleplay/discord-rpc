#include <process.h>
#include "client.h"
#include "discord.h"
#include "payload.h"
#include "http.h"

static void process(void*)
{
	WSADATA wsa;

	wchar_t* input = GetCommandLine();

	WSAStartup(MAKEWORD(2, 2), &wsa);

	Discord::initialize();

	std::string ip = ServerConnection::getIp("https://gkwiki.vercel.app/api/ip");

	ServerConnection::ServerData data;
	if (ServerConnection::readServerData(input, data)) {
		auto start = std::time(0);
		if (data.connect == ServerConnection::SAMP_CONNECT_SERVER && data.address == ip) {
			ServerConnection::Payload payload(data.address, std::stoi(data.port));
			while (true) {
				ServerConnection::Payload::Information information;
				if (payload.info(information)) {
					
					auto state = "";
					auto players = std::to_string(information.basic.players) + "/" + std::to_string(information.basic.maxPlayers) + " players online";
					auto info = "["+ information.language+"]"+" " + information.gamemode + " as " + data.username + " in ";
					auto image = "valleyrp";
					auto infoImage = "valleyrp";

					Discord::update(start, state, information.hostname, image, info, infoImage, players);

					Sleep(15000 - QUERY_DEFAULT_TIMEOUT * 2);
				}
			}
		
		}
	}

}

BOOL APIENTRY DllMain(HMODULE module, DWORD reason, LPVOID reserved)
{
	switch (reason)
	{
		case DLL_PROCESS_ATTACH: {
			DisableThreadLibraryCalls(module);
			_beginthread(&process, 0, nullptr);
			break;
		}
		case DLL_PROCESS_DETACH: {
			WSACleanup();
			break;
		}
	}
	return TRUE;
}