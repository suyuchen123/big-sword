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
	void Refresh();//����ҩ�ǡ���ҩ���ڸú���������1000�κ���ʧ��
	void CreatNew(Position&);//���ݴ���������������꣬����֮һ���ʱ���ҩ��
	void Disappear(int i);//����ҩ
	int Add(Position tmp);//����Ӣ�����꣬�鿴Ӣ���Ƿ񴥷��Ե�ҩ ����ֵΪ��Ѫ��
	int exist(int i)//����i��ҩ�Ƿ��� ������Ⱦ
	{
		return occupy[i];
	}

	Position showPosition(int i)//��ʾ����������Ⱦ
	{
		return position[i];
	}
	int shownum()//��ʾ ��ǰҩ��Ŀ������ ����ʱ�õ� ���մ���Ӧ���ò���
	{
		return nowNum;
	}
	int reset(); //����
};


#endif