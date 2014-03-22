/*************************************************
Function:  isCol       // ��������
Description: Collision check    // �������ܡ����ܵȵ�����
Calls:(none)          // �����������õĺ����嵥
Input:int isCol(struct pos bird, struct pos upobs, struct pos dowobs, float wid(����), float edge���±߽磩, float s�����)          // �������
Output:��none��        // �����������˵��
Return:(int) 1->Collision      0->not collision        // ��������ֵ��˵��
Others:         // ����˵��
*************************************************/
#ifndef COLLISION_H_INCLUDED

#define COLLISION_H_INCLUDED
struct pos
{
    int x;
    int y;
    int wid;       //���ն���������Լ����
} bird,upobs,dowobs;
int isCol(struct pos bird, struct pos upobs, struct pos dowobs, int edge);//��������
#endif // DRAWING_H_INCLUDED
