#ifndef INCIDENTFUNCTION_H_
#define INCIDENTFUNCTION_H_

#include "VariableDefine.h"
#include "Hero.h"
#include "Room.h"
#include "Bulletset.h"
#include "Monster.h"

Direction changDirection(Direction);			  //左变右，上变下 
Direction collisionConvert(CollisionType);		  //将碰撞类型转化为方向,“上下左右碰撞”转化为“上下左右”，其他转化为“NoDirection”
double gaussrand();								  //随机生成高斯函数
bool judgeRange(int x,int y);					  //判断(x,y)是否在先验知识作用域内

#endif