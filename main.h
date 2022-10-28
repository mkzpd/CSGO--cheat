#pragma once
#include <windows.h>

DWORD ProcessID;
HANDLE ProcessHandle;
DWORD blood;
DWORD person_linklist = 0x4DDD90C;
DWORD person_address;
DWORD blood_value;
DWORD person_address_value;
//DWORD game_exe_base_address;
DWORD client_dll_base_address;
int team_distinguish;
float x_zuobiao_value;
float y_zuobiao_value;
float z_zuobiao_value;
DWORD matrixAddress;
float g_matrix[4][4] = { 0 };
const char* cs_game_name = "csgo.exe";
const char* SiJi_game_name = "DS202266-Win64-Shipping.exe";
const char* client_dll_name = "client.dll";
HWND game_hwnd;
HWND white_window;
int g_game_x, g_game_y, g_game_w, g_game_h, worldtoscreen_flag;



struct vec4
{
    float x, y, z, w;
};

struct vec2
{
    float x, y;
};

struct vec3
{
    float x, y, z;
};

struct player
{
    float x;
    float y;
    float z;
    int blood;
    int camp;
};

vec2 screen;
vec3 pos;

struct player game_player[102];

void render_line(D3DCOLOR color, float x1, float y1, float x2, float y2, float line_size = 1.0f);
void render_text(D3DCOLOR color, long x, long y, const char* text);
void render_rect(D3DCOLOR color, float x, float y, float width, float height, float rect_size = 2.0f);
HRESULT init_d3d(HWND hWnd);
void cleanup_d3d();


void read_matrix();
int get_blood_xyz_camp_value();
DWORD FindGameProcessName(const char* ProcessName);
DWORD get_module_address(DWORD ProcessID, const char* look_for_module_name);
DWORD readDword(HANDLE ProcessHandle, DWORD person_address);
float readFloat(HANDLE ProcessHandle, DWORD person_address);
char* readCharArray(HANDLE ProcessHandle, DWORD person_address, int length);

void get_window_rect(HWND target, int* x, int* y, int* width, int* height);
void render_player_box();
void render_manager();
LRESULT __stdcall window_proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HWND create_window(HWND game_hwnd);
void message_handle(HWND game_hwnd, HWND windows_hwnd);

int WorldToScreenD3DW_left_hand(vec3 pos, vec2* screen, float matrix[4][4], int windowWidth, int windowHeight);
int WorldToScreenOpenGLW_right_hand(vec3 pos, vec3* screen, float matrix[4][4], int game_width, int game_height);
int WorldToScreenD3DZ_left_hand(float matrix[4][4], vec3 pos, int game_width, int game_height, int* box_x, int* box_y, int* box_w, int* box_h);