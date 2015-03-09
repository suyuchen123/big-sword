#ifndef MONSTER_H_
#define MONSTER_H_
//这个类还得设计，需要有继承的子类
#include "VariableDefine.h"
#include "Room.h"
#include "Hero.h"
#include "IncidentFunction.h"

class Monster{
protected:
	Position position;			 //怪物左上角位置
	Direction faceDirection;	 //怪物面朝的方向
	int level;		 //怪物等级
	int hp;			 //血量
	int height;		 //怪物高度
	int width;		 //怪物宽度
	int moveSpeed;	 //左右移动的速度 (以及某些情况下上下移动的速度）
public:
	Monster()
	{
	}
	Monster(int level_set);				//创建等级为level_set的怪物    
	Monster(int level_set,Position p);	//Overloading 创建等级为level_set,位置在P(x,y)的怪物
	Monster(int level_set,int x,int y); //Overloading 创建等级为level_set，位置在(x,y)的怪物
	//~Monster();
	Position setPosition(Position);		//设置怪物初始位置 或 更改怪物坐标
	Position setPosition(int x,int y);  //Overloading设置怪兽初始位置 或 更改怪物坐标
	void setHeight(int);				//设置怪兽高度
	void setWidth(int);					//设置怪兽宽度
	void setSize(int,int);				//实现上面两个函数的功能，同时实现怪兽高度和宽度设置
	virtual Position move(Direction);	//移动，函数返回位置，供渲染以及判断碰撞使用
	Position goBack(Direction);			//向某个方向退一格，输入退格的方向
	Position showPosition();			//显示左上角位置
	bool hurt(BulletMsg);				//受到攻击减血，并触发攻击效果，返回是否死掉
	bool hurt(int);						//Overloading 当子弹仅造成伤害的时候，怪兽减血函数，返回是否死掉
	int showHp();						//显示怪兽血量
	int showHeight();					//显示怪物高度
	int showWidth();					//显示怪物宽度
	void setHp(int);					//设置怪兽血量（友情提示：尽量别用！~）
	Direction showFaceDirection();		//显示怪兽面朝的方向	
	
};

class Slime:public Monster{				//史莱姆，不会飞行
private:
	int leapSpeed;						//跳起速度
	bool fall;						    //是否在掉落（是否在空中）
	float inAirTime;					//在空中的时间
	int inAirSpeed;						//在空中的时间
	Direction inAirDirection;			//在空中向哪边移动
	int IQ;								//史莱姆的智商，决定怪兽的行为模式
//以下为怪兽进行决策时的参数，不做较多说明
	double rv;							//随机变量
	bool  hypothesis;					//判断标志
	int hRecord;						//记录原先高度
	double tRecord;						//记录原先时间
	float timer;						//史莱姆的计时器
	int centerNum;						//先验中心个数
	double mu[100];						//史莱姆的先验知识——跳跃均值
	double sigma[100];					//史莱姆的先验知识——跳跃方差
	Position bayesCenter[100];			//先验适用范围中心记录
	int bayesWeight[100];				//先验权重
	int record;
		
public:
	friend class SlimeSet;
	Slime()
	{
	}
	Slime(int level_set);				//生成史莱姆
	Slime(int level_set,Position p);	//Overloading 创建等级为level_set,位置在P(x,y)的史莱姆
	Slime(int level_set,int x,int y);	//Overloading 创建等级为level_set,位置在 (x,y)的史莱姆
	bool leap();						//跳跃，fall=1,如果已经在空中则操作失败。返回0代表失败，返回1代表成功。
	bool leap(Direction);				//Overloading，向某个方向跳跃，如果已经在空中则操作失败。返回0代表失败，返回1代表成功。
	void startFall();					//开始落下，用于当史莱姆从高的Block走下的时候  
	Position stopFall();				//掉下来触碰到地面,fall=0
	Position Fall(float dt);			//向下掉落，输入两次调用之间的时间间隔，返回函数结束时的位置
	bool checkFall();					//返回是否正在下落
	MonsterAttackMsg attack();			//攻击，返回怪物攻击信息，对英雄直接造成伤害或者
	void hitCell();						//撞到天花板
	bool checkRange(Position center);	//判断怪兽是否在先验域内
	
	void behave(Room&,Hero&,float dt);		//每一回合史莱姆根据各种信息做出决定，做哪些动作
										//输入参数：①所在房间地址 ②每次调用时间间隔 ③英雄
};

enum AttackType{FireBall,IceBall};
class Dragon:public Monster{			//龙，可以飞行
public:
	MonsterAttackMsg attack(AttackType);			//选择攻击类型
};

#endif