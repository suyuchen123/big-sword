#ifndef BULLETSET_H_
#define BULLETSET_H_
#include"VariableDefine.h"
#include"Room.h"
using namespace std;
class BulletSet
{
private:
  BulletMsg bullets[20];		
  int occupy[20];
  int Bullettime[20];
  int BulletNum;
public:
  BulletSet();
  BulletMsg GetOut(int i);				//��������ӵ�λ��
  void Refresh(Room& room);						//�������е��ӵ�λ��
  int CreateNew(int x, int y,float Rspeed,int Hurt);		//��������Ϊ���ɵ��ӵ����͡�
  int CreateNew(BulletMsg& tmp);
  void Disappear(int i);				//��occupy��i����Ϊ0����ʾ��λ�洢���ӵ�����ʧ
  int singlecheck(Position);			//�����ӵ����϶�һ������ļ�⣨�� ����ֵ��С������ɵ��˺�������ֵΪ��������������
  int exsit(int i);						//���ӵ��Ƿ����
  int reset(); //����
  Weapon showweapon(int i)
  {
	  return bullets[i].weapon;
  }
  int showdir(int i)
  {
	  if(bullets[i].xSpeed>0) return 1;
	  else return 0;
  }
};

#endif