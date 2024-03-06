#include "SocketAddress.h"
#include <Ws2tcpip.h>

SocketAddress::SocketAddress(uint32_t inAddress, uint16_t inPort) {
	GetAsSockAddrIn()->sin_family = AF_INET;
	GetAsSockAddrIn()->sin_addr.S_un.S_addr = htonl(inAddress);
	GetAsSockAddrIn()->sin_port = htons(inPort);
}

SocketAddress::SocketAddress(const PCTSTR inAddress, uint16_t inPort) {
	GetAsSockAddrIn()->sin_family = AF_INET;
	GetAsSockAddrIn()->sin_port = htons(inPort);
	InetPton(AF_INET, inAddress, GetAsSockAddrIn());
}

SocketAddress::SocketAddress(const sockaddr& inSockAddr) {
	memcpy(&mSockAddr, &inSockAddr, sizeof(sockaddr));
}

sockaddr_in* SocketAddress::GetAsSockAddrIn() {
	return reinterpret_cast<sockaddr_in*>(&mSockAddr);
}

size_t SocketAddress::GetSize() const {
	return sizeof(sockaddr); 
}