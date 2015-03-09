#ifndef VARIABLEDEFINE_H_
#define VARIABLEDEFINE_H_
#define heroHight 100
#define heroWide 40
#define monsterHight 50
#define monsterWide 50
#define bulletSpeed 9
#define ItemWide 40
#define ItemHeight 40
#define ItemNum 3//��ʾ��Ʒ���ϵ����� ͬʱҲ�����Ͽ��ܴ��ڵĲ�ҩ�����
#define MissleWide 40
#define MissleHeight 40
//��ͷ�ļ�����һЩ���������Ķ��壬��Щ����������Ƶ��ʹ��

struct Position{			 //����
	float x;
	float y;
};

enum CollisionType{NoCollision,UpCollision,DownCollision,LeftCollision,RightCollision,
LeftUpCollision,LeftDownCollision,RightUpCollision,RightDownCollision};						//��ײ����
enum Decision{MoveRight,MoveLeft,Leap,LeapLeft,LeapRight,Stop};
enum BlockType{Air,Solid1,Solid2,Solid3,Solid4};  //��������ĵ�ͼ����
enum Weapon{Gun,Missle};				   //��������
enum Effect{None,Slow};					   //���﹥����ɵ�Ч��
enum Direction{Left,Right,Up,Down,NoDirection};	       //����
const float g=39.8;						   //�������ٶ�
const float dt=0.017;					   //������Ծ������
 
//��Ϣ���壺
struct BulletMsg{			//�ӵ���Ϣ
	float xSpeed;		    //x�᷽���ٶȣ���Ϊ���ң���Ϊ����      
    float ySpeed;			//y�᷽���ٶȣ���Ϊ���ϣ���Ϊ����
	int hurt;				//�˺�
	Weapon weapon;			//��ʾ���������������ӵ�
	Position position; 	//�ӵ�λ��
	int lifetime;
};

struct MonsterAttackMsg{			//���﹥����Ϣ
	Direction direction;	//���﹥������
	Effect effect;			//����Ч��
	Position position;
	int damage;				//������ɵ��˺�
};
//enum ItemAttribute{A_Weapon,Medicine,Stimulus};

/*struct ItemMsg{
	//ItemAttribute attribute;
	int addHp;
	Position position;
};*/

#endif