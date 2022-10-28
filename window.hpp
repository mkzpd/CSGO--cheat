#include <windows.h>
#include <dwmapi.h>
#include "d3d9.hpp"
#include "gamedata.hpp"
#include "worldtoscreen​.hpp"

#ifndef __MAIN_H
#include "main.h"
#endif // !__MAIN_H

#pragma comment(lib,"dwmapi.lib")



void get_window_rect(HWND game_hwnd, int* g_game_x, int* g_game_y, int* g_game_w, int* g_game_h)
{
	RECT rect;
	GetWindowRect(game_hwnd,&rect);
	*g_game_x = rect.left;
	*g_game_y = rect.top;
	*g_game_w = rect.right - rect.left;
	*g_game_h = rect.bottom - rect.top;
}

void read_matrix()
{
	matrixAddress = client_dll_base_address + 0x4DCF234;
	ReadProcessMemory(ProcessHandle, (LPCVOID)(matrixAddress), &g_matrix, sizeof(float) * 4 * 4, 0);
	for (int i = 0; i < 4; i++)
	{
		for (int num = 0; num < 4; num++)
		{
			printf("%f\t", g_matrix[i][num]);
		}
		printf("\n");
	}
}

void render_player_box()
{

	get_window_rect(game_hwnd, &g_game_x, &g_game_y, &g_game_w, &g_game_h);
	printf("***Begin go into render_player_box*** x = %d, y = %d, width = %d, height = %d\n", g_game_x, g_game_y, g_game_w, g_game_h);
	get_blood_xyz_camp_value();
	read_matrix();

	int self_camp = game_player[1].camp;
	for (int i = 2; i < 11; i++)
	{
		if (game_player[i].blood > 1)
		{
			D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 0);
			if (game_player[i].camp != self_camp)
			{
				color = D3DCOLOR_XRGB(255, 0, 0);
			}
			    
			pos.x = game_player[i].x;
			pos.y = game_player[i].y;
			pos.z = game_player[i].z;

			int box_x;
			int box_y;
			int box_w;
			int box_h;
				
			worldtoscreen_flag = WorldToScreenD3DZ_left_hand(g_matrix, pos, g_game_w, g_game_h, &box_x, &box_y, &box_w, &box_h);
			if (worldtoscreen_flag)
			{
				printf("***准备画图了 *** box_x = %d, box_y = %d, box_w = %d, box_h = %d\n", box_x, box_y, box_w, box_h);
				render_rect(color, box_x , box_y, box_w, box_h);
				render_line(color, g_game_w / 2, g_game_h,(int)(box_x + (box_h * 0.526) / 2), box_y);

				//render_text(color, box_x, box_y, "here");
			}


				
			//worldtoscreen_flag = WorldToScreenD3DW_left_hand(pos, &screen, g_matrix, g_game_w, g_game_h);
			//if (worldtoscreen_flag)
			//{
			//	
			//	int x = screen.x - 25, y = screen.y + 25, w = 45, h = -90;
			//	render_rect(color, x, y, w, h);
			//	render_line(color, g_game_w / 2, g_game_h, x + (w / 2), y - h);
			//}


		}
	}
}

void render_manager()
{
	if (NULL == g_pd3dDevice)
	{
		return;
	}

	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, 0, 1.0f, 0);

	if (SUCCEEDED(g_pd3dDevice->BeginScene()))
	{
		render_player_box();

		//render_line(D3DCOLOR_XRGB(255, 0, 0), 0, 0, 40, 40);

		////D3DXVECTOR2 vextor[2]{ {0,0}, {40,40} };
		////G_ID3DXLine->SetWidth(1);
		////G_ID3DXLine->Draw(vextor, 2, D3DCOLOR_XRGB(255, 0, 0));

		//render_text(D3DCOLOR_XRGB(255, 0, 0), 100, 100, "测试");
		////RECT rect{ 100, 100 };
		////G_ID3DXFont->DrawTextA(NULL, "测试", -1, &rect, DT_CALCRECT, D3DCOLOR_XRGB(255, 0, 0));
		////G_ID3DXFont->DrawTextA(NULL, "测试", -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 0, 0));

		//render_rect(D3DCOLOR_XRGB(255, 0, 0), 150, 150, 50, 100);

		g_pd3dDevice->EndScene();

	}

	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);

}

MARGINS g_MARGINS;
LRESULT __stdcall window_proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
		DwmExtendFrameIntoClientArea(hWnd, &g_MARGINS);
		break;
	case WM_PAINT:
		render_manager();
		break;
	case WM_CLOSE:
		cleanup_d3d();
		PostQuitMessage;
		break;
	default:
		return DefWindowProcA(hWnd, uMsg, wParam,lParam);
	}
	return 1;
}

HWND create_window(HWND game_hwnd)
{
	const char* window_name = "test";
	WNDCLASSEX windows_class;
	ZeroMemory(&windows_class, sizeof(windows_class));
	windows_class.cbSize = sizeof(windows_class);
	windows_class.hCursor = LoadCursor(0, IDC_ARROW);
	windows_class.hInstance = GetModuleHandle(NULL);
	windows_class.lpfnWndProc = window_proc;
	windows_class.lpszClassName = window_name;
	windows_class.style = CS_VREDRAW | CS_HREDRAW;
	//windows_class.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
	HRESULT result = RegisterClassExA(&windows_class);


	
	get_window_rect(game_hwnd, &g_game_x, &g_game_y, &g_game_w, &g_game_h);
	// | WS_EX_TRANSPARENT | WS_EX_LAYERED  
	HWND windows_hwnd = CreateWindowExA(WS_EX_TOPMOST | WS_EX_TRANSPARENT | WS_EX_LAYERED,
	window_name, window_name, WS_POPUP, g_game_x, g_game_y, g_game_w, g_game_h, NULL, NULL, GetModuleHandle(NULL), NULL);

	SetLayeredWindowAttributes(windows_hwnd, 0, RGB(0, 1, 0), LWA_COLORKEY);

	ShowWindow(windows_hwnd, SW_SHOW);
	UpdateWindow(windows_hwnd);
	return windows_hwnd;
}

void message_handle(HWND game_hwnd, HWND windows_hwnd)
{
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessageA(&msg);
		}

		get_window_rect(game_hwnd, &g_game_x, &g_game_y, &g_game_w, &g_game_h);
		MoveWindow(windows_hwnd, g_game_x, g_game_y, g_game_w, g_game_h, TRUE);
	}
}