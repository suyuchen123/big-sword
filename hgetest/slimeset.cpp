#include"Slimeset.h"
#include"VariableDefine.h"
#include<math.h>
using namespace std;
SlimeSet::SlimeSet()
{
	KillNumber=0;
	SlimeNum=0;
	int i;
	for(i=0;i<10;i++)
		occupy[i]=0;
}

int SlimeSet::reset()
{KillNumber=0;
	SlimeNum=0;
	int i;
	for(i=0;i<10;i++)
		occupy[i]=0;
	return 0;
}


int SlimeSet::Init()
{
	KillNumber=0;
	SlimeNum=0;
	int i;
	for(i=0;i<10;i++)
		occupy[i]=0;
	return 0;
}
void SlimeSet::Disappear(int i)
{      KillNumber++;
	   SlimeNum--;
	   occupy[i]=0;
}
Position SlimeSet::BulletCheck(BulletSet& bullets)//传出值为这一贞 死掉的怪物的坐标，用于物品生成额 在怪物死亡处出现药
{
	int i=10;
	int totalhurt;
	Position returnpos;
	returnpos.x=0;returnpos.y=0;
	for(i=0;i<10;i++)
	{
		if(occupy[i])
		{
			totalhurt=bullets.singlecheck(slimes[i].showPosition());//singlecheck 传出子弹对于怪兽的总伤害值
			slimes[i].hurt(totalhurt);
			if(slimes[i].showHp()==0) 
				{returnpos=slimes[i].showPosition();
			     Disappear(i);
				 
			}

			
		}
	}
	return returnpos;
}
void SlimeSet::Refresh(Room& room,Hero& hero, float dt)
{
	int i;
	for(i=0;i<10;i++)
		if(occupy[i]) slimes[i].behave( room, hero, dt);
}

void SlimeSet::CreateNew()
{
	int i;
	if(SlimeNum<(KillNumber/10+1))
	{
	for(i=1;i<10;i++)
	{
		if(!occupy[i])
		{
		   occupy[i]=1;
		   SlimeNum++;
		   /*slimes[i].height=monsterHight;		slimes[i].width=monsterWide;		slimes[i].fall=1;	   
	        slimes[i].leapSpeed=200;	slimes[i].inAirTime=0;	slimes[i].faceDirection=Left;
			slimes[i].level=3;slimes[i].hp=50;slimes[i].moveSpeed=3;
			slimes[i].position.x=401; slimes[i].position.y=500;*/

	 	   slimes[i].height=50;		 slimes[i].width=50;		 slimes[i].fall=1;					 slimes[i].inAirDirection=NoDirection;
	 	   	 slimes[i].inAirTime=0;		 slimes[i].faceDirection=Left;		 slimes[i].centerNum=0;
	       slimes[i].IQ=3;				 slimes[i].timer=0;
		   slimes[i].level=3;					 
		   slimes[i].position.x=20; slimes[i].position.y=100;	 slimes[i].record=0;
		   slimes[i].hp=50*((KillNumber/10)+1);

		   slimes[i].moveSpeed=4; slimes[i].inAirSpeed=2+KillNumber/10;slimes[i].leapSpeed=300; 
	      int j;
	   for(j=0;j<100;j++){
			slimes[i].mu[j]=0.2;
			slimes[i].sigma[j]=1;
			slimes[i].bayesWeight[j]=0;
		}
			break;
		}
	}
	}
}
void SlimeSet::Add()
{
	while(SlimeNum<(KillNumber/10+1))

	{
		CreateNew();
	}
}

Position SlimeSet:: PosForRender(int i)
{
	return slimes[i].showPosition();
}
int SlimeSet::ExistForRender(int i)
	{
		return occupy[i];
	}
int SlimeSet::HurtHero(Position& pos)
{
	int i;
	int totalHurt=0;
	pos.x+=heroWide/2;
	pos.y+=heroHight/2;//求出英雄的中心坐标
    int widelimit,heightlimit;
	widelimit=(heroWide+monsterWide)/2;
	heightlimit=(heroHight+monsterHight)/2;
	for(i=0;i<10;i++)
	{
		if(occupy[i])
		{
			if(abs(pos.x-(slimes[i].position.x+monsterWide/2))<widelimit-20 && abs(pos.y-(slimes[i].position.y+monsterHight))<heightlimit-30)
			 totalHurt+=slimes[i].level*10;
		}
	}
	return totalHurt;
}

Direction SlimeSet::checkface(int i)
{
	return slimes[i].showFaceDirection();
}