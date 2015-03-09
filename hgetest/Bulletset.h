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
  BulletMsg GetOut(int i);				//输出现有子弹位置
  void Refresh(Room& room);						//更行所有的子弹位置
  int CreateNew(int x, int y,float Rspeed,int Hurt);		//传入数据为生成的子弹类型。
  int CreateNew(BulletMsg& tmp);
  void Disappear(int i);				//将occupy【i】表为0，表示该位存储的子弹已消失
  int singlecheck(Position);			//整个子弹集合对一个人物的检测（） 返回值大小代表造成的伤害，传入值为待检测人物的坐标
  int exsit(int i);						//该子弹是否存在
  int reset(); //重置
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