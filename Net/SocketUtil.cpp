#include "SocketUtil.h"

UDPSocketPtr SocketUtil::CreateUDPSocket(SocketAddressFamily inFamily) {
	SOCKET s = socket(inFamily, SOCK_DGRAM, IPPROTO_UDP);
	if (s != INVALID_SOCKET) {
		return UDPSocketPtr(new UDPSocket(s));
	}
	else {
		ReportError(L"SocketUtil::CreateUDPSocket");
		return nullptr;
	}
}

TCPSocketPtr SocketUtil::CreateTCPSocket(SocketAddressFamily inFamily) {
	SOCKET s = socket(inFamily, SOCK_STREAM, IPPROTO_TCP);
	if (s != INVALID_SOCKET) {
		return TCPSocketPtr(new TCPSocket(s));
	}
	else {
		ReportError(L"SocketUtil::CreateTCPSocket");
		return nullptr;
	}
}

int SocketUtil::GetLastError() {
	return WSAGetLastError();
}

void SocketUtil::ReportError(const wchar_t* err) {
	printf("%ls\n", err);
}