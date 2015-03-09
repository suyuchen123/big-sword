#include<iostream>
#include"Monster.h"

using namespace std;
#ifndef ROOM_H_
#define ROOM_H_

#include "VariableDefine.h"

class Room{
private:
	int index;			//地图ID
	int block[12][16];	//地图区域信息
	int monsterNumber;  //地图上怪兽的数量
public:
	//Room();
	//~Room();
     int set(const char *filename);
	 void setMonstetNumber(int);					//设置怪兽数量
	 int  showMonsterNumber();						//显示现存怪兽数量
	 BlockType showBlock(Position p);				//显示指定坐标P(x,y)下Block的类型
	 BlockType showBlock(int x,int y);				//Overloading 显示指定坐标P(x,y)下Block的类型
//	 CollisionType checkCollision(Monster&);		//判断怪兽是否与地图有重叠，返回怪兽哪边撞到了地图。
													//返回怪兽按“左右上下”的顺序第一个碰撞到的边
	 CollisionType checkCollision(Position ,int height,int width);		//Overloading,判断位置在Position，高height,宽为width的怪兽是否与地图有重叠，返回怪兽哪边撞到了地图。
																		//返回怪兽按“左右上下”的顺序第一个碰撞到的边
};

Position showBlockCoordinate(int i,int j);		//根据Block的数组坐标显示Block 左上角 在地图中的位置

#endif