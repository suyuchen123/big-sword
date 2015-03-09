#include"Bulletset.h"
#include"VariableDefine.h"
BulletSet::BulletSet()
{
	int i;
	for(i=0;i<=19;i++)
	 occupy[i]=Bullettime[i]=0;
	BulletNum=0;
}
int BulletSet::reset()
{
	int i;
	for(i=0;i<=19;i++)
	 occupy[i]=Bullettime[i]=0;
	BulletNum=0;
	return 0;
}


int BulletSet::CreateNew(int x, int y,float txspeed,int Hurt)
{
   int i;
   for(i=0;i<=19;i++)
	   if(occupy[i]==0)
	   {
	    bullets[i].position.x=x;
	    bullets[i].position.y=y;
		bullets[i].xSpeed=txspeed;
		//暂时没有y方向
		bullets[i].hurt=Hurt;
		Bullettime[i]=0;
		occupy[i]=1;
		break;
	   }
	   return 1;
}
int BulletSet::CreateNew(BulletMsg& tmp)
{
   int i;
   for(i=0;i<=19;i++)
	   if(occupy[i]==0)
	   {
	    bullets[i]=tmp;
		Bullettime[i]=0;
		occupy[i]=1;
		break;
	   }
	   return 1;
}

void BulletSet::Refresh(Room& room1)
{
   int i;
  
   for(i=0;i<19;i++)
   {  
	    if(room1.showBlock(bullets[i].position.x,bullets[i].position.y)>0) 
					
						Disappear(i);
		if(bullets[i].weapon==Missle && room1.showBlock(bullets[i].position.x+MissleWide,bullets[i].position.y)>0)
			            Disappear(i);
					   //考虑加音效及其动画效果
					
	if(occupy[i])
	{
	  bullets[i].position.x+=bullets[i].xSpeed;
	  Bullettime[i]++;
	  if(Bullettime[i]>bullets[i].lifetime) Disappear(i);
	}
   }
}

void BulletSet::Disappear(int i)
{
	occupy[i]=0;
}


int BulletSet::singlecheck(Position tmp)//【2014 1.1 对于传入的怪物坐标进行所有子弹检测，并返回所有子弹造成的伤害总和】
{
	
	int i;
	int total=0;
	for(i=0;i<19;i++)
	{
		
		if(occupy[i]&& bullets[i].position.x>tmp.x && bullets[i].position.x<tmp.x+monsterWide
			&&bullets[i].position.y>tmp.y && bullets[i].position.y<tmp.y+monsterHight
			)
		{  if(bullets[i].weapon==Gun)Disappear(i);
		   total+=bullets[i].hurt;
		}
		
	}
   return total;
}
int BulletSet::exsit(int i)
{
 return occupy[i];
}

BulletMsg  BulletSet::GetOut(int i)
{
	return bullets[i];
}