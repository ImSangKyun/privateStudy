#include <stdio.h>
#include <WinSock2.h>
#pragma comment (lib, "ws2_32.lib")
#define BUFFER_SIZE 1024

int main(void) {
	WSADATA wsa;
	SOCKET srvSocket;
	SOCKADDR_IN srvAddr;
	SOCKADDR_IN cliAddr;
	char buf[BUFFER_SIZE];
	int cliLen, recvSize, sendSize, cnt;

	if (WSAStartup(MAKEWORD(2, 2), &wsa) == -1) {
		printf("WSAStartup Error\n");
		return -1;
	}
	memset(&srvAddr, 0, sizeof(srvAddr));
	memset(&cliAddr, 0, sizeof(cliAddr));
	memset(&buf, 0, sizeof(buf));

	srvAddr.sin_family = AF_INET;
	srvAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	srvAddr.sin_port = htons(69);	//TFTP 포트번호

	srvSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (srvSocket == INVALID_SOCKET) {
		printf("socket Error\n");
		return -1;
	}

	if (bind(srvSocket, (SOCKADDR*)&srvAddr, sizeof(srvAddr)) == SOCKET_ERROR) {
		printf("bind error\n");
		return -1;
	}

	while (1) {
		cliLen = sizeof(cliAddr);
		recvSize = recvfrom(srvSocket, buf, BUFFER_SIZE, 0, (SOCKADDR*)&cliAddr, &cliLen);
		if (recvSize < 0) {
			printf("recv error\n");
			break;
		}
		//아 우분투로 개발해야하네
	}

	WSACleanup();
}