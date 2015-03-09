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

Position Monster::move(Direction direction)		//�������
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
		return 1;	//��ʾ���޹���
	}
	else
		return 0;	//��ʾ���޻�û��
}
bool Monster::hurt(int k)
{
	hp=hp-k;
	if(hp<0)
		hp=0;
	if(hp==0)
		return 1;	//��ʾ���޹���
	else 
		return 0;	//��ʾ����û��
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
	inAirTime=leapSpeed/g;		//��ʱ������ٶ�����Ϊ0���Ǹ�ʱ�̣���ʵ�ֳ�ʼ�ٶ�Ϊ0
}


void Slime::hitCell()
{
	inAirTime=leapSpeed/g;		//��ʱ������ٶ�����Ϊ0���Ǹ�ʱ�̣���ʵ��ײ���컨���ٶȹ�0	
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
	//���޸�����Ϣ��������
	if(IQ==0){				//û���̵�ɵ�ƹ��ɵվ��
		//ʲôҲ����
	}
	if(IQ==1)			    //���̵��µĹ������Ѳ�ߣ�������Ծ
	{
		if(faceDirection==Left){
			decision=MoveLeft;
		}
		if(faceDirection==Right){
			decision=MoveRight;
		}

		if(this->checkFall()==1){					//�������������״̬�������Ƿ���ײ������Ӧ����
			decision=Stop;
			this->Fall(dt);							//�����µ�
			if((room.checkCollision(position,height,width)==DownCollision)||(room.checkCollision(position,height,width)==LeftDownCollision)||
				(room.checkCollision(position,height,width)==RightDownCollision)){
					this->stopFall();					//ײ�����棬ֹͣ����
					while(room.checkCollision(position,height,width)){
						this->goBack(Up);				//����ײ����������ȥ�ˣ��ѹ��ް�����
					}
			}
			else if((room.checkCollision(position,height,width)==UpCollision)||(room.checkCollision(position,height,width)==LeftUpCollision)||
				(room.checkCollision(position,height,width)==RightUpCollision)){
					this->hitCell();					//ײ���컨�壬�ٶȵ�0����ʼ��������
					while(room.checkCollision(position,height,width)){
						this->goBack(Down);				//���ײ���컨������ȥ����ʷ��ķ�γ���
					}
			}
		}
		else{								//���û�����䣬���ʷ��ķ�Ƿ�ȿգ��Ӹ�̨�ϵ�����
			this->goBack(Down);				//������������һ��
			if((room.checkCollision(position,height,width)!=DownCollision)&&(room.checkCollision(position,height,width)!=LeftDownCollision)&&
				(room.checkCollision(position,height,width)!=RightDownCollision)){
					this->startFall();			//�������û�赲���Ϳ�ʼ����
			}
			this->goBack(Up);				//������һ�񲹳�һ��ʼ�����ߵ�һ��
		}
		switch(decision){
		case MoveLeft:
			this->move(Left);
			while((room.checkCollision(position,height,width)==LeftCollision)||(room.checkCollision(position,height,width)==LeftUpCollision)
				||(room.checkCollision(position,height,width)==LeftDownCollision)){
					this->goBack(Right);		//���ײ�����ǽ���棬��ʷ��ķ���Ұγ���
					faceDirection=Right;		//ײ����ߵ�ǽ�����������
			}
			break;
		case MoveRight:
			this->move(Right);
			while((room.checkCollision(position,height,width)==RightCollision)||(room.checkCollision(position,height,width)==RightUpCollision)
				||(room.checkCollision(position,height,width)==RightDownCollision)){
					this->goBack(Left);			//���ײ���ұ�ǽ���棬��ʷ��ķ����γ���
					faceDirection=Left;			//ײ���ұߵ�ǽ�����������
			}
			break;
		case Stop:
			break;
		default:
			break;
		} 
	}

	if (IQ==2)						//���̽ϸߵĹ������Ӣ�۵�λ�ý����ƶ�������ֱ��Ծ����������̨��
	{
		
		if(this->position.x>p.x+hero.showWidth()/2)
			decision=MoveLeft;
		else if(this->position.x<p.x-this->width/2)
			decision=MoveRight;
		else if(this->position.y>p.y+hero.showHeight())
			decision=Leap;
		else
			decision=Stop;

		if(this->checkFall()==1){					//�������������״̬�������Ƿ���ײ������Ӧ����
			decision=Stop;
			this->Fall(dt);							//�����µ�
			if((room.checkCollision(position,height,width)==DownCollision)||(room.checkCollision(position,height,width)==LeftDownCollision)||
				(room.checkCollision(position,height,width)==RightDownCollision)){
					this->stopFall();					//ײ�����棬ֹͣ����
					while(room.checkCollision(position,height,width)){
						this->goBack(Up);				//����ײ����������ȥ�ˣ��ѹ��ް�����
					}
			}
			else if((room.checkCollision(position,height,width)==UpCollision)||(room.checkCollision(position,height,width)==LeftUpCollision)||
				(room.checkCollision(position,height,width)==RightUpCollision)){
					this->hitCell();					//ײ���컨�壬�ٶȵ�0����ʼ��������
					while(room.checkCollision(position,height,width)){
						this->goBack(Down);				//���ײ���컨������ȥ����ʷ��ķ�γ���
					}
			}
		}
		else{								//���û�����䣬���ʷ��ķ�Ƿ�ȿգ��Ӹ�̨�ϵ�����
			this->goBack(Down);				//������������һ��
			if((room.checkCollision(position,height,width)!=DownCollision)&&(room.checkCollision(position,height,width)!=LeftDownCollision)&&
				(room.checkCollision(position,height,width)!=RightDownCollision)){
					this->startFall();			//�������û�赲���Ϳ�ʼ����
			}
			this->goBack(Up);				//������һ�񲹳�һ��ʼ�����ߵ�һ��
		}
		switch(decision){
		case MoveLeft:
			this->move(Left);
			while((room.checkCollision(position,height,width)==LeftCollision)||(room.checkCollision(position,height,width)==LeftUpCollision)
				||(room.checkCollision(position,height,width)==LeftDownCollision)){
					this->goBack(Right);		//���ײ�����ǽ���棬��ʷ��ķ���Ұγ���
			}
			break;
		case MoveRight:
			this->move(Right);
			while((room.checkCollision(position,height,width)==RightCollision)||(room.checkCollision(position,height,width)==RightUpCollision)
				||(room.checkCollision(position,height,width)==RightDownCollision)){
					this->goBack(Left);			//���ײ���ұ�ǽ���棬��ʷ��ķ����γ���
			}
			break;
		case Leap:
			if(checkFall()==0){
				leap();						//�յ���Ծ�źţ���ʼ��Ծ
			}
			break;
		case Stop:
			break;
		default:
			break;
		} 
	}

	if(IQ==3){			//���̺����곽һ���ߵ�ʷ��ķ������Ӣ�۵�λ�ý����ƶ���������̨�ס�
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
			//�����м��п�϶
		}
		else if(heroFoot<=slimeFoot-20){		//Ӣ�۵Ľű�ʷ��ķ��ͷ��Ҫ��,ʷ��ķѰ·������Ӣ��
			if(faceDirection==Left){		    //�������������Ѱ·
				decision=MoveLeft;
			}
			if(faceDirection==Right){
				decision=MoveRight;
			}			
			//�����ϰ�����Ծ����ƽ̨
			if(position.x>40){				//�鿴����Ƿ���������ȥ��ƽ̨
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
				this->move(Right);			//�鿴�ұ��Ƿ���������ȥ��ƽ̨
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
				//������ٳͷ���
				//��¼��Ϣ
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
				
		if(this->checkFall()==1){					//�������������״̬�������Ƿ���ײ������Ӧ����
			decision=Stop;
			this->Fall(dt);							//�����µ�
			if((room.checkCollision(position,height-1,width-1)==DownCollision)||(room.checkCollision(position,height-1,width-1)==LeftDownCollision)||
				(room.checkCollision(position,height-1,width-1)==RightDownCollision)){
					this->stopFall();					//ײ�����棬ֹͣ����
					if(hypothesis==1){
						hypothesis=0;
						if(hRecord>position.y+40){     //��������λ�ñ�ԭ����
							//����
							mu[record]=(tRecord+mu[record]*bayesWeight[record])/(1+bayesWeight[record]);
							sigma[record]=sigma[record]/4;
							bayesWeight[record]++;
							record=8888;
							rv=9999;
							hRecord=0;
						}
						else{
							//�ͷ�
							hRecord=0;
						}
					}
					inAirDirection=NoDirection;

					while(room.checkCollision(position,height,width)){
						this->goBack(Up);				//����ײ����������ȥ�ˣ��ѹ��ް�����
					}
			}
			else if((room.checkCollision(position,height,width)==UpCollision)||(room.checkCollision(position,height,width)==LeftUpCollision)||
				(room.checkCollision(position,height,width)==RightUpCollision)){
					this->hitCell();					//ײ���컨�壬�ٶȵ�0����ʼ��������
					while(room.checkCollision(position,height,width)){
						this->goBack(Down);				//���ײ���컨������ȥ����ʷ��ķ�γ���
					}
			}
			if(inAirDirection==Left){
				position.x=position.x-inAirSpeed;
				while((room.checkCollision(position,height,width)==LeftCollision)||(room.checkCollision(position,height,width)==LeftUpCollision)
				||(room.checkCollision(position,height,width)==LeftDownCollision)){
					this->goBack(Right);		//���ײ�����ǽ���棬��ʷ��ķ���Ұγ���
				//	inAirDirection=Up;
				}
			}
			if(inAirDirection==Right){
				position.x=position.x+inAirSpeed;
				while((room.checkCollision(position,height,width)==RightCollision)||(room.checkCollision(position,height,width)==RightUpCollision)
				||(room.checkCollision(position,height,width)==RightDownCollision)){
					this->goBack(Left);			//���ײ���ұ�ǽ���棬��ʷ��ķ����γ���
				//	inAirDirection=Up;
				}
			}
		}
		else{								//���û�����䣬���ʷ��ķ�Ƿ�ȿգ��Ӹ�̨�ϵ�����
			this->goBack(Down);				//������������һ��
			if((room.checkCollision(position,height,width)!=DownCollision)&&(room.checkCollision(position,height,width)!=LeftDownCollision)&&
				(room.checkCollision(position,height,width)!=RightDownCollision)){
					this->startFall();		//�������û�赲���Ϳ�ʼ����
			}
			this->goBack(Up);				//������һ�񲹳�һ��ʼ�����ߵ�һ��
		}
		switch(decision){
		case MoveLeft:
			this->move(Left);
			while((room.checkCollision(position,height,width)==LeftCollision)||(room.checkCollision(position,height,width)==LeftUpCollision)
				||(room.checkCollision(position,height,width)==LeftDownCollision)){
					this->goBack(Right);		//���ײ�����ǽ���棬��ʷ��ķ���Ұγ���
					faceDirection=Right;		//ײ����ߵ�ǽ�����������
			}
			break;
		case MoveRight:
			this->move(Right);
			while((room.checkCollision(position,height,width)==RightCollision)||(room.checkCollision(position,height,width)==RightUpCollision)
				||(room.checkCollision(position,height,width)==RightDownCollision)){
					this->goBack(Left);			//���ײ���ұ�ǽ���棬��ʷ��ķ����γ���
					faceDirection=Left;		//ײ���ұߵ�ǽ�����������
			}
			break;
		case Leap:
			if(checkFall()==0){
				leap();						//�յ���Ծ�źţ���ʼ��Ծ
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