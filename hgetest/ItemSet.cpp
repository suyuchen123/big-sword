#include"Itemset.h"
#include"VariableDefine.h"
#include<math.h>
#include <hge.h> 
extern HGE* pHge;
//using namespace std;
ItemSet::ItemSet()
{
  int i;
  for(i=0;i<3;i++)
 {
  occupy[i]=0;
  existtime[i]=0;
 }
 disappeartime=1000;
 nowNum=0;
// ItemWide=50;这两个扔variabledefine.h里面了
// ItemHeight=50;
 addHp=20;

}

int ItemSet::reset()
{
  int i;
  for(i=0;i<3;i++)
 {
  occupy[i]=0;
  existtime[i]=0;
 }
 disappeartime=1000;
 nowNum=0;
// ItemWide=50;这两个扔variabledefine.h里面了
// ItemHeight=50;
 addHp=20;
 return 0;

}




void ItemSet::Refresh()
	{
		int i;
		for(i=0;i<3;i++)
		{ 
		 if(occupy[i])
		 {
			existtime[i]++;
			if(existtime[i]>disappeartime)
				Disappear(i);
		 }
		}
	}
	void ItemSet::CreatNew(Position& tmp)
	{
	    int i;
		pHge->Random_Seed();
		int radom=pHge->Random_Int(0,2);
		if(radom==0)
		{
		  if(nowNum<ItemNum )
		   {
		
		    for(i=0;i<3;i++)
			  if(!occupy[i])
			   {
				 existtime[i]=0;
		        position[i]=tmp;
				occupy[i]=1;
				nowNum++;
				break;
			   }
		    }
		}
	}
	void ItemSet::Disappear(int i)
	{
		occupy[i]=0;
		nowNum--;
	}
	int ItemSet::Add(Position pos)
	{
	    int i;
	    int totalAdd=0;
	    pos.x+=heroWide/2;
	   pos.y+=heroHight/2;//求出英雄的中心坐标
    int widelimit,heightlimit;
	widelimit=(heroWide+ItemWide)/2;
	heightlimit=(heroHight+ItemHeight)/2;
	for(i=0;i<ItemNum;i++)
	{
		if(occupy[i])
		{
			if(abs(pos.x-(position[i].x+ItemWide/2))<widelimit-20 && abs(pos.y-(position[i].y+ItemHeight))<heightlimit-30)
			{ totalAdd+=addHp;
			Disappear(i);}
		}
	}
	return totalAdd;


	}


