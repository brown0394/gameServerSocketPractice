#pragma once
#include "UDPSocket.h"
#include "TCPSocket.h"
#include <vector>

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
	fd_set* FillSetFromVector(fd_set& outSet, const std::vector<TCPSocketPtr>* inSockets);
	void FillVectorFromSet(std::vector<TCPSocketPtr>* outSockets, const std::vector<TCPSocketPtr>*
		inSockets, const fd_set& inSet);
	int Select(const std::vector<TCPSocketPtr>* inReadSet, std::vector<TCPSocketPtr>* outReadSet,
		const std::vector<TCPSocketPtr>* inWriteSet, std::vector<TCPSocketPtr>* outWriteSet,
		const std::vector<TCPSocketPtr>* inExceptSet, std::vector<TCPSocketPtr>* outExceptSet);
};

