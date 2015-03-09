#ifndef MONSTER_H_
#define MONSTER_H_
//����໹����ƣ���Ҫ�м̳е�����
#include "VariableDefine.h"
#include "Room.h"
#include "Hero.h"
#include "IncidentFunction.h"

class Monster{
protected:
	Position position;			 //�������Ͻ�λ��
	Direction faceDirection;	 //�����泯�ķ���
	int level;		 //����ȼ�
	int hp;			 //Ѫ��
	int height;		 //����߶�
	int width;		 //������
	int moveSpeed;	 //�����ƶ����ٶ� (�Լ�ĳЩ����������ƶ����ٶȣ�
public:
	Monster()
	{
	}
	Monster(int level_set);				//�����ȼ�Ϊlevel_set�Ĺ���    
	Monster(int level_set,Position p);	//Overloading �����ȼ�Ϊlevel_set,λ����P(x,y)�Ĺ���
	Monster(int level_set,int x,int y); //Overloading �����ȼ�Ϊlevel_set��λ����(x,y)�Ĺ���
	//~Monster();
	Position setPosition(Position);		//���ù����ʼλ�� �� ���Ĺ�������
	Position setPosition(int x,int y);  //Overloading���ù��޳�ʼλ�� �� ���Ĺ�������
	void setHeight(int);				//���ù��޸߶�
	void setWidth(int);					//���ù��޿��
	void setSize(int,int);				//ʵ���������������Ĺ��ܣ�ͬʱʵ�ֹ��޸߶ȺͿ������
	virtual Position move(Direction);	//�ƶ�����������λ�ã�����Ⱦ�Լ��ж���ײʹ��
	Position goBack(Direction);			//��ĳ��������һ�������˸�ķ���
	Position showPosition();			//��ʾ���Ͻ�λ��
	bool hurt(BulletMsg);				//�ܵ�������Ѫ������������Ч���������Ƿ�����
	bool hurt(int);						//Overloading ���ӵ�������˺���ʱ�򣬹��޼�Ѫ�����������Ƿ�����
	int showHp();						//��ʾ����Ѫ��
	int showHeight();					//��ʾ����߶�
	int showWidth();					//��ʾ������
	void setHp(int);					//���ù���Ѫ����������ʾ���������ã�~��
	Direction showFaceDirection();		//��ʾ�����泯�ķ���	
	
};

class Slime:public Monster{				//ʷ��ķ���������
private:
	int leapSpeed;						//�����ٶ�
	bool fall;						    //�Ƿ��ڵ��䣨�Ƿ��ڿ��У�
	float inAirTime;					//�ڿ��е�ʱ��
	int inAirSpeed;						//�ڿ��е�ʱ��
	Direction inAirDirection;			//�ڿ������ı��ƶ�
	int IQ;								//ʷ��ķ�����̣��������޵���Ϊģʽ
//����Ϊ���޽��о���ʱ�Ĳ����������϶�˵��
	double rv;							//�������
	bool  hypothesis;					//�жϱ�־
	int hRecord;						//��¼ԭ�ȸ߶�
	double tRecord;						//��¼ԭ��ʱ��
	float timer;						//ʷ��ķ�ļ�ʱ��
	int centerNum;						//�������ĸ���
	double mu[100];						//ʷ��ķ������֪ʶ������Ծ��ֵ
	double sigma[100];					//ʷ��ķ������֪ʶ������Ծ����
	Position bayesCenter[100];			//�������÷�Χ���ļ�¼
	int bayesWeight[100];				//����Ȩ��
	int record;
		
public:
	friend class SlimeSet;
	Slime()
	{
	}
	Slime(int level_set);				//����ʷ��ķ
	Slime(int level_set,Position p);	//Overloading �����ȼ�Ϊlevel_set,λ����P(x,y)��ʷ��ķ
	Slime(int level_set,int x,int y);	//Overloading �����ȼ�Ϊlevel_set,λ���� (x,y)��ʷ��ķ
	bool leap();						//��Ծ��fall=1,����Ѿ��ڿ��������ʧ�ܡ�����0����ʧ�ܣ�����1����ɹ���
	bool leap(Direction);				//Overloading����ĳ��������Ծ������Ѿ��ڿ��������ʧ�ܡ�����0����ʧ�ܣ�����1����ɹ���
	void startFall();					//��ʼ���£����ڵ�ʷ��ķ�Ӹߵ�Block���µ�ʱ��  
	Position stopFall();				//����������������,fall=0
	Position Fall(float dt);			//���µ��䣬�������ε���֮���ʱ���������غ�������ʱ��λ��
	bool checkFall();					//�����Ƿ���������
	MonsterAttackMsg attack();			//���������ع��﹥����Ϣ����Ӣ��ֱ������˺�����
	void hitCell();						//ײ���컨��
	bool checkRange(Position center);	//�жϹ����Ƿ�����������
	
	void behave(Room&,Hero&,float dt);		//ÿһ�غ�ʷ��ķ���ݸ�����Ϣ��������������Щ����
										//��������������ڷ����ַ ��ÿ�ε���ʱ���� ��Ӣ��
};

enum AttackType{FireBall,IceBall};
class Dragon:public Monster{			//�������Է���
public:
	MonsterAttackMsg attack(AttackType);			//ѡ�񹥻�����
};

#endif