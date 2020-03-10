#include "stdafx.h"
#pragma comment(lib, "Ws2_32.lib")

DWORD WINAPI RecvThread(SOCKET sockfd)
{
	int recieved = 0;
	char recvline[100];

	while ("")
	{
		memset(recvline, 0, sizeof(recvline));
		recieved = recv((SOCKET)sockfd, recvline, sizeof(recvline), 0);

		if (recieved == -1 || recieved == 0)
		{
			ExitProcess(0);
		}

		printf("%s\r\n", recvline);
	}

	return 0;
}

int main(int argc, char **argv)
{
	WSADATA wsaData;

	if (WSAStartup(WINSOCK_VERSION, &wsaData))
	{
		printf("winsock not be initialized !\r\n");
		WSACleanup();
	}

	SOCKET sockfd;
	char sendline[100];

	struct sockaddr_in servaddr;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	memset(&servaddr, 0, sizeof servaddr);

	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(59999);

	inet_pton(AF_INET, "127.0.0.1", &(servaddr.sin_addr));

	printf("Start connecting\r\n");

	connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

	HANDLE thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)RecvThread, (LPVOID)sockfd, 0, NULL);

	printf("Connected. Error %d\r\n", GetLastError());

	printf("Enter password \r\n");

	scanf_s("%s", sendline, (unsigned)_countof(sendline));
	send(sockfd, sendline, (int)strlen(sendline), 0);

	while (1)
	{
		memset(sendline, 0, 100);
		scanf_s("%s", sendline, (unsigned)_countof(sendline));
		send(sockfd, sendline, (int)strlen(sendline), 0);
	}
}