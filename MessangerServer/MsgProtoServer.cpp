#include "stdafx.h"

CHAR* MsgProc(PCLIENT_INFO pClient, CHAR* Message, size_t MsgLen)
{
	if (MsgLen < 4)
	{
		//return ERROR;byh7gbhubhu
	}
	switch (*(DWORD*)Message)
	{
		case REGISTER_USER:
		{
			//Сообщение по протоколу о введении логина
			send(pClient->comm_fd, (LPSTR)"Enter login", (int)strlen("Enter login"), 0);
			//изменяем состояние клиента
			break;
		}

		case LOGIN:
		{
		/*	unsigned char digest[16] = { 0 };
			//Сообщение по протоколу о введении логина
		   	if ((int)strlen(Message) <= 5)
			{
				//отправить сообщение об ошибке (по протоколу)
				break;
			}

				
				//md5((unsigned char*)&Message[5], ((int)strlen(Message) - 5), digest);
		
			//изменяем состояние клиента*/
			break;
		}

		case AUTH_USER:
		{
			int i = 0;
			break;
		}

		default:
		{
			int i = 0;
			break;
		}
		
	}
	return NULL;
}