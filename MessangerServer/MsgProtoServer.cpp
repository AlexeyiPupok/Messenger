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
			unsigned char digest[16] = { 0 };
			char FinalPath[MAX_PATH + 6] = { 0 };
			char TempBuf[MAX_PATH] = { 0 };
			//���� ������ ��� ��������������
			if (pClient->ClientCondition == Registred)
			{
				send(pClient->comm_fd, (LPSTR)"Error, already registered", (int)strlen("Error, already registered"), 0);
				break;
			}
			//�������� ��������� �������
			pClient->ClientCondition = Registred;
			//��������� �� ��������� � �������� ������
			//send(pClient->comm_fd, (LPSTR)"Enter login", (int)strlen("Enter login"), 0);
			//��������� �� ��������� � �������� ������

			AsyncRecieve(pClient->comm_fd, TempBuf, sizeof(TempBuf));

			sprintf(FinalPath, "users\\%s", TempBuf);
			
			FILE *Login;
			Login = fopen(FinalPath, "w");

			memset(TempBuf, 0, MAX_PATH);

			//send(pClient->comm_fd, (LPSTR)"Enter password", (int)strlen("Enter password"), 0);

			int count = AsyncRecieve(pClient->comm_fd, TempBuf, sizeof(TempBuf));

			md5((unsigned char*)TempBuf , count, digest);

			fwrite(digest, 1, sizeof(digest), Login);

			fclose(Login);

			//send(pClient->comm_fd, (LPSTR)"successful registration", (int)strlen("successful registration"), 0);
			//�������� ��������� �������*/
			pClient->ClientCondition = Connected;
			
			break;
		}

		case LOGIN:
		{
		/*	unsigned char digest[16] = { 0 };
			//��������� �� ��������� � �������� ������
		   	if ((int)strlen(Message) <= 5)
			{
				//��������� ��������� �� ������ (�� ���������)
				break;
			}

				
				//md5((unsigned char*)&Message[5], ((int)strlen(Message) - 5), digest);
		
			//�������� ��������� �������*/
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