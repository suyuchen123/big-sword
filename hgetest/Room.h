#include<iostream>
#include"Monster.h"

using namespace std;
#ifndef ROOM_H_
#define ROOM_H_

#include "VariableDefine.h"

class Room{
private:
	int index;			//��ͼID
	int block[12][16];	//��ͼ������Ϣ
	int monsterNumber;  //��ͼ�Ϲ��޵�����
public:
	//Room();
	//~Room();
     int set(const char *filename);
	 void setMonstetNumber(int);					//���ù�������
	 int  showMonsterNumber();						//��ʾ�ִ��������
	 BlockType showBlock(Position p);				//��ʾָ������P(x,y)��Block������
	 BlockType showBlock(int x,int y);				//Overloading ��ʾָ������P(x,y)��Block������
//	 CollisionType checkCollision(Monster&);		//�жϹ����Ƿ����ͼ���ص������ع����ı�ײ���˵�ͼ��
													//���ع��ް����������¡���˳���һ����ײ���ı�
	 CollisionType checkCollision(Position ,int height,int width);		//Overloading,�ж�λ����Position����height,��Ϊwidth�Ĺ����Ƿ����ͼ���ص������ع����ı�ײ���˵�ͼ��
																		//���ع��ް����������¡���˳���һ����ײ���ı�
};

Position showBlockCoordinate(int i,int j);		//����Block������������ʾBlock ���Ͻ� �ڵ�ͼ�е�λ��

#endif