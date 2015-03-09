#ifndef HERO_H_
#define HERO_H_

#include "VariableDefine.h"
#include <stack>     //栈用于存储武器
using namespace std;
  
class Hero{
friend class Room;
private:
	Position position;			  //英雄左上角位置
	//int weaponNumber;				  //英雄持有的武器
    //stack<Weapon> weaponStack;    //英雄现有武器
	//Weapon weaponSet[3];
	Weapon weapon;

	int hp;			 //血量
	float airTime;  //腾空时间
	float firetime;
	int faceDirection;//0为右，1为左；
	int height;		 //人物高度
	int width;		 //人物宽度
	int moveSpeed;	 //左右移动的速度 (以及某些情况下上下移动的速度）
	int leapSpeed;   //跳起速度
	int onFloor;    //是否在地面上	
	int beforeface; //之前脸朝向
public:
	Hero();           
	void changeWeapon(int dir);			//切换武器,dir表示武器编号
	Weapon showWeapon();
	//void GetItem(ItemMsg);				//得到武器 （就是一个武器入栈的过程）
	void move(Direction);				//移动，函数返回位置，供渲染以及判断碰撞使用
	//void leap();						//跳跃，onFloor=0
	//Position Fall();					//向下掉落，返回位置判断碰撞 暂时认为这两个函数没有用。。 全部综合在了 inAir里面
	void inAir(float bornSpeed,Direction dir,int Block);	//表示bornspeed 表示跳的向上初速度，dir表示斜跳的左右方向,传入UP表示原地上下跳。如果初速度是0的话 则表示是从高处自由下落
	int checkFloor();					//检测是否在空中，在空中时 不接受移动指令。
	int checkMove(Direction dir);		//主要用于地图检测，检测下落是否完毕，左右行是否阻挡，向上跳是否阻碍。
	Direction checkFace();				//返回面朝方向
	int checkFaceresult();
	int stopAir();						//掉下来触碰到地面,onFloor=1,腾空时间清0；或者说清空腾空数据
	Position showPosition();			//显示位置
	Position changePosition(Position);	//当判断碰撞为真时，用以修正英雄坐标
	
	BulletMsg attack();					//攻击，返回射出子弹的信息供子弹生成使用
	int hurt(int);						//受到攻击减血，并触发攻击效果，返回是否死掉
	int showHeight();					//显示英雄高度
	int showWidth();	 				//显示英雄宽度
	int death();						//没有写。。。坐标清零？
	int showHp()
	{
		return hp;
	}
	void addhp(int i)
	{
		hp+=i;
		if(hp>100) hp=100;
	}
	void setSpeed(int speed,Position position); //移动速度设置
	int reset(); //重制

};

#endif