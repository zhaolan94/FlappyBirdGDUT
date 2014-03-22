/** Copyright:
 *
 * Author:Huangzhaolan
 * Date:2014-3-5
 * Description:Fuck Bird的游戏界面及物理引擎实现。
 *
 */
#include <SDL.h>
#include <stdio.h>

#ifndef DRAWING_H_INCLUDED

#define DRAWING_H_INCLUDED
typedef struct
{
    SDL_Rect upblock,downblock;
}Blocks;
/*************************************************
Function:start()
Description:游戏界面入口点
Calls:(none)
Input:(none)
Output:(none)
Return:(int)状态正常0,不正常-1
Others:         // 其它说明
*************************************************/

int start();

/*************************************************
Function:SetRect()
Description:设置矩形对象属性
Calls:(none)
Input:(none)
Output:(none)
Return:(int)状态正常0,不正常-1
Others:         // 其它说明
*************************************************/
int SetSDLRect(SDL_Rect* rect,int posX,int posY,int width,int height);
unsigned int BirdCallBackMove(int interval,SDL_Rect* Bird );
int MainRun();
int ScreenDrawer();
int ScreenInitialize();
unsigned int MainCallBack(int interval,void*);
unsigned int BlocksCallBackMove(int interval,Blocks* block);
int CollisionCheck();
int MouseEventHandler();
#endif // DRAWING_H_INCLUDED
