#ifndef __MAIN_H
#include "main.h"
#endif // !__MAIN_H

//bool WorldToScreenD3DW_left_hand(vec3 pos, vec2* screen, float matrix[16], int windowWidth, int windowHeight)
int WorldToScreenD3DW_left_hand(vec3 pos, vec2* screen, float matrix[4][4], int g_game_w, int g_game_h)
{
    //×Ô¼º¾ØÕó 4*4
    /*
    0.041292        0.832310        -0.000000       641.270447
    0.419566        -0.020815       1.265429        -57.224075
    -0.948139       0.047038        0.315139        -331.349396
    -0.947906       0.047027        0.315061        -324.267639
    */

    
    vec4 clipCoords;

    clipCoords.x = pos.x * matrix[0][0] + pos.y * matrix[0][1] + pos.z * matrix[0][2] + matrix[0][3];
    clipCoords.y = pos.x * matrix[1][0] + pos.y * matrix[1][1] + pos.z * matrix[1][2] + matrix[1][3];
    clipCoords.z = pos.x * matrix[2][0] + pos.y * matrix[2][1] + pos.z * matrix[2][2] + matrix[2][3];
    clipCoords.w = pos.x * matrix[3][0] + pos.y * matrix[3][1] + pos.z * matrix[3][2] + matrix[3][3];

    //clipCoords.x = pos.x * matrix[0] + pos.y * matrix[1] + pos.z * matrix[2] + matrix[3];
    //clipCoords.y = pos.x * matrix[4] + pos.y * matrix[5] + pos.z * matrix[6] + matrix[7];
    //clipCoords.z = pos.x * matrix[8] + pos.y * matrix[9] + pos.z * matrix[10] + matrix[11];
    //clipCoords.w = pos.x * matrix[12] + pos.y * matrix[13] + pos.z * matrix[14] + matrix[15];

    if (clipCoords.w < 0.1f)
        return 0;

    vec3 NDC;
    NDC.x = clipCoords.x / clipCoords.w;
    NDC.y = clipCoords.y / clipCoords.w;
    NDC.z = clipCoords.z / clipCoords.w;

    screen->x = (g_game_w / 2 * NDC.x) + (NDC.x + g_game_w / 2);
    screen->y = -(g_game_h / 2 * NDC.y) + (NDC.y + g_game_h / 2);
    return 1;
}


////bool WorldToScreenOpenGLW_right_hand(vec3 pos, vec3* screen, float matrix[16], int game_width, int game_height)
//int WorldToScreenOpenGLW_right_hand(vec3 pos, vec3* screen, float matrix[4][4], int g_game_w, int g_game_h)
//{
//    vec4 clipCoords;
//
//    clipCoords.x = pos.x * matrix[0][0] + pos.y * matrix[1][0] + pos.z * matrix[2][0] + matrix[3][0];
//    clipCoords.y = pos.x * matrix[0][1] + pos.y * matrix[1][1] + pos.z * matrix[2][1] + matrix[3][1];
//    clipCoords.z = pos.x * matrix[0][2] + pos.y * matrix[1][2] + pos.z * matrix[2][2] + matrix[3][2];
//    clipCoords.w = pos.x * matrix[0][3] + pos.y * matrix[1][3] + pos.z * matrix[2][3] + matrix[3][3];
//
//    //clipCoords.x = pos.x * matrix[0] + pos.y * matrix[4] + pos.z * matrix[8] + matrix[12];
//    //clipCoords.y = pos.x * matrix[1] + pos.y * matrix[5] + pos.z * matrix[9] + matrix[13];
//    //clipCoords.z = pos.x * matrix[2] + pos.y * matrix[6] + pos.z * matrix[10] + matrix[14];
//    //clipCoords.w = pos.x * matrix[3] + pos.y * matrix[7] + pos.z * matrix[11] + matrix[15];
//
//    if (clipCoords.w < 0.1f)
//    {
//        return 0;
//    }
//
//    vec3 NDC;
//    NDC.x = clipCoords.x / clipCoords.w;
//    NDC.y = clipCoords.y / clipCoords.w;
//    NDC.z = clipCoords.z / clipCoords.w;
//
//    screen->x = (g_game_w / 2 * NDC.x) + (NDC.x + g_game_w / 2);
//    screen->y = -(g_game_h / 2 * NDC.y) + (NDC.y + g_game_h / 2);
//    return 1;
//}


int WorldToScreenD3DZ_left_hand(float matrix[4][4], vec3 pos, int g_game_w, int g_game_h, int* box_x, int* box_y, int* box_w, int* box_h)
{
    printf("***in WorldToScreenD3DZ_left_hand*** g_game_w = %d, g_game_h = %d\n", g_game_w, g_game_h);
    //g_game_w = g_game_w * 2;
    //g_game_h = g_game_h * 2;
    //float clip_z = pos.x * matrix[2][0] + pos.y * matrix[2][1] + pos.z * matrix[2][2] + matrix[2][3];
    //if (clip_z < 0.1f)
    //{
    //    return 0;
    //}


    //float clip_x = pos.x * matrix[0][0] + pos.y * matrix[0][1] + pos.z * matrix[0][2] + matrix[0][3];
    //float clip_y_foot = pos.x * matrix[1][0] + pos.y * matrix[1][1] + (pos.z + 55.0f) * matrix[1][2] + matrix[1][3];
    //float clip_y_head = pos.x * matrix[1][0] + pos.y * matrix[1][1] + (pos.z - 50.0f) * matrix[1][2] + matrix[1][3];

    //float scal_ratio = 1.0f / clip_z;


    g_game_w = g_game_w / 2;
    g_game_h = g_game_h / 2;
    float clip_z = pos.x * matrix[2][0] + pos.y * matrix[2][1] + pos.z * matrix[2][2] + matrix[2][3];

    float scal_ratio = 1.0f / clip_z;

    if (clip_z < 0.1f)
    {
        return 0;
    }


    float clip_x =  pos.x * matrix[0][0] + pos.y * matrix[0][1] + pos.z * matrix[0][2] + matrix[0][3];
    float clip_y_foot = pos.x * matrix[1][0] + pos.y * matrix[1][1] + (pos.z + 75.0f) * matrix[1][2] + matrix[1][3];
    float clip_y_head = pos.x * matrix[1][0] + pos.y * matrix[1][1] + (pos.z - 15.0f) * matrix[1][2] + matrix[1][3];
    
    
    float screen_x = g_game_w + clip_x * scal_ratio * g_game_w ;
    float screen_y_foot = g_game_h - clip_y_foot * scal_ratio * g_game_h ;
    float screen_y_head = g_game_h - clip_y_head * scal_ratio * g_game_h ;


    
    float box_height = (screen_y_foot - screen_y_head);
    printf("---look box_height---- screen_y_foot is %f, screen_y_head is %f, box_height is %f\n", screen_y_foot, screen_y_head, box_height);

    
    *box_y = (int)(screen_y_head);
    *box_h = (int)(screen_y_foot - screen_y_head);
    *box_w = (int)(*box_h * 0.526);
    *box_x = (int)(screen_x - (*box_h * 0.526) / 2);






    //float box_height = (screen_y_head - screen_y_foot);
    //printf("---look box_height---- screen_y_foot is %f, screen_y_head is %f, box_height is %f\n", screen_y_foot, screen_y_head, box_height);
    //*box_x = (int)(screen_y_head);
    //*box_y = (int)(screen_y_foot);
    //*box_w = (int)(box_height / 2);
    //*box_h = (int)(box_height);

   
    

    return 1;

}