#ifndef VARIABLEDEFINE_H_
#define VARIABLEDEFINE_H_
#define heroHight 100
#define heroWide 40
#define monsterHight 50
#define monsterWide 50
#define bulletSpeed 9
#define ItemWide 40
#define ItemHeight 40
#define ItemNum 3//表示物品集合的容量 同时也代表场上可能存在的补药最大数
#define MissleWide 40
#define MissleHeight 40
//该头文件进行一些基本变量的定义，这些定义在类中频繁使用

struct Position{			 //坐标
	float x;
	float y;
};

enum CollisionType{NoCollision,UpCollision,DownCollision,LeftCollision,RightCollision,
LeftUpCollision,LeftDownCollision,RightUpCollision,RightDownCollision};						//碰撞类型
enum Decision{MoveRight,MoveLeft,Leap,LeapLeft,LeapRight,Stop};
enum BlockType{Air,Solid1,Solid2,Solid3,Solid4};  //方块区域的地图类型
enum Weapon{Gun,Missle};				   //武器类型
enum Effect{None,Slow};					   //怪物攻击造成的效果
enum Direction{Left,Right,Up,Down,NoDirection};	       //方向
const float g=39.8;						   //重力加速度
const float dt=0.017;					   //用于跳跃。。。
 
//消息定义：
struct BulletMsg{			//子弹信息
	float xSpeed;		    //x轴方向速度，正为向右，负为向左      
    float ySpeed;			//y轴方向速度，正为向上，负为向下
	int hurt;				//伤害
	Weapon weapon;			//表示何种武器发出的子弹
	Position position; 	//子弹位置
	int lifetime;
};

struct MonsterAttackMsg{			//怪物攻击信息
	Direction direction;	//怪物攻击方向
	Effect effect;			//附加效果
	Position position;
	int damage;				//攻击造成的伤害
};
//enum ItemAttribute{A_Weapon,Medicine,Stimulus};

/*struct ItemMsg{
	//ItemAttribute attribute;
	int addHp;
	Position position;
};*/

#endif