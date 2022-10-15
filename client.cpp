#include "client.h"
#include <memory>

namespace ServerConnection {
	bool readServerData(wchar_t* cmdLine, ServerData& data)
	{
		auto input = std::unique_ptr<wchar_t>(_wcsdup(cmdLine));
		wchar_t* next = nullptr;
		wchar_t* token = wcstok_s(input.get(), L" ", &next);
		while (token != nullptr) {
			if (!std::wcscmp(token, L"-c")) {
				if (data.connect != SAMP_CONNECT_UNKNOWN) {
					return false;
				}
				data.connect = SAMP_CONNECT_SERVER;
			}
			else if (!std::wcscmp(token, L"-h")) {
				if (!next) {
					return false;
				}
				std::wstring ws(wcstok_s(nullptr, L" ", &next));
				std::string address(ws.begin(), ws.end());
				data.address = address;
			}
			else if (!std::wcscmp(token, L"-p")) {
				if (!next) {
					return false;
				}
				std::wstring ws(wcstok_s(nullptr, L" ", &next));
				std::string port(ws.begin(), ws.end());
				data.port = port;
			}
			else if (!std::wcscmp(token, L"-n")) {
				if (!next) {
					return false;
				}
				std::wstring ws(wcstok_s(nullptr, L" ", &next));
				std::string username(ws.begin(), ws.end());
				data.username = username;
			}
			token = wcstok_s(nullptr, L" ", &next);
		}
		return true;
	}
}