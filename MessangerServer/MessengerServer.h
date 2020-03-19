#pragma once
typedef enum ClientState
{
	Disconnected,
	Connected,
	Registred,
	Login,
	Loginned
}ClientState;

typedef struct _CLIENT_INFO
{
	LIST_ENTRY pListEntry;
	SOCKET	comm_fd;
	ClientState State;
}CLIENT_INFO, *PCLIENT_INFO;

typedef struct _SERVER_INFO
{
	LIST_ENTRY ClientsListHead;
}SERVER_INFO, *PSERVER_INFO;

DWORD  RecvThread(SOCKET comm_fd);