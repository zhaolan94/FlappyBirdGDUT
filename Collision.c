/*************************************************
Function:  isCol       // ��������
Description: Collision check    // �������ܡ����ܵȵ�����
Calls:(none)          // �����������õĺ����嵥
Input:int isCol(struct pos bird, struct pos upobs, struct pos dowobs, float wid(����), float edge���±߽磩, float s�����)          // �������
Output:��none��        // �����������˵��
Return:(int) 1->Collision      0->not collision        // ��������ֵ��˵��
Others:         // ����˵��
*************************************************/
#include <stdio.h>
#include <stdlib.h>

struct pos
{
    int x;
    int y;
    int wid;       //���ն���������Լ����
};
int isCol(struct pos bird, struct pos upobs, struct pos dowobs, int edge)
//     �ֱ����С�������ӣ������ӵ�λ�����꼰��ȣ��������µ�����
{
  if  (bird.y<=0)        //���ϱ߽�����ϲ���
    {
    //  printf("Hit UP Edge!");
      return 0;
    }
   else if (bird.y>=(edge-bird.wid)) //�±߽� ����
    {
        return 1;
    }
    else if (bird.y<=(upobs.y) && bird.x<=(upobs.x+upobs.wid) && bird.x>=(upobs.x-bird.wid))  //�������Ӽ��,��U��
    {
     return 1;
     }
    else if(bird.y>=(dowobs.y-bird.wid) && bird.x<=(dowobs.x+dowobs.wid) && bird.x>=(dowobs.x-bird.wid))  //�������Ӽ��,��n��
    {
        return 1;
    }
    else
    {
        return -1;
    }


}
