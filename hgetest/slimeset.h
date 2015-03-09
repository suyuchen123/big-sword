#ifndef SLIMESET_H_
#define SLIMESET_H_
#include"VariableDefine.h"
#include"Monster.h"
using namespace std;
class SlimeSet
{
private:
	int SlimeNum;
	Slime slimes[10];
	int KillNumber;//记录杀敌数目；
	int occupy[10];
public:
	int Init();//应该没用了吧。。。
	int reset();
	SlimeSet();
	Position BulletCheck(BulletSet& bullets);//传入子弹。。对每个怪物进行受伤检测。。。主要是用到了bulletset 的singlecheck（）
	void Disappear(int i);
	void Refresh(Room& room,Hero& hero, float dt);//怪物行为。。。简单对每个怪物调用slime的behave
	void CreateNew();//生成新怪物，暂时按大学长的 3级怪能力生成。。不过建议根据杀敌量进行 怪物的能力初始化。。后期调参数时再改吧
	void Add();//补充怪物至场上应有的数量 应有数量为 killnumber/10+1
	Position PosForRender(int i);//为渲染而返回 坐标
	int ExistForRender(int i);//为渲染
	Direction checkface(int i); //朝向
	int testkill()//测试用。。后期还是要用到的吧。。。要在屏幕上显示杀敌数
	{
		return KillNumber;
	}
	int testNow()//测试用。。。显示场上应有怪物数
	{
		return SlimeNum;
	}
	int HurtHero(Position& pos);//传入英雄坐标对拿每个场上怪物对英雄进行检测。。返回值为 对英雄伤害总和
	int showScore()
	{
		return KillNumber;
	}

};
#endif