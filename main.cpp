#include "window.hpp"

#ifndef __MAIN_H
#include "main.h"
#endif // !__MAIN_H

// 人物基址 client.dll+4DDD90C    
//自己矩阵基址  client.dll+4DCF234



int main()
{
	/* 得到进程ID */
	if (!(ProcessID = FindGameProcessName(cs_game_name)))
	{
		printf("游戏没启动，请先启动游戏\n");
		return 0;
	}
	printf("游戏己启动，进程ID用十进制表示为%d,十六进制为%X\n", ProcessID, ProcessID);
	/* 通过进程ID取得进程句柄*/
	if (!(ProcessHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, ProcessID)))
	{
		printf("进程打开失败!\n");
		return 0;
	}


	//game_exe_base_address = get_module_address(ProcessID, cs_game_name);

	//printf("%s模块的基地址是%X(hex)\n\n", cs_game_name, game_exe_base_address);

	client_dll_base_address = get_module_address(ProcessID, client_dll_name);
	printf("%s模块的基地址是%X(hex)\n\n", client_dll_name, client_dll_name);

	game_hwnd = FindWindowA(NULL, "Counter-Strike: Global Offensive - Direct3D 9");
	white_window = create_window(game_hwnd);
	init_d3d(white_window);
	message_handle(game_hwnd, white_window);


	CloseHandle(ProcessHandle);
	return 0;
}

