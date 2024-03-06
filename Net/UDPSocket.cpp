#include "UDPSocket.h"
#include "SocketUtil.h"

int UDPSocket::SendTo(const void* inData, int inLen, const SocketAddress& inTo) {
	int byteSentCount = sendto(mSocket, static_cast<const char*>(inData),
		inLen, 0, &inTo.mSockAddr, inTo.GetSize());
	if (byteSentCount >= 0) {
		return byteSentCount;
	}
	else {
		//return error as negative number 
		SocketUtil::ReportError(L"UDPSocket::SendTo");
		return -SocketUtil::GetLastError();
	}
}
int UDPSocket::ReceiveFrom(void* inBuffer, int inLen, SocketAddress& outFromAddress) {
	int fromLength = outFromAddress.GetSize();
	int readByteCount = recvfrom(mSocket,
		static_cast<char*>(inBuffer),
		inLen,
		0, &outFromAddress.mSockAddr,
		&fromLength);
	if (readByteCount >= 0) {
		return readByteCount;
	}
	else {
		SocketUtil::ReportError(L"UDPSocket::ReceiveFrom");
		return -SocketUtil::GetLastError();
	}
}
UDPSocket::~UDPSocket() {
	closesocket(mSocket);
}

int UDPSocket::Bind(const SocketAddress& inBindAddress) {
	int err = bind(mSocket, &inBindAddress.mSockAddr,
		inBindAddress.GetSize());
	if (err != 0)
	{
		SocketUtil::ReportError(L"UDPSocket::Bind");
		return SocketUtil::GetLastError();
	}
	return NO_ERROR;
}