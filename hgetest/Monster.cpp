#include<iostream>
#include"Monster.h"
#include"VariableDefine.h"
using namespace std;

Monster::Monster(int level_set)
{
	level=level_set;
}
Monster::Monster(int level_set,Position p)
{
	position.x=p.x;
	position.y=p.y;
	level=level_set;
}
Monster::Monster(int level_set,int x,int y)
{
	position.x=x;
	position.y=y;
	level=level_set;
}

void Monster::setHeight(int h)
{
	height=h;
}
void Monster::setWidth(int w)
{
	width=w;
}
void Monster::setSize(int h,int w)
{
	height=h;
	width=w;
}

Position Monster::showPosition()
{
	return position;
}

int Monster::showHeight()
{
	return height;
}

int Monster::showWidth()
{

	return width;
}

Position Monster::setPosition(Position p)
{
	position.x=p.x;
	position.y=p.y;
	return position;
}
Position Monster::setPosition(int x,int y)
{
	position.x=x;
	position.y=y;
	return position;
}

Position Monster::move(Direction direction)		//基本完成
{
	if(direction==Right){
		position.x=position.x+moveSpeed;
		faceDirection=Right;
	}
	if(direction==Left){
		position.x=position.x-moveSpeed;
		faceDirection=Left;
	}
	return position;
}

Position Monster::goBack(Direction direction)
{
	if(direction==Right)
		position.x=position.x+1;
	if(direction==Left)
		position.x=position.x-1;
	if(direction==Up)
		position.y=position.y-1;
	if(direction==Down)
		position.y=position.y+1;
	return position;
}

bool Monster::hurt(BulletMsg msg)
{
	if(msg.weapon==Gun){
		hp=hp-10;
	}
	if(msg.weapon==Missle){
		hp=hp-100;
	}
	if(hp<0)
		hp=0;
	if(hp==0){
		return 1;	//表示怪兽挂了
	}
	else
		return 0;	//表示怪兽还没挂
}
bool Monster::hurt(int k)
{
	hp=hp-k;
	if(hp<0)
		hp=0;
	if(hp==0)
		return 1;	//表示怪兽挂了
	else 
		return 0;	//表示怪兽没挂
}

int Monster::showHp()
{
	return hp;
}
void Monster::setHp(int hpp)
{
	hp=hpp;
}

Direction Monster::showFaceDirection()
{
	return faceDirection;
}

Slime::Slime(int level_set):Monster(level_set)
{

	height=120;		width=120;		fall=1;					inAirDirection=NoDirection;
	leapSpeed=250;	inAirTime=0;	faceDirection=Left;		centerNum=0;
	IQ=3;			inAirSpeed=2;	timer=0;
	int i;
	for(i=0;i<20;i++){
		mu[i]=1.2;
		sigma[i]=0.5;
		bayesWeight[i]=0;
	}
	if(level==1){hp=50;	moveSpeed=2;}
	if(level==2){hp=100;moveSpeed=2;}
	if(level==3){hp=50;	moveSpeed=3;}
	if(level==4){hp=100;moveSpeed=3;}
	if(level==5){hp=200;moveSpeed=4;}
	if(level==6){hp=50;	moveSpeed=4;}
	if(level==7){hp=150;moveSpeed=4;}
	if(level==8){hp=50;	moveSpeed=5;}
	if(level==9){hp=500;moveSpeed=4;}	
}

Slime::Slime(int level_set,Position p):Monster(level_set,p)
{
	height=120;		width=120;		fall=1;					inAirDirection=NoDirection;
	leapSpeed=250;	inAirTime=0;	faceDirection=Left;		centerNum=0;
	IQ=3;			inAirSpeed=1;	timer=0;
	int i;
	for(i=0;i<20;i++){
		mu[i]=1.2;
		sigma[i]=0.5;
		bayesWeight[i]=0;
	}
	if(level==1){hp=50;	moveSpeed=2;}
	if(level==2){hp=100;moveSpeed=2;}
	if(level==3){hp=50;	moveSpeed=3;}
	if(level==4){hp=100;moveSpeed=3;}
	if(level==5){hp=200;moveSpeed=3;}
	if(level==6){hp=50;	moveSpeed=4;}
	if(level==7){hp=150;moveSpeed=4;}
	if(level==8){hp=50;	moveSpeed=5;}
	if(level==9){hp=500;moveSpeed=4;}	
}
Slime::Slime(int level_set,int x,int y):Monster(level_set,x,y)
{
	height=75;		width=75;		fall=1;					inAirDirection=NoDirection;
	leapSpeed=250;	inAirTime=0;	faceDirection=Left;		centerNum=0;	
	IQ=3;			inAirSpeed=2;	timer=0;
	int i;
	for(i=0;i<20;i++){
		mu[i]=1.2;
		sigma[i]=0.5;
		bayesWeight[i]=0;
	}
	if(level==1){hp=50;	moveSpeed=2;}
	if(level==2){hp=100;moveSpeed=2;}
	if(level==3){hp=50;	moveSpeed=3;}
	if(level==4){hp=100;moveSpeed=3;}
	if(level==5){hp=200;moveSpeed=3;}
	if(level==6){hp=50;	moveSpeed=4;}
	if(level==7){hp=150;moveSpeed=4;}
	if(level==8){hp=50;	moveSpeed=5;}
	if(level==9){hp=500;moveSpeed=4;}	
}

bool Slime::leap()
{
	if(fall==0){
		fall=1;
		inAirTime=0;
		inAirDirection=Up;
		return 1;
	}
	else
		return 0;
}

bool Slime::leap(Direction direction)
{
	if(fall==0){
		if(direction==Right){
			fall=1;
			inAirTime=0;
			inAirDirection=Right;
			faceDirection=Right;
			return 1;
		}
		if(direction==Left){
			fall=1;
			inAirTime=0;
			inAirDirection=Left;
			faceDirection=Left;
			return 1;
		}
		else{
			fall=1;
			inAirTime=0;
			inAirDirection=Up;
			return 1;
		}
	}
	else
		return 0;
}

bool Slime::checkFall()
{
	return fall;
}

	
Position Slime::Fall(float dt)
{
	float dx,dy;  
	inAirTime=inAirTime+dt;
	dy=(-leapSpeed+3*g*inAirTime)*dt;
	position.y=position.y+dy;
	return position;
}

Position Slime::stopFall()
{
	fall=0;
	inAirTime=0;
	return position;
}

void Slime::startFall()
{
	fall=1;
	inAirTime=leapSpeed/g;		//将时间调成速度正好为0的那个时刻，以实现初始速度为0
}


void Slime::hitCell()
{
	inAirTime=leapSpeed/g;		//将时间调成速度正好为0的那个时刻，以实现撞到天花板速度归0	
}

bool Slime::checkRange(Position center)
{
	if((position.x<center.x+200)&&(position.x>center.x-200)&&(position.y<center.y+50)&&(position.y>center.y-50))
		return 1;
	else
		return 0;
}

void Slime::behave(Room& room,Hero& hero,float dt)
{
	Decision decision;
	Position p;
	Direction tempDirection;

	p=hero.showPosition();
	//怪兽根据信息做出决策
	if(IQ==0){				//没智商的傻逼怪物：傻站着
		//什么也不做
	}
	if(IQ==1)			    //智商低下的怪物：左右巡逻，不会跳跃
	{
		if(faceDirection==Left){
			decision=MoveLeft;
		}
		if(faceDirection==Right){
			decision=MoveRight;
		}

		if(this->checkFall()==1){					//如果怪兽在下落状态，根据是否碰撞作出相应调整
			decision=Stop;
			this->Fall(dt);							//先向下掉
			if((room.checkCollision(position,height,width)==DownCollision)||(room.checkCollision(position,height,width)==LeftDownCollision)||
				(room.checkCollision(position,height,width)==RightDownCollision)){
					this->stopFall();					//撞到地面，停止下落
					while(room.checkCollision(position,height,width)){
						this->goBack(Up);				//可能撞到地面里面去了，把怪兽拔上来
					}
			}
			else if((room.checkCollision(position,height,width)==UpCollision)||(room.checkCollision(position,height,width)==LeftUpCollision)||
				(room.checkCollision(position,height,width)==RightUpCollision)){
					this->hitCell();					//撞到天花板，速度调0，开始自由落体
					while(room.checkCollision(position,height,width)){
						this->goBack(Down);				//如果撞到天花板里面去，把史莱姆拔出来
					}
			}
		}
		else{								//如果没有下落，检查史莱姆是否踩空，从高台上掉下来
			this->goBack(Down);				//试着先向下走一格
			if((room.checkCollision(position,height,width)!=DownCollision)&&(room.checkCollision(position,height,width)!=LeftDownCollision)&&
				(room.checkCollision(position,height,width)!=RightDownCollision)){
					this->startFall();			//如果下面没阻挡，就开始掉落
			}
			this->goBack(Up);				//向上走一格补偿一开始向下走的一格
		}
		switch(decision){
		case MoveLeft:
			this->move(Left);
			while((room.checkCollision(position,height,width)==LeftCollision)||(room.checkCollision(position,height,width)==LeftUpCollision)
				||(room.checkCollision(position,height,width)==LeftDownCollision)){
					this->goBack(Right);		//如果撞到左边墙里面，把史莱姆向右拔出来
					faceDirection=Right;		//撞到左边的墙后决定向右走
			}
			break;
		case MoveRight:
			this->move(Right);
			while((room.checkCollision(position,height,width)==RightCollision)||(room.checkCollision(position,height,width)==RightUpCollision)
				||(room.checkCollision(position,height,width)==RightDownCollision)){
					this->goBack(Left);			//如果撞到右边墙里面，把史莱姆向左拔出来
					faceDirection=Left;			//撞到右边的墙后决定向左走
			}
			break;
		case Stop:
			break;
		default:
			break;
		} 
	}

	if (IQ==2)						//智商较高的怪物：根据英雄的位置进行移动，会竖直跳跃，但不会爬台阶
	{
		
		if(this->position.x>p.x+hero.showWidth()/2)
			decision=MoveLeft;
		else if(this->position.x<p.x-this->width/2)
			decision=MoveRight;
		else if(this->position.y>p.y+hero.showHeight())
			decision=Leap;
		else
			decision=Stop;

		if(this->checkFall()==1){					//如果怪兽在下落状态，根据是否碰撞作出相应调整
			decision=Stop;
			this->Fall(dt);							//先向下掉
			if((room.checkCollision(position,height,width)==DownCollision)||(room.checkCollision(position,height,width)==LeftDownCollision)||
				(room.checkCollision(position,height,width)==RightDownCollision)){
					this->stopFall();					//撞到地面，停止下落
					while(room.checkCollision(position,height,width)){
						this->goBack(Up);				//可能撞到地面里面去了，把怪兽拔上来
					}
			}
			else if((room.checkCollision(position,height,width)==UpCollision)||(room.checkCollision(position,height,width)==LeftUpCollision)||
				(room.checkCollision(position,height,width)==RightUpCollision)){
					this->hitCell();					//撞到天花板，速度调0，开始自由落体
					while(room.checkCollision(position,height,width)){
						this->goBack(Down);				//如果撞到天花板里面去，把史莱姆拔出来
					}
			}
		}
		else{								//如果没有下落，检查史莱姆是否踩空，从高台上掉下来
			this->goBack(Down);				//试着先向下走一格
			if((room.checkCollision(position,height,width)!=DownCollision)&&(room.checkCollision(position,height,width)!=LeftDownCollision)&&
				(room.checkCollision(position,height,width)!=RightDownCollision)){
					this->startFall();			//如果下面没阻挡，就开始掉落
			}
			this->goBack(Up);				//向上走一格补偿一开始向下走的一格
		}
		switch(decision){
		case MoveLeft:
			this->move(Left);
			while((room.checkCollision(position,height,width)==LeftCollision)||(room.checkCollision(position,height,width)==LeftUpCollision)
				||(room.checkCollision(position,height,width)==LeftDownCollision)){
					this->goBack(Right);		//如果撞到左边墙里面，把史莱姆向右拔出来
			}
			break;
		case MoveRight:
			this->move(Right);
			while((room.checkCollision(position,height,width)==RightCollision)||(room.checkCollision(position,height,width)==RightUpCollision)
				||(room.checkCollision(position,height,width)==RightDownCollision)){
					this->goBack(Left);			//如果撞到右边墙里面，把史莱姆向左拔出来
			}
			break;
		case Leap:
			if(checkFall()==0){
				leap();						//收到跳跃信号，开始跳跃
			}
			break;
		case Stop:
			break;
		default:
			break;
		} 
	}

	if(IQ==3){			//智商和苏雨辰一样高的史莱姆：根据英雄的位置进行移动，会跳上台阶。
		int heroFoot=p.y+hero.showHeight();
		int heroHead=p.y;
		int slimeFoot=position.y+height;
		int slimeHead=position.y;
		
		if((heroFoot<slimeFoot+20)&&(heroFoot>slimeFoot-20)){
			if(this->position.x>p.x+hero.showWidth()/2)
				decision=MoveLeft;
			else if(this->position.x<p.x-this->width/2)
				decision=MoveRight;
			else
				decision=Stop;
			//可能中间有空隙
		}
		else if(heroFoot<=slimeFoot-20){		//英雄的脚比史莱姆的头还要高,史莱姆寻路向上找英雄
			if(faceDirection==Left){		    //正常情况下左右寻路
				decision=MoveLeft;
			}
			if(faceDirection==Right){
				decision=MoveRight;
			}			
			//遇到障碍，跳跃走上平台
			if(position.x>40){				//查看左边是否有能跳上去的平台
				tempDirection=faceDirection;
				this->move(Left);			
				if((room.checkCollision(position,height,width)==LeftCollision)||(room.checkCollision(position,height,width)==LeftUpCollision)
				||(room.checkCollision(position,height,width)==LeftDownCollision)){
					decision=LeapLeft;
				}
				this->move(Right);
				faceDirection=tempDirection;
			}
			if(position.x<760-width){
				tempDirection=faceDirection;
				this->move(Right);			//查看右边是否有能跳上去的平台
				if((room.checkCollision(position,height,width)==RightCollision)||(room.checkCollision(position,height,width)==RightUpCollision)
					||(room.checkCollision(position,height,width)==RightDownCollision)){
						decision=LeapRight;
				}
				this->move(Left);
				faceDirection=tempDirection;
			}
		}
		else if(heroFoot>slimeFoot+20){
			if(faceDirection==Left){
				decision=MoveLeft;
			}
			if(faceDirection==Right){
				decision=MoveRight;
			}
		}
		else
			decision=Stop;

		if(heroFoot<slimeFoot-20){
			if(checkFall()==0){
				timer=timer+dt;
				//出结果再惩罚！
				//记录信息
				int i;
				for(i=0;i<centerNum;i++){
					if(checkRange(bayesCenter[i])==1)
						break;
				}
				if(i==centerNum){
					centerNum++;
					bayesCenter[i]=position;
				}
				if(record!=i){
					timer=0;
					rv=9999;
				}
				record=i;
				timer=timer+dt;
				if(rv>1000){
					rv=gaussrand();
					rv=gaussrand()*sigma[i]+mu[i];
				}
				if(timer>rv){
					if(faceDirection==Left){
						decision=LeapLeft;
					}
					if(faceDirection==Right){
						decision=LeapRight;
					}
					hRecord=position.y;
					tRecord=timer;
					rv=500;
				}
			}
		}
				
		if(this->checkFall()==1){					//如果怪兽在下落状态，根据是否碰撞作出相应调整
			decision=Stop;
			this->Fall(dt);							//先向下掉
			if((room.checkCollision(position,height-1,width-1)==DownCollision)||(room.checkCollision(position,height-1,width-1)==LeftDownCollision)||
				(room.checkCollision(position,height-1,width-1)==RightDownCollision)){
					this->stopFall();					//撞到地面，停止下落
					if(hypothesis==1){
						hypothesis=0;
						if(hRecord>position.y+40){     //落下来的位置比原来高
							//激励
							mu[record]=(tRecord+mu[record]*bayesWeight[record])/(1+bayesWeight[record]);
							sigma[record]=sigma[record]/4;
							bayesWeight[record]++;
							record=8888;
							rv=9999;
							hRecord=0;
						}
						else{
							//惩罚
							hRecord=0;
						}
					}
					inAirDirection=NoDirection;

					while(room.checkCollision(position,height,width)){
						this->goBack(Up);				//可能撞到地面里面去了，把怪兽拔上来
					}
			}
			else if((room.checkCollision(position,height,width)==UpCollision)||(room.checkCollision(position,height,width)==LeftUpCollision)||
				(room.checkCollision(position,height,width)==RightUpCollision)){
					this->hitCell();					//撞到天花板，速度调0，开始自由落体
					while(room.checkCollision(position,height,width)){
						this->goBack(Down);				//如果撞到天花板里面去，把史莱姆拔出来
					}
			}
			if(inAirDirection==Left){
				position.x=position.x-inAirSpeed;
				while((room.checkCollision(position,height,width)==LeftCollision)||(room.checkCollision(position,height,width)==LeftUpCollision)
				||(room.checkCollision(position,height,width)==LeftDownCollision)){
					this->goBack(Right);		//如果撞到左边墙里面，把史莱姆向右拔出来
				//	inAirDirection=Up;
				}
			}
			if(inAirDirection==Right){
				position.x=position.x+inAirSpeed;
				while((room.checkCollision(position,height,width)==RightCollision)||(room.checkCollision(position,height,width)==RightUpCollision)
				||(room.checkCollision(position,height,width)==RightDownCollision)){
					this->goBack(Left);			//如果撞到右边墙里面，把史莱姆向左拔出来
				//	inAirDirection=Up;
				}
			}
		}
		else{								//如果没有下落，检查史莱姆是否踩空，从高台上掉下来
			this->goBack(Down);				//试着先向下走一格
			if((room.checkCollision(position,height,width)!=DownCollision)&&(room.checkCollision(position,height,width)!=LeftDownCollision)&&
				(room.checkCollision(position,height,width)!=RightDownCollision)){
					this->startFall();		//如果下面没阻挡，就开始掉落
			}
			this->goBack(Up);				//向上走一格补偿一开始向下走的一格
		}
		switch(decision){
		case MoveLeft:
			this->move(Left);
			while((room.checkCollision(position,height,width)==LeftCollision)||(room.checkCollision(position,height,width)==LeftUpCollision)
				||(room.checkCollision(position,height,width)==LeftDownCollision)){
					this->goBack(Right);		//如果撞到左边墙里面，把史莱姆向右拔出来
					faceDirection=Right;		//撞到左边的墙后决定向右走
			}
			break;
		case MoveRight:
			this->move(Right);
			while((room.checkCollision(position,height,width)==RightCollision)||(room.checkCollision(position,height,width)==RightUpCollision)
				||(room.checkCollision(position,height,width)==RightDownCollision)){
					this->goBack(Left);			//如果撞到右边墙里面，把史莱姆向左拔出来
					faceDirection=Left;		//撞到右边的墙后决定向左走
			}
			break;
		case Leap:
			if(checkFall()==0){
				leap();						//收到跳跃信号，开始跳跃
			}
			break;
		case LeapLeft:
			if(checkFall()==0){
				leap(Left);					
			}
			break;
		case LeapRight:
			if(checkFall()==0){
				leap(Right);
			}
			break;
		case Stop:
			break;
		default:
			break;
		} 
	}
}