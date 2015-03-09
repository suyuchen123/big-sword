#include"Hero.h"
#include"VariableDefine.h"

Hero::Hero()
{   
	hp=100;
	position.x=100;
	position.y=100;
	moveSpeed=6;
	airTime=0;onFloor=1;
	weapon=Gun;
	width=41;
	height=100;

}

int Hero::reset()
{   
	hp=100;
	position.x=100;
	position.y=100;
	moveSpeed=6;
	airTime=0;onFloor=1;
	weapon=Gun;
	return 0;
}
int Hero::showHeight()
{
	return height;
}
int Hero::showWidth()
{
	return width;
}
Position Hero::showPosition()
{
	return position;
}

void Hero::changeWeapon(int dir)		//ok
{
  if (dir==1) weapon=Gun;
  else weapon=Missle;
}

Weapon Hero::showWeapon()
{
	return weapon;
}

void Hero::move(Direction dir)
{
	switch(dir)
	{
		case Left:  faceDirection=1;  position.x-=moveSpeed;  break;
		case Right: faceDirection=0;  position.x+=moveSpeed;  break;
    }
}
int Hero::checkFloor()
{
	return onFloor;
}

int Hero::checkMove(Direction dir)
{
	return 0;
}

Direction Hero::checkFace()
{
	if (faceDirection==0) return Right;
	else  return Left;
}

int Hero::checkFaceresult()
{
	if(beforeface!=faceDirection) 
	{
		beforeface=faceDirection;
		return 1;
	}
	return 0;
}


void Hero::inAir(float bornSpeed,Direction dir,int Block)
{
  if(airTime==0 && Block!=1)
  {
	leapSpeed=bornSpeed;
	airTime+=dt;
	onFloor=0;
	position.y=position.y-1*(airTime==0);
	float dy=-leapSpeed+g*airTime;
    position.y=position.y+dy;
  }
  else
  {   
	  move(dir);
	  airTime+=dt;
	  float b=-leapSpeed*airTime+(g/2*(airTime*airTime));
	  if(b<0 && Block==1) {airTime=0; leapSpeed=0;return;}
	  position.y+=-leapSpeed*airTime+(g/2*(airTime*airTime));
	  
	  
  }
}

int Hero::stopAir()//回到地面，或者说清空腾空数据
{
  airTime=0;
  onFloor=1;
  position.y=int(position.y)/50*50+12;
  return 0;
}

BulletMsg Hero::attack()// 12.29 苏畅， 根据英雄的武器生成子弹 传出
{   
	BulletMsg tmp;


	  if (weapon==Gun){
	    tmp.hurt=50;
		tmp.weapon=Gun;
	     tmp.lifetime=30;
	    tmp.position.x=position.x;
	    tmp.position.y=position.y+50;
	    if(faceDirection==0) tmp.xSpeed=10;
	     else tmp.xSpeed=-10;

	   }else
	  {
		tmp.weapon=Missle;
		 tmp.hurt=40;
	     tmp.lifetime=300;
	     tmp.position.x=position.x;
	    tmp.position.y=position.y+50;
	     if(faceDirection==0) tmp.xSpeed=7;
		 else tmp.xSpeed=-7;
	   }


	return tmp;

}

int Hero::hurt(int num)
{
	hp-=num;
	if(hp<=0) hp=0;
	if(num>0) return 1; else return 0;
}
int Hero::death()
{
	if(hp<=0)
		return 1;
	else return 0;

}

/*void Hero::setSpeed(int speed,Position pos)
{
	position=pos;
	moveSpeed=speed;
	onFloor=1;
	airTime=0;
}*/