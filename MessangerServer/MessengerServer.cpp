// EchoServerThreads.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#pragma comment(lib, "Ws2_32.lib")

SERVER_INFO g_server_info;

PCLIENT_INFO
GetClientByComm(SOCKET comm_fd)
{
	PCLIENT_INFO pCurrentClientInfo = (PCLIENT_INFO)g_server_info.ClientsListHead.Flink;
	while (g_server_info.ClientsListHead.Flink != pCurrentClientInfo->pListEntry.Flink)
	{
		printf("Current Client %llx\r\n", pCurrentClientInfo->comm_fd);

		if (pCurrentClientInfo->comm_fd == comm_fd)
		{
			return pCurrentClientInfo;
		}

		pCurrentClientInfo = (PCLIENT_INFO)pCurrentClientInfo->pListEntry.Flink;
	}

	return NULL;
}

void
ClientExit(SOCKET comm_fd)
{

	PCLIENT_INFO pClientInfo = GetClientByComm(comm_fd);

	printf("Client %zd removed\r\n", pClientInfo->comm_fd);

	RemoveEntryList(&pClientInfo->pListEntry);

	free(pClientInfo);
}

int
AsyncRecieve(SOCKET comm_fd, char* message, int msg_len)
{
	int recieved = 0;

	while ("Some shit")
	{
		recieved = recv(comm_fd, message, msg_len, 0);

		if (recieved == -1)
		{
			if (WSAGetLastError() != WSAETIMEDOUT)
				break;
			else
				continue;
		}
		else
		{
			break;
		}

	}

	return recieved;

}

VOID
SendMessageToClients(char* message, size_t comm_fd)
{
	PCLIENT_INFO pCurrentClientInfo = (PCLIENT_INFO)g_server_info.ClientsListHead.Flink;

	while (g_server_info.ClientsListHead.Flink != pCurrentClientInfo->pListEntry.Flink)
	{

		if (pCurrentClientInfo->comm_fd != comm_fd)
		{
			send(pCurrentClientInfo->comm_fd, (LPSTR)message, (int)strlen(message), 0);
		}

		pCurrentClientInfo = (PCLIENT_INFO)pCurrentClientInfo->pListEntry.Flink;
	}

	return;
}


VOID
PrintAllClients()
{
	PCLIENT_INFO pCurrentClientInfo = (PCLIENT_INFO)g_server_info.ClientsListHead.Flink;

	while (g_server_info.ClientsListHead.Flink != pCurrentClientInfo->pListEntry.Flink)
	{
		printf("Current Client %zd\r\n", pCurrentClientInfo->comm_fd);
		pCurrentClientInfo = (PCLIENT_INFO)pCurrentClientInfo->pListEntry.Flink;
	}
}

int main()
{

	WSADATA wsaData;

	if (WSAStartup(WINSOCK_VERSION, &wsaData))
	{
		printf("winsock not bi initialized !\n");
		WSACleanup();
	}

	InitializeListHead(&g_server_info.ClientsListHead);

	SOCKET listen_fd, comm_fd;

	struct sockaddr_in servaddr;

	listen_fd = socket(AF_INET, SOCK_STREAM, 0);

	memset(&servaddr, 0, sizeof(servaddr));


	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htons(INADDR_ANY);
	servaddr.sin_port = htons(59999);

	bind(listen_fd, (struct sockaddr *) &servaddr, sizeof(servaddr));

	while (1)
	{
		listen(listen_fd, 10);

		comm_fd = accept(listen_fd, (struct sockaddr*) NULL, NULL);

		int timeout = 500;  // user timeout in milliseconds [ms]
		setsockopt(comm_fd, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(timeout));

		PCLIENT_INFO pClientInfo = (PCLIENT_INFO)malloc(sizeof(CLIENT_INFO));

		pClientInfo->comm_fd = comm_fd;

		InsertTailList(&g_server_info.ClientsListHead, &pClientInfo->pListEntry);

		HANDLE thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)RecvThread, (LPVOID)comm_fd, 0, NULL);

	}
}

DWORD  RecvThread(SOCKET comm_fd)
{
	char str[100];

	memset(str, 0, sizeof(str));
	PCLIENT_INFO pClientInfo = GetClientByComm(comm_fd);

	while (1)
	{
		memset(str, 0, 100);

		int recieved = AsyncRecieve(comm_fd, str, sizeof(str));

		if (recieved == -1 || recieved == 0)
		{
			printf("Client %zd fell off\r\n", comm_fd);

			ClientExit(comm_fd);

			PrintAllClients();

			return 0;
		}

		printf("Client %zd said: %s\r\n", comm_fd, str);

		MsgProc(pClientInfo, str, recieved);

		SendMessageToClients(str, comm_fd);
	}
};