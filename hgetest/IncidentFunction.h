#ifndef INCIDENTFUNCTION_H_
#define INCIDENTFUNCTION_H_

#include "VariableDefine.h"
#include "Hero.h"
#include "Room.h"
#include "Bulletset.h"
#include "Monster.h"

Direction changDirection(Direction);			  //����ң��ϱ��� 
Direction collisionConvert(CollisionType);		  //����ײ����ת��Ϊ����,������������ײ��ת��Ϊ���������ҡ�������ת��Ϊ��NoDirection��
double gaussrand();								  //������ɸ�˹����
bool judgeRange(int x,int y);					  //�ж�(x,y)�Ƿ�������֪ʶ��������

#endif