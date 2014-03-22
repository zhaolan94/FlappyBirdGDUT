/*************************************************
Function:  isCol       // 函数名称
Description: Collision check    // 函数功能、性能等的描述
Calls:(none)          // 被本函数调用的函数清单
Input:int isCol(struct pos bird, struct pos upobs, struct pos dowobs, float wid(柱宽), float edge（下边界）, float s（鸟宽）)          // 输入参数
Output:（none）        // 对输出参数的说明
Return:(int) 1->Collision      0->not collision        // 函数返回值的说明
Others:         // 其它说明
*************************************************/
#include <stdio.h>
#include <stdlib.h>

struct pos
{
    int x;
    int y;
    int wid;       //接收对象的坐标以及宽度
};
int isCol(struct pos bird, struct pos upobs, struct pos dowobs, int edge)
//     分别接收小鸟。上柱子，下柱子的位置坐标及宽度，界面最下的坐标
{
  if  (bird.y<=0)        //在上边界或以上不死
    {
    //  printf("Hit UP Edge!");
      return 0;
    }
   else if (bird.y>=(edge-bird.wid)) //下边界 死掉
    {
        return 1;
    }
    else if (bird.y<=(upobs.y) && bird.x<=(upobs.x+upobs.wid) && bird.x>=(upobs.x-bird.wid))  //上面柱子检测,呈U型
    {
     return 1;
     }
    else if(bird.y>=(dowobs.y-bird.wid) && bird.x<=(dowobs.x+dowobs.wid) && bird.x>=(dowobs.x-bird.wid))  //下面柱子检测,呈n型
    {
        return 1;
    }
    else
    {
        return -1;
    }


}
