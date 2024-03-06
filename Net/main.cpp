#include <iostream>
#include <Winsock2.h>
#include <WS2tcpip.h>

void setSockAddr(sockaddr_in& myAddr, int b1, int b2, int b3, int b4, int port) {
	memset(myAddr.sin_zero, 0, sizeof(myAddr.sin_zero));
	myAddr.sin_family = AF_INET;
	myAddr.sin_port = htons(port);
	myAddr.sin_addr.S_un.S_un_b.s_b1 = b1;
	myAddr.sin_addr.S_un.S_un_b.s_b2 = b2;
	myAddr.sin_addr.S_un.S_un_b.s_b3 = b3;
	myAddr.sin_addr.S_un.S_un_b.s_b4 = b4;
}

int main() {
	WSAData lpwsa;

	sockaddr_in myAddr;
	setSockAddr(myAddr, 65, 254, 248, 180, 80);

	if (!WSAStartup(MAKEWORD(2, 2), &lpwsa)) {


		WSACleanup();
	}
}