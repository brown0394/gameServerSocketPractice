#pragma once
#include <stdint.h>
#include <memory>
#include <Winsock2.h>
class SocketAddress
{
public:
	SocketAddress(uint32_t inAddress, uint16_t inPort);
	SocketAddress(const PCTSTR inAddress, uint16_t inPort);
	SocketAddress(const sockaddr& inSockAddr);
	size_t GetSize() const;
private:
	sockaddr mSockAddr;
	sockaddr_in* GetAsSockAddrIn();
	friend class UDPSocket;
	friend class TCPSocket;
};
typedef std::shared_ptr<SocketAddress> SocketAddressPtr;

