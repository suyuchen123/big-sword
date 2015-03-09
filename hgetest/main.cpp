#include <hge.h> 
#include<hgesprite.h>
#include"Hero.h"
#include<hgeanim.h>
#include<hgefont.h>
#include"VariableDefine.h"
#include"Slimeset.h"
#include"Room.h"
#include"Bulletset.h"
#include"Monster.h"
#include"ItemSet.h"
#include"IncidentFunction.h"
#define monsterx 401
#define monstery 251
Room room1;
Hero hero;
BulletSet bulletset;
SlimeSet slimeset;
ItemSet itemset;
hgeFont*   fnt;
HGE* pHge =0; 
hgeSprite  *m_sp;
hgeSprite  *bloc0,*bloc1,*bloc2,*bloc3,*bloc4;	//������ɵ�����ͼƬ
hgeSprite  *background;	//����
hgeSprite *bullet;						//�ӵ�����
//hgeSprite *srimpic;						//demo�ֵ�����
hgeSprite *itempic;
hgeSprite *misslel;
hgeSprite *missler;
hgeSprite *startimage;
hgeSprite *endimage;
HEFFECT  shoutgun;
HEFFECT  shoutmis;
HEFFECT  addlife;
//��������
int downBlock,upBlock,leftBlock,rightBlock;
int flag;
char outWord[25];
char debug[25];
int starting;  //�жϿ�ʼ����
int ending; //�жϽ�������
HTEXTURE g_tex;
HTEXTURE srimtex;
HTEXTURE texbackground; //������ɵ�����ͼƬ

hgeAnimation *g_gun,*g_mis;  
hgeAnimation *srimpic;
float LittleG;		//����ϵ��
float firetime=0.1;	//����ʱ���ӳ�
float nohurttime=0;
float creattime=0;

bool RenderFunc()	//���ƺ���������ʼ��HGE����ͣ������
{
	pHge->Gfx_BeginScene();//��ʼ��Ⱦ
		
	//��Ⱦ��ʼ
	if(starting==1)
	{
		startimage->Render(0,0);	  
	  pHge->Gfx_EndScene();//������Ⱦ 
	  return false;
	}
	if(hero.death()==1)
	{
		endimage->Render(0,0);

		 fnt->printf(400,300, HGETEXT_LEFT, "%d",slimeset.showScore());
	  pHge->Gfx_EndScene();//������Ⱦ 
	  return false;
	}
	background->Render(0,0);





	//��Ⱦ����
	for(int i=0;i<=750;i=i+50){
		for(int j=0;j<=550;j=j+50){
			//if(room1.showBlock(i,j)==0) bloc0->Render(i,j);
			if(room1.showBlock(i,j)==1) bloc1->Render(i,j);
			if(room1.showBlock(i,j)==2) bloc2->Render(i,j);
			if(room1.showBlock(i,j)==3) bloc3->Render(i,j);
		    if(room1.showBlock(i,j)==4) bloc4->Render(i,j);
		}
	}

	if(hero.checkFace())		//����̫�������Ҫ��һ��
	{ 
		g_gun->SetFlip(0,0);    
		g_mis->SetFlip(0,0);  
	} 
	else
	{ 
		g_gun->SetFlip(1,0);
		g_mis->SetFlip(1,0);
	}
	//��Ⱦ����Ч��
	int hurt=nohurttime*100;
	if((hurt%5<=2  &&nohurttime<=2) || nohurttime>2 || nohurttime==0 )
	
	if(hero.showWeapon()==Gun)
	{
	g_gun->Render(hero.showPosition().x,hero.showPosition().y); //��ȾӢ��  
	}
	else
	{
	 	g_mis->Render(hero.showPosition().x,hero.showPosition().y); //��ȾӢ��  
	}
 	//��Ⱦ�ӵ�
	for(int i=0;i<19;i++)
	{
		if(bulletset.exsit(i))
		{   
			if(bulletset.showweapon(i)==Gun)
			bullet->Render(bulletset.GetOut(i).position.x,bulletset.GetOut(i).position.y);
			else if(bulletset.showdir(i)) missler->Render(bulletset.GetOut(i).position.x,bulletset.GetOut(i).position.y);
			else misslel->Render(bulletset.GetOut(i).position.x,bulletset.GetOut(i).position.y);
		}
	}
	for(int i=0;i<ItemNum;i++)
	{
		if(itemset.exist(i))
		{
			itempic->Render(itemset.showPosition(i).x,itemset.showPosition(i).y);
		}
	}

	//��Ⱦһ��demo��
	for(int i=0;i<10;i++)
		if(slimeset.ExistForRender(i))
	{
		//�жϹ��ﳯ��

		if(slimeset.checkface(i))		//����̫�������Ҫ��һ��
	    { 
		srimpic->SetFlip(0,0); 	
		}		
		else
		{
		 srimpic->SetFlip(1,0); 
		}
		srimpic->Render(slimeset.PosForRender(i).x,slimeset.PosForRender(i).y);
		fnt->printf(slimeset.PosForRender(i).x,slimeset.PosForRender(i).y, HGETEXT_LEFT, "%s", outWord);
	}

	
	 fnt->printf(600, 5, HGETEXT_LEFT, "Score:%d\n",slimeset.showScore());
	 fnt->printf(5, 5, HGETEXT_LEFT, "Hp:%d\n",hero.showHp());
	//  fnt->printf(5, 200, HGETEXT_LEFT, "item num:%d\n",itemset.shownum());
	 // fnt->printf(5, 250, HGETEXT_LEFT, "%d %d %d\n",itemset.exist(0),itemset.exist(1),itemset.exist(2));

	pHge->Gfx_EndScene();//������Ⱦ
	return false;//���Ƿ���false
}


int way(int a)  //�����ӵ�������
{
  if (a==0) return -1;
  return 1;
}

void checkblock()
{
	downBlock=upBlock=leftBlock=rightBlock=0;
	int x,y;
		 for(int i=10;i<=heroWide-10;i++)   //��ȡӢ�۵���,����ͷ��
			{
				if(room1.showBlock(hero.showPosition().x+i,hero.showPosition().y+90)>0 ) 
				{
					downBlock=1; 
				}
				if(room1.showBlock(hero.showPosition().x+i,hero.showPosition().y)>0 ) 
				{
					upBlock=1; 
				}
		    }
      for(int i=0;i<=heroHight-30;i++)     //��ȡӢ�������Ƿ��赲
		{
				if(room1.showBlock(hero.showPosition().x+heroWide,hero.showPosition().y+i)>0 ) 
				{
					rightBlock=1; 
				}
				if(room1.showBlock(hero.showPosition().x,hero.showPosition().y+i)>0 ) 
				{
					leftBlock=1; 
				}
	  }

}


bool FrameFunc(){ 
		float dt=pHge->Timer_GetDelta();  
		int flag=0;
		checkblock();
		static Direction direction;
		if(starting==1) // ȷ�Ͽ�ʼ����
		{
		  if (pHge->Input_GetKeyState(HGEK_ENTER))  
			{
			starting=0;
			}
		   return 0;
		}
		if(hero.death()==1) //ȷ�Ͻ�������
	   {
	       if (pHge->Input_GetKeyState(HGEK_R))  
			{
			  
				hero.reset();
				slimeset.reset();
				itemset.reset();
				bulletset.reset();
				
			}
		   if(pHge->Input_GetKeyState(HGEK_ENTER))
		   {
		     return 1;
		   }
		 return 0;
	   }




		if (pHge->Input_GetKeyState(HGEK_LEFT))  
		{
			if(leftBlock==0) hero.move(Left);
			flag=1;
		}
		if (pHge->Input_GetKeyState(HGEK_RIGHT)) 
		{
			if(rightBlock==0) hero.move(Right); 
			flag=1;  
		}

		 int flag1=0;
			if(downBlock==1)  hero.stopAir();           //�����赲��ֹͣ   
		
			if(downBlock==0)
			{
				hero.inAir(0,Up,upBlock);				//���ǵ���ȥ�����
			}


			if(pHge->Input_GetKeyState(HGEK_SPACE))
			{
			if(hero.checkFloor()==1)
			{
					hero.inAir(20,Up,upBlock);
			 }
				flag=1;
			}
			if(flag==1)
			{
				g_gun->Update(dt);
				g_mis->Update(dt);
			}
			srimpic->Update(dt);


			if(pHge->Input_GetKeyState(HGEK_1))
				hero.changeWeapon(1);
			if(pHge->Input_GetKeyState(HGEK_2))
				hero.changeWeapon(2);

					
			firetime=firetime+dt;   //���𲢴������ӳ�
			if (pHge->Input_GetKeyState(HGEK_F)) 
			{
				          
				if((hero.showWeapon()==Gun&&firetime>0.2) ||(hero.showWeapon()==Missle&&firetime>1.0 )) 
					{
					 firetime=0;
					 //bulletset.CreateNew(hero.showPosition().x,hero.showPosition().y+50,bulletSpeed*way(hero.checkFace()),10);
					 bulletset.CreateNew(hero.attack());
					 if(hero.showWeapon()==Gun)
					 pHge->Effect_Play(shoutgun);//��������
					 if(hero.showWeapon()==Missle)
					 pHge->Effect_Play(shoutmis);//��������


					 //hero.attack ����ֵΪBulletMsg �����Ӣ�۳��е����������ӵ���Ϣ��Ȼ�����ӵ��������ɡ���2014 1.1 �ճ���
					 //�����Ҫ���������������ӵ���Ϣ,ȥhero.CPP��hero.attack������������2014 1.1 �ճ���
					//�����ӵ�
				   }
			}
			
			bulletset.Refresh(room1); //�����ӵ�����
			//�����ӵ����е�/��ǽ ��12.30�����ӵ�ײǽ�ѱ� ��װָrefresh���� �ճ���
			/*for(int i=0;i<19;i++)
			{
				if(bulletset.exsit(i))
				{
					
			        //������һ�����׵��ж��ӵ��Ե���һ���ֵ�Ч��
					if(bulletset.GetOut(i).position.x>slime.showPosition().x && bulletset.GetOut(i).position.x<slime.showPosition().x+125 
			       	  && bulletset.GetOut(i).position.y>slime.showPosition().y && bulletset.GetOut(i).position.y<slime.showPosition().y+150
					  && room1.showMonsterNumber()==1
					  )
					  {
						  bulletset.Disappear(i);
						  slime.hurt(bulletset.GetOut(i).hurt);
						  if(slime.showHp()==0) room1.setMonstetNumber(0);
					  }
				}
				if(room1.showMonsterNumber()>0)  sprintf(outWord,"Life %d\n",slime.showHp());

		   }*/
			
			Position testpos=slimeset.BulletCheck(bulletset);// ��2014 1.1 �ճ����ӵ����жԹ���ļ�⡣����������һ�������Ĺ�������� ����itemset ����������Ʒ
			if(testpos.x!=0 || testpos.y!=0)
				itemset.CreatNew(testpos);
			itemset.Refresh();
			int tmp=itemset.Add(hero.showPosition()); //����������

			hero.addhp(tmp);  //��2014 1.1 �ճ������Ӣ�۵�λ�� �������itemset.ADD��Ѫ���,ADD�ķ���ֵ�ٴ����hero.addhp�ļ�Ѫ����
		  	if(tmp!=0)
			{
				pHge->Effect_Play(addlife); //���ż�Ѫ��Ч
			}


			//����Ļ������� ������߼����¡�2014 1.1 �ճ���
			slimeset.CreateNew();//�������� ����Ӧ���������������鿴slimeset.h ����Ľ��ܡ�2014 1.1 �ճ���
        /*������һ��ʱ�̵���Ϊ*/
		slimeset.Refresh(room1,hero,dt);//������Ϊ���С�2014 1.1 �ճ���
		/*�����ж�����*/

		//Ӣ�����ˡ�2014 1.1 �ճ���
		if(nohurttime==0)
			if (   hero.hurt(slimeset.HurtHero(hero.showPosition()))      ) {hero.inAir(40,Up,upBlock);nohurttime+=dt;} else;
	   else {
			   nohurttime+=dt;
			   if (nohurttime>2) nohurttime=0;//���˺� 2���޵�ʱ�� �������Զ���Ծ��2014 1.1 �ճ���
		}


	/*	if (pHge->Input_GetKeyState(HGEK_R))  //����һ�¹���
		{
			room1.setMonstetNumber(1);
			//srim.life=100;
			slime.setHp(100);
		}*/

		return 0;

/*if (pHge->Input_GetKeyState(HGEK_ESCAPE))  return true; 
    return false; */
} 

/*void Init()  //��ʼ��
{
  //	Position pos;
//	pos.x=100;
	//pos.y=100;
	//hero.setSpeed(6,pos);
	//hero.stopAir();
	//demomonster
	//srim.exsit=1;
	room1.setMonstetNumber(1);
	//srim.life=100;
	//srim.x=monsterx;
	//srim.y=monstery;
	//slime.setPosition(monsterx,monstery);
}*/





int WINAPI WinMain( HINSTANCE hInstance, 
					HINSTANCE hPrevInstance, 
					LPSTR lpCmdLine, 
					int ShowCmd){ 

	pHge = hgeCreate(HGE_VERSION); 
	pHge->System_SetState(HGE_FRAMEFUNC, FrameFunc);             //ָ���߼�����
	pHge->System_SetState(HGE_WINDOWED, true); 
	pHge->System_SetState(HGE_USESOUND, false);		
	pHge->System_SetState(HGE_TITLE, "Big Sword"); 
	pHge->System_SetState(HGE_RENDERFUNC,RenderFunc);        //ָ����Ⱦ����
	pHge->System_SetState(HGE_FPS,60);                       //����fps
	pHge->System_SetState(HGE_USESOUND,true);//����ʹ������ 
	
	//��ʼ��
	flag=0;
	starting=1;
	ending=0;

	LittleG=9.8;
	room1.set("room1.txt");

	if (pHge->System_Initiate())	
	{ 
		srimtex=pHge->Texture_Load("srimr.png");
     	g_tex=pHge->Texture_Load("gunright.png"); 
         
		texbackground=pHge->Texture_Load("back.bmp");
				fnt=new hgeFont("font2.fnt");  //��������
		fnt->SetScale(3);


		bloc0 = new hgeSprite(pHge->Texture_Load("0.png"),0,0,50,50);
		bloc1 = new hgeSprite(pHge->Texture_Load("1.png"),0,0,50,50);
		bloc2 = new hgeSprite(pHge->Texture_Load("2.png"),0,0,50,50);
		bloc3 = new hgeSprite(pHge->Texture_Load("3.png"),0,0,50,50);
		bloc4 = new hgeSprite(pHge->Texture_Load("4.png"),0,0,50,50);
		background = new hgeSprite(pHge->Texture_Load("sky.png"),0,0,800,600);



		bullet = new hgeSprite(pHge->Texture_Load("bullet.png"),0,0,20,20);
		//srimpic = new hgeSprite(pHge->Texture_Load("srim.png"),0,0,monsterWide,monsterHight);
		itempic=new hgeSprite(pHge->Texture_Load("item.png"),0,0,ItemWide,ItemHeight);
		missler=new hgeSprite(pHge->Texture_Load("missler.png"),0,0,MissleWide,MissleHeight);
		misslel=new hgeSprite(pHge->Texture_Load("misslel.png"),0,0,MissleWide,MissleHeight);
		startimage=new hgeSprite(pHge->Texture_Load("start.png"),0,0,800,600);  //��ʼ����
		endimage=new hgeSprite(pHge->Texture_Load("end.png"),0,0,800,600);  //��������


		shoutgun=pHge->Effect_Load("./shoutgun.mp3"); //���ط�����Ч
		shoutmis=pHge->Effect_Load("./shoutmis.mp3"); //���ط�����Ч
		addlife=pHge->Effect_Load("./addlife.mp3"); //���ؼ�Ѫ��Ч

		g_gun = new hgeAnimation(g_tex, 5, 10, 6, 0, heroWide,heroHight);  
		g_mis = new hgeAnimation(pHge->Texture_Load("powerright.png"), 5, 10, 9, 0, heroWide,heroHight);
		srimpic = new hgeAnimation(srimtex,3,3,0,0,monsterWide,monsterHight);
		

		
		srimpic->SetSpeed(10);
		srimpic->Play();
		g_gun->SetSpeed(10);
		g_gun->Play();  
		g_mis->SetSpeed(10);
		g_mis->Play();  

	
		pHge->System_Start(); 
	} 
else 
{ 
	MessageBox(NULL,LPCWSTR(pHge->System_GetErrorMessage()), TEXT("Error"), MB_OK | MB_ICONERROR | MB_APPLMODAL); 

} 
pHge->System_Shutdown(); 
pHge->Release(); 
    
return 0; 

}