/** Copyright:
 *
 * Author:Huangzhaolan
 * Date:2014-3-5
 * Description:Fuck Bird����Ϸ���漰��������ʵ�֡�
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
Description:��Ϸ������ڵ�
Calls:(none)
Input:(none)
Output:(none)
Return:(int)״̬����0,������-1
Others:         // ����˵��
*************************************************/

int start();

/*************************************************
Function:SetRect()
Description:���þ��ζ�������
Calls:(none)
Input:(none)
Output:(none)
Return:(int)״̬����0,������-1
Others:         // ����˵��
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
