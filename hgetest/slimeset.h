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
	int KillNumber;//��¼ɱ����Ŀ��
	int occupy[10];
public:
	int Init();//Ӧ��û���˰ɡ�����
	int reset();
	SlimeSet();
	Position BulletCheck(BulletSet& bullets);//�����ӵ�������ÿ������������˼�⡣������Ҫ���õ���bulletset ��singlecheck����
	void Disappear(int i);
	void Refresh(Room& room,Hero& hero, float dt);//������Ϊ�������򵥶�ÿ���������slime��behave
	void CreateNew();//�����¹����ʱ����ѧ���� 3�����������ɡ��������������ɱ�������� �����������ʼ���������ڵ�����ʱ�ٸİ�
	void Add();//�������������Ӧ�е����� Ӧ������Ϊ killnumber/10+1
	Position PosForRender(int i);//Ϊ��Ⱦ������ ����
	int ExistForRender(int i);//Ϊ��Ⱦ
	Direction checkface(int i); //����
	int testkill()//�����á������ڻ���Ҫ�õ��İɡ�����Ҫ����Ļ����ʾɱ����
	{
		return KillNumber;
	}
	int testNow()//�����á�������ʾ����Ӧ�й�����
	{
		return SlimeNum;
	}
	int HurtHero(Position& pos);//����Ӣ���������ÿ�����Ϲ����Ӣ�۽��м�⡣������ֵΪ ��Ӣ���˺��ܺ�
	int showScore()
	{
		return KillNumber;
	}

};
#endif