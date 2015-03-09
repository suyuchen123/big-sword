#include<iostream>
#include<fstream>
#include "VariableDefine.h"
#include"Room.h"
using namespace std;
int Room::set(const char *filename)
{
	ifstream in(filename);
	for(int i=0;i<12;i++)// load 50 *50 back ground background
	for(int j=0;j<16;j++)
	{
	 in>>block[i][j];
	}
	/* 此处可处理地图事件
	for(i=1;i<= 
   */
	in.close();
	return 0;
}
BlockType Room::showBlock(Position p)
{
	return showBlock(p.x,p.y);
}
BlockType Room::showBlock(int x,int y)
{
	if(x<0||y<0||y>600||x>800) return Solid1;
    switch(block[y/50][x/50])
    {
	    case 0:return Air;   break;
	    case 1:return Solid1;break;
        case 2:return Solid2;break;
	    case 3:return Solid3;break;
		case 4:return Solid4;break;
		

   }
}

void Room::setMonstetNumber(int i)
{
	monsterNumber=i;
}

int Room::showMonsterNumber()
{
	return monsterNumber;
}

Position showBlockCoordinate(int i,int j)
{
	Position p;
	if((i<12)&&(i>=0)&&(j<16)&&(j>=0)){
		p.x=j*50;
		p.y=i*50;
	}
	else{
		cout<<"地图Block数组溢出！"<<endl;
	}
	return p;
}
/*
CollisionType Room::checkCollision(Monster& monster)
{
	Position p=monster.showPosition();
	bool leftUp,leftDown,rightUp,rightDown;
	leftUp=0;  leftDown=0;
	rightUp=0; rightDown=0;
	//检查4个角
	if(showBlock(p)!=Air){			//检查左上角
		leftUp=1;
	}
	p.x=p.x+monster.showWidth();
	if(showBlock(p)!=Air){			//检查右上角
		rightUp=1;
	}
	p.y=p.y+monster.showHeight();
	if(showBlock(p)!=Air){			//检查右下角 
		rightDown=1;
	}
	p.x=p.x-monster.showWidth();
	if(showBlock(p)!=Air){			//检查左下角
		leftDown=1;
	}
	//判断哪条边发生了碰撞并返回
	if((leftDown==1)&&(leftUp==1)){
		return LeftCollision;
	}
	if((rightUp==1)&&(rightDown==1)){
		return RightCollision;
	}
	if((leftUp==1)&&(rightUp==1)){
		return UpCollision;
	}
	if((leftDown==1)&&(rightDown==1)){
		return DownCollision;
	}
	if((leftDown==1)&&(rightDown!=1)&&(leftUp!=1)){
		return LeftDownCollision;
	}
	if((leftUp==1)&&(leftDown!=1)&&(rightUp!=1)){
		return LeftUpCollision;
	}
	if((rightUp==1)&&(leftUp!=1)&&(rightDown==1)){
		return RightUpCollision;
	}
	if((rightDown==1)&&(rightUp!=1)&&(leftDown==1)){
		return RightDownCollision;
	}
	return NoCollision;
}
*/
CollisionType Room::checkCollision(Position p,int height,int width)
{
	bool leftUp,leftDown,rightUp,rightDown;
	leftUp=0;  leftDown=0;
	rightUp=0; rightDown=0;
	//检查4个角
	if(showBlock(p)!=Air){			//检查左上角
		leftUp=1;
	}
	p.x=p.x+width;
	if(showBlock(p)!=Air){			//检查右上角
		rightUp=1;
	}
	p.y=p.y+height;
	if(showBlock(p)!=Air){			//检查右下角 
		rightDown=1;
	}
	p.x=p.x-width;
	if(showBlock(p)!=Air){			//检查左下角
		leftDown=1;
	}
	//判断哪条边发生了碰撞并返回
	if((leftDown==1)&&(rightDown!=1)&&(leftUp!=1)){
		return LeftDownCollision;
	}
	if((leftUp==1)&&(leftDown!=1)&&(rightUp!=1)){
		return LeftUpCollision;
	}
	if((rightUp==1)&&(leftUp!=1)&&(rightDown!=1)){
		return RightUpCollision;
	}
	if((rightDown==1)&&(rightUp!=1)&&(leftDown!=1)){
		return RightDownCollision;
	}
	if((leftDown==1)&&(leftUp==1)){
		return LeftCollision;
	}
	if((rightDown==1)&&(rightUp==1)){
		return RightCollision;
	}
	if((leftUp==1)&&(rightUp==1)){
		return UpCollision;
	}
	if((leftDown==1)&&(rightDown==1)){
		return DownCollision;
	}
	return NoCollision;
}

