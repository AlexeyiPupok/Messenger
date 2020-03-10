#pragma once
typedef struct _CLIENT_INFO
{
	LIST_ENTRY pListEntry;
	SOCKET	comm_fd;
}CLIENT_INFO, *PCLIENT_INFO;

typedef struct _SERVER_INFO
{
	LIST_ENTRY ClientsListHead;
}SERVER_INFO, *PSERVER_INFO;

DWORD  RecvThread(SOCKET comm_fd);