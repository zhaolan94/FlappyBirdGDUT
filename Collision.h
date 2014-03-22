/*************************************************
Function:  isCol       // 函数名称
Description: Collision check    // 函数功能、性能等的描述
Calls:(none)          // 被本函数调用的函数清单
Input:int isCol(struct pos bird, struct pos upobs, struct pos dowobs, float wid(柱宽), float edge（下边界）, float s（鸟宽）)          // 输入参数
Output:（none）        // 对输出参数的说明
Return:(int) 1->Collision      0->not collision        // 函数返回值的说明
Others:         // 其它说明
*************************************************/
#ifndef COLLISION_H_INCLUDED

#define COLLISION_H_INCLUDED
struct pos
{
    int x;
    int y;
    int wid;       //接收对象的坐标以及宽度
} bird,upobs,dowobs;
int isCol(struct pos bird, struct pos upobs, struct pos dowobs, int edge);//函数声明
#endif // DRAWING_H_INCLUDED
