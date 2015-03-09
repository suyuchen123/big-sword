#ifndef HERO_H_
#define HERO_H_

#include "VariableDefine.h"
#include <stack>     //ջ���ڴ洢����
using namespace std;
  
class Hero{
friend class Room;
private:
	Position position;			  //Ӣ�����Ͻ�λ��
	//int weaponNumber;				  //Ӣ�۳��е�����
    //stack<Weapon> weaponStack;    //Ӣ����������
	//Weapon weaponSet[3];
	Weapon weapon;

	int hp;			 //Ѫ��
	float airTime;  //�ڿ�ʱ��
	float firetime;
	int faceDirection;//0Ϊ�ң�1Ϊ��
	int height;		 //����߶�
	int width;		 //������
	int moveSpeed;	 //�����ƶ����ٶ� (�Լ�ĳЩ����������ƶ����ٶȣ�
	int leapSpeed;   //�����ٶ�
	int onFloor;    //�Ƿ��ڵ�����	
	int beforeface; //֮ǰ������
public:
	Hero();           
	void changeWeapon(int dir);			//�л�����,dir��ʾ�������
	Weapon showWeapon();
	//void GetItem(ItemMsg);				//�õ����� ������һ��������ջ�Ĺ��̣�
	void move(Direction);				//�ƶ�����������λ�ã�����Ⱦ�Լ��ж���ײʹ��
	//void leap();						//��Ծ��onFloor=0
	//Position Fall();					//���µ��䣬����λ���ж���ײ ��ʱ��Ϊ����������û���á��� ȫ���ۺ����� inAir����
	void inAir(float bornSpeed,Direction dir,int Block);	//��ʾbornspeed ��ʾ�������ϳ��ٶȣ�dir��ʾб�������ҷ���,����UP��ʾԭ����������������ٶ���0�Ļ� ���ʾ�ǴӸߴ���������
	int checkFloor();					//����Ƿ��ڿ��У��ڿ���ʱ �������ƶ�ָ�
	int checkMove(Direction dir);		//��Ҫ���ڵ�ͼ��⣬��������Ƿ���ϣ��������Ƿ��赲���������Ƿ��谭��
	Direction checkFace();				//�����泯����
	int checkFaceresult();
	int stopAir();						//����������������,onFloor=1,�ڿ�ʱ����0������˵����ڿ�����
	Position showPosition();			//��ʾλ��
	Position changePosition(Position);	//���ж���ײΪ��ʱ����������Ӣ������
	
	BulletMsg attack();					//��������������ӵ�����Ϣ���ӵ�����ʹ��
	int hurt(int);						//�ܵ�������Ѫ������������Ч���������Ƿ�����
	int showHeight();					//��ʾӢ�۸߶�
	int showWidth();	 				//��ʾӢ�ۿ��
	int death();						//û��д�������������㣿
	int showHp()
	{
		return hp;
	}
	void addhp(int i)
	{
		hp+=i;
		if(hp>100) hp=100;
	}
	void setSpeed(int speed,Position position); //�ƶ��ٶ�����
	int reset(); //����

};

#endif