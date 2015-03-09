#ifndef ItemSET_H_
#define ItemSET_H_
#include"VariableDefine.h"
//using namespace std;
class ItemSet{
private:
		Position position[3];
		int addHp;
	    int occupy[3];
		int existtime[3];
		int disappeartime;
		int nowNum;
		//int ItemWide;
		//int ItemHeight;
public:
	ItemSet();
	void Refresh();//更新药们。。药会在该函数被调用1000次后消失；
	void CreatNew(Position&);//根据传入的死掉怪物坐标，三分之一几率爆出药。
	void Disappear(int i);//消除药
	int Add(Position tmp);//传入英雄坐标，查看英雄是否触发吃到药 返回值为加血量
	int exist(int i)//检测第i个药是否在 用于渲染
	{
		return occupy[i];
	}

	Position showPosition(int i)//显示坐标用于渲染
	{
		return position[i];
	}
	int shownum()//显示 当前药数目，，额 调试时用的 最终代码应该用不到
	{
		return nowNum;
	}
	int reset(); //重置
};


#endif