#pragma once
#include "UDPSocket.h"
#include "TCPSocket.h"
enum SocketAddressFamily {
	INET = AF_INET,
	INET6 = AF_INET6
};
class SocketUtil {
public:
	UDPSocketPtr CreateUDPSocket(SocketAddressFamily inFamily);
	TCPSocketPtr CreateTCPSocket(SocketAddressFamily inFamily);
	static int GetLastError();
	static void ReportError(const wchar_t* err);
};

