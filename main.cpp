#include "window.hpp"

#ifndef __MAIN_H
#include "main.h"
#endif // !__MAIN_H

// �����ַ client.dll+4DDD90C    
//�Լ������ַ  client.dll+4DCF234



int main()
{
	/* �õ�����ID */
	if (!(ProcessID = FindGameProcessName(cs_game_name)))
	{
		printf("��Ϸû����������������Ϸ\n");
		return 0;
	}
	printf("��Ϸ������������ID��ʮ���Ʊ�ʾΪ%d,ʮ������Ϊ%X\n", ProcessID, ProcessID);
	/* ͨ������IDȡ�ý��̾��*/
	if (!(ProcessHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, ProcessID)))
	{
		printf("���̴�ʧ��!\n");
		return 0;
	}


	//game_exe_base_address = get_module_address(ProcessID, cs_game_name);

	//printf("%sģ��Ļ���ַ��%X(hex)\n\n", cs_game_name, game_exe_base_address);

	client_dll_base_address = get_module_address(ProcessID, client_dll_name);
	printf("%sģ��Ļ���ַ��%X(hex)\n\n", client_dll_name, client_dll_name);

	game_hwnd = FindWindowA(NULL, "Counter-Strike: Global Offensive - Direct3D 9");
	white_window = create_window(game_hwnd);
	init_d3d(white_window);
	message_handle(game_hwnd, white_window);


	CloseHandle(ProcessHandle);
	return 0;
}

