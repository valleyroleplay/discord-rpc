#pragma once

#include <string>

namespace ServerConnection {
	enum EConnectMode {
		SAMP_CONNECT_UNKNOWN,
		SAMP_CONNECT_SERVER,
		SAMP_CONNECT_DEBUG
	};
	struct ServerData {
		EConnectMode connect = SAMP_CONNECT_UNKNOWN;
		std::string address;
		std::string port;
		std::string username;
	};
	//const wchar_t* cmdline, 
	bool readServerData(wchar_t* cmdLine, ServerData& data);
}