#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <Tlhelp32.h>
#include <d3d9.h>

#ifndef __MAIN_H
#include "main.h"
#endif // !__MAIN_H



#pragma warning(disable:4996)



int get_blood_xyz_camp_value()
{
	int count = 0;
	/* ������Ϸ�������Ѫֵ��xyz���ꡢ��Ӫ��ʶ*/
	for (int i = 1; i < 11; i++)
	{


		//ReadProcessMemory(ProcessHandle, (LPCVOID)(g_base_address + person_linklist + 0x10 * i), &person_address, sizeof(DWORD), 0);
		person_address = readDword(ProcessHandle, client_dll_base_address + person_linklist + 0x10 * i);
		//printf("%X + %X + 0x10 * %d = %X\n", g_base_address, person_linklist, i, (g_base_address + person_linklist + 0x10 * i));
		//printf("person_address is %X\n", person_address);
		//printf("person_address_value is %X\n", person_address_value);

		if (person_address != NULL)
		{
			game_player[i].blood = readDword(ProcessHandle, person_address + 0x100);
			game_player[i].camp = readDword(ProcessHandle, person_address + 0xF4);
			//ReadProcessMemory(ProcessHandle, (LPCVOID)(person_address + 0x100), &blood_value, sizeof(DWORD), 0);
			//ReadProcessMemory(ProcessHandle, (LPCVOID)(person_address + 0xF4), &team_distinguish, sizeof(DWORD), 0);

			game_player[i].x = readFloat(ProcessHandle, person_address + 0x138);
			game_player[i].y = readFloat(ProcessHandle, person_address + 0x13c);
			game_player[i].z = readFloat(ProcessHandle, person_address + 0x140);
			//ReadProcessMemory(ProcessHandle, (LPCVOID)(person_address + 0x138), &x_zuobiao_value, sizeof(FLOAT), 0);
			//ReadProcessMemory(ProcessHandle, (LPCVOID)(person_address + 0x13c), &y_zuobiao_value, sizeof(FLOAT), 0);
			//ReadProcessMemory(ProcessHandle, (LPCVOID)(person_address + 0x140), &z_zuobiao_value, sizeof(FLOAT), 0);


			printf("***��%d��������Ӫ��ʾ%d[����:2Ϊ�ֲ����ӣ�3Ϊ���־�Ӣ]Ѫ��Ϊ%d,x������%f,y������%f,z������%f\n\n", 
					i, game_player[i].camp, game_player[i].blood, game_player[i].x, game_player[i].y, game_player[i].z);
			
		}
		else
		{
			count++;
		}
		if (count == 49)
		{
			printf("\n*******person_address����NULL��������������Ƿ���ȷ��������Ϸ�Ƿ��������Լ��Ƿ�ʼ����Ϸ��\n");
			return 0;
		}

	}
	printf("\n\n");
	/*Sleep(1000);*/
}


DWORD readDword(HANDLE ProcessHandle, DWORD person_address)
{
	DWORD value = 0;
	DWORD read_size = 0;
	ReadProcessMemory(ProcessHandle, (LPCVOID)(person_address), &value, sizeof(DWORD), &read_size);
	return value;
}

float readFloat(HANDLE ProcessHandle, DWORD person_address)
{
	float value = 0;
	DWORD read_size = 0;
	ReadProcessMemory(ProcessHandle, (LPCVOID)(person_address), &value, sizeof(float), &read_size);
	return value;
}

char* readCharArray(HANDLE ProcessHandle, DWORD person_address,int length)
{
	char value[2048] = {0};
	DWORD read_size = 0;
	ReadProcessMemory(ProcessHandle, (LPCVOID)(person_address), value, length, &read_size);
	return value;
}

DWORD get_module_address(DWORD ProcessID, const char* look_for_module_name)
{
	HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, ProcessID);
	MODULEENTRY32 module_info;
	int state;
	ZeroMemory(&module_info, sizeof(module_info));
	module_info.dwSize = sizeof(module_info);

	char look_for_module_name_up[1024] = { 0 };
	char szModule_up[1024] = { 0 };
	strncpy(look_for_module_name_up, look_for_module_name, strlen(look_for_module_name));
	_strupr(look_for_module_name_up);

	state = Module32First(snap, &module_info);

	while (state)
	{
		strncpy(szModule_up, module_info.szModule, strlen(module_info.szModule));
		_strupr(szModule_up);

		//printf("look_for_module_name_upģ������%s\n", look_for_module_name_up);
		//printf("found module_info.szModuleģ��������%s\n", module_info.szModule);
		//printf("ģ�����ַ��%d(dec),%X(hex)\n", module_info.modBaseAddr, module_info.modBaseAddr);

		if (0 == (strncmp(look_for_module_name_up, szModule_up, strlen(look_for_module_name))))
		{
			CloseHandle(snap);
			return (DWORD)module_info.modBaseAddr;
		}
		state = Module32Next(snap, &module_info);

	}

	CloseHandle(snap);
	return 0;
}


DWORD FindGameProcessName(const char* ProcessName)
{
	PROCESSENTRY32 stProcess;
	HANDLE hProcessShot;
	hProcessShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	stProcess.dwSize = sizeof(PROCESSENTRY32);
	Process32First(hProcessShot, &stProcess);
	do
	{
		if (!strcmp(ProcessName, stProcess.szExeFile))
			return stProcess.th32ProcessID;
	} while (Process32Next(hProcessShot, &stProcess));
	CloseHandle(hProcessShot);
	return 0;
}