/** Copyright:
 *
 * Author:Huangzhaolan
 * Date:2014-3-5
 * Description:Fuck Bird��ͼ�����漰��������ʵ�֡�
 *
 */
#include "Drawing.h"
#include "Collision.h"
int GAME_STATE = 0;
int collisionT = 0;
const int SCREEN_WIDTH = 1280;//SCREEN��
const int SCREEN_HEIGHT = 720;//SCREEN��
float BirdVeloY=0;//С���ٶ�
float BlockVeloX=-5;
SDL_Window* window = NULL; //SDL����ָ��
SDL_Surface* screenSurface = NULL;//SDL����ָ��
SDL_Renderer* screenRen = NULL;//SDL��Ⱦ��
SDL_TimerID MoveTimer;//SDL��ʱ��
SDL_Rect rect;
Blocks block;
/*************************************************
Function:start()
Description:��Ϸ������ڵ�
Calls:(none)
Input:(none)
Output:(none)
Return:(int)״̬����0,������-1
Others:         // ����˵��
*************************************************/
int start()
{



    /* SDL��ʼ��*/
    if( SDL_Init( SDL_INIT_VIDEO|SDL_INIT_TIMER ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        return 1;
    }

    //�������ڶ���
    window = SDL_CreateWindow("Fuck Bird", //����
                              SDL_WINDOWPOS_CENTERED,//�������
                              SDL_WINDOWPOS_CENTERED,//�������
                              SCREEN_WIDTH,//���ڿ��
                              SCREEN_HEIGHT, //���ڸ߶�
                              SDL_WINDOW_SHOWN );//������ʽ��������������ʾ��ȫ��
    if( window == NULL )
    {
        printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        return 1;
    }

    //������Ⱦ��
    screenRen = SDL_CreateRenderer(window,
                                   -1,
                                   SDL_RENDERER_ACCELERATED| SDL_RENDERER_PRESENTVSYNC);
    if( screenRen == NULL )
    {
        printf( "Render could not be get! SDL_Error: %s\n", SDL_GetError() );
        return 1;
    }

    ScreenInitialize();

    MoveTimer = SDL_AddTimer(1,MainCallBack,NULL);
    //�¼�����ѭ��
    while (1)
    {


        SDL_Event e;
        if (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                break;
            }
            else if ( e.type == SDL_KEYDOWN)
            {
              //  printf("KeyDown");
                 KeyEventHandler(&(e.key));

            }
            else if (e.type == SDL_MOUSEBUTTONDOWN)
            {
                MouseEventHandler();
            }
        }


    }



    SDL_UpdateWindowSurface( window );
    // SDL_Delay( 5000 );



    SDL_DestroyWindow( window );
    SDL_Quit();
    return 0;

}
/*************************************************
Function:SetSDLRect()
Description:����SDL���ζ�������
Calls:(none)
Input:SDL_rect* rect, //SDL���ζ���
      int posX, //����x�����Ŀ��ֵ
      int posY, //����y�����Ŀ��ֵ
      int width,//���ο�
      int height��//���θ�
Output:(none)
Return:(int)״̬����0,������-1
Others:         // ����˵��
*************************************************/
int SetSDLRect(SDL_Rect* rect,const int posX,const int posY,const int width,const int height)
{
    if (NULL == rect)
    {
        return -1;
    }

    rect->x = posX;
    rect->y = posY;
    if (NULL !=  height)
    {
        rect->h = height;
    }

    if (NULL != width)
    {
        rect->w = width;
    }

    return 0;


}
/*************************************************
Function:KeyEventHandler()
Description:�����¼�������
Calls:(none)
Input:SDL_KeyboardEvent* KeyEvent, //SDL�����¼�����

Output:(none)
Return:(int)״̬����0,������-1
Others:         // ����˵��
*************************************************/
int KeyEventHandler(SDL_KeyboardEvent* KeyEvent)
{
  //  printf("KeyHandling!");
    switch (KeyEvent->keysym.scancode)
    {
    case SDL_SCANCODE_DOWN :

        SetSDLRect(&rect,rect.x,(rect.y+10) ,100,100);

        break;
    case SDL_SCANCODE_UP :
        SetSDLRect(&rect,rect.x,(rect.y-10) ,100,100);

      //  BirdVeloY = -1.25;
        break;
    case SDL_SCANCODE_LEFT :

        SetSDLRect(&rect,(rect.x-10) ,rect.y ,100,100);

        break;
    case SDL_SCANCODE_RIGHT :

        SetSDLRect(&rect,(rect.x+10),rect.y ,100,100);

        break;


    }
    return 0;
}
int MouseEventHandler()
{
    BirdVeloY = -5;
    return 0;
}
/*************************************************
Function:KeyEventHandler()
Description:�����¼�������
Calls:(none)
Input:SDL_KeyboardEvent* KeyEvent, //SDL�����¼�����

Output:(none)
Return:(int)״̬����0,������-1
Others:         // ����˵��
*************************************************/
unsigned int BirdCallBackMove(int interval,SDL_Rect* Bird)
{
    float posY;
    if (GAME_STATE == 1)
    {
        return interval;
    }
    BirdVeloY = 0.5 *interval + BirdVeloY;
    posY = Bird->y +  BirdVeloY * interval;
    SetSDLRect(Bird,Bird->x,(int )posY,Bird->w,Bird->h);
    return interval;
}
unsigned int BlocksCallBackMove(int interval,Blocks* block)
{
    float posX;
    if (GAME_STATE == 1)
    {
        return interval;
    }

    posX = (block->downblock).x +  BlockVeloX * interval;
    SetSDLRect(&(block->downblock),(int)posX,(block->downblock).y,(block->downblock).w,(block->downblock).h);
    SetSDLRect(&(block->upblock),(int)posX,(block->upblock).y,(block->upblock).w,(block->upblock).h);
    return interval;
}
unsigned int MainCallBack(int interval,void * para)
{
    MainRun();
  BirdCallBackMove(interval,&rect);
  BlocksCallBackMove(interval,&block);
    return interval;

}
int MainRun()
{
    CollisionCheck();
    ScreenDrawer();

    return 0;
}
int ScreenDrawer()

{


    SDL_RenderClear(screenRen);
    SDL_SetRenderDrawColor(screenRen, 0,255, 0, 255);
    SDL_RenderDrawRect(screenRen,
                       &rect);
    SDL_RenderFillRect(screenRen,
                       &(block.upblock));
    SDL_RenderFillRect(screenRen,
                       &(block.downblock));
    SDL_RenderPresent(screenRen);
    SDL_SetRenderDrawColor(screenRen, 0, 0, 0, 255);
    return 0;
}
int ScreenInitialize()
{
    SDL_SetRenderDrawColor(screenRen, 0, 0, 0, 255);
    SetSDLRect(&rect,SCREEN_WIDTH/3,SCREEN_HEIGHT/2,50,50);
    SetSDLRect(&(block.upblock),1080,0,100,300);
    SetSDLRect(&(block.downblock),1080,520,100,300);
    SDL_SetRenderDrawColor(screenRen, 0,255, 0, 255);
    SDL_RenderDrawRect(screenRen,
                       &rect);

    SDL_RenderPresent(screenRen);
    return 0;
}
int CollisionCheck()
{
    GAME_Pause();
    //Collision Check
    bird.wid = rect.w;
    bird.x = rect.x;
    bird.y = rect.y;
    upobs.wid = (block.upblock).w;
    upobs.x = (block.upblock).x;
    upobs.y = (block.upblock).y + (block.upblock).h;
    dowobs.wid =block. downblock.w;
    dowobs.x =block. downblock.x;
    dowobs.y =block. downblock.y ;
    if (1 == isCol(bird,upobs,dowobs,SCREEN_HEIGHT))
    {
        collisionT++;
        printf("Collision!# %d \n",collisionT);
        return 0;

    }
    else if (0 == isCol(bird,upobs,dowobs,SCREEN_HEIGHT))
    {
        BirdVeloY = 0.1;
        SetSDLRect(&rect,rect.x,0,NULL,NULL);
    }

    GAME_Resume();
    return 0;
}
int GAME_Pause()
{
    GAME_STATE = 1;
}
int GAME_Resume()
{
    GAME_STATE = 0;
}

