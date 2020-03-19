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
			int i = 0;
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
			//return ERROR;
			break;
		}
	}
	return NULL;
}