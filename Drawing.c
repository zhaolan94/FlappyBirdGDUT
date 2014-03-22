/** Copyright:
 *
 * Author:Huangzhaolan
 * Date:2014-3-5
 * Description:Fuck Bird的图形引擎及物理引擎实现。
 *
 */
#include "Drawing.h"
#include "Collision.h"
int GAME_STATE = 0;
int collisionT = 0;
const int SCREEN_WIDTH = 1280;//SCREEN宽
const int SCREEN_HEIGHT = 720;//SCREEN高
float BirdVeloY=0;//小鸟速度
float BlockVeloX=-5;
SDL_Window* window = NULL; //SDL窗口指针
SDL_Surface* screenSurface = NULL;//SDL表面指针
SDL_Renderer* screenRen = NULL;//SDL渲染器
SDL_TimerID MoveTimer;//SDL计时器
SDL_Rect rect;
Blocks block;
/*************************************************
Function:start()
Description:游戏界面入口点
Calls:(none)
Input:(none)
Output:(none)
Return:(int)状态正常0,不正常-1
Others:         // 其它说明
*************************************************/
int start()
{



    /* SDL初始化*/
    if( SDL_Init( SDL_INIT_VIDEO|SDL_INIT_TIMER ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        return 1;
    }

    //创建窗口对象
    window = SDL_CreateWindow("Fuck Bird", //标题
                              SDL_WINDOWPOS_CENTERED,//横向剧中
                              SDL_WINDOWPOS_CENTERED,//纵向居中
                              SCREEN_WIDTH,//窗口宽度
                              SCREEN_HEIGHT, //窗口高度
                              SDL_WINDOW_SHOWN );//窗口样式：创建后立即显示并全屏
    if( window == NULL )
    {
        printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        return 1;
    }

    //创建渲染器
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
    //事件处理循环
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
Description:设置SDL矩形对象属性
Calls:(none)
Input:SDL_rect* rect, //SDL矩形对象
      int posX, //矩形x坐标的目标值
      int posY, //矩形y坐标的目标值
      int width,//矩形宽
      int height，//矩形高
Output:(none)
Return:(int)状态正常0,不正常-1
Others:         // 其它说明
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
Description:键盘事件处理函数
Calls:(none)
Input:SDL_KeyboardEvent* KeyEvent, //SDL键盘事件参数

Output:(none)
Return:(int)状态正常0,不正常-1
Others:         // 其它说明
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
Description:键盘事件处理函数
Calls:(none)
Input:SDL_KeyboardEvent* KeyEvent, //SDL键盘事件参数

Output:(none)
Return:(int)状态正常0,不正常-1
Others:         // 其它说明
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

