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
hgeSprite  *bloc0,*bloc1,*bloc2,*bloc3,*bloc4;	//背景组成的三种图片
hgeSprite  *background;	//背景
hgeSprite *bullet;						//子弹纹理
//hgeSprite *srimpic;						//demo怪的纹理
hgeSprite *itempic;
hgeSprite *misslel;
hgeSprite *missler;
hgeSprite *startimage;
hgeSprite *endimage;
HEFFECT  shoutgun;
HEFFECT  shoutmis;
HEFFECT  addlife;
//处理声音
int downBlock,upBlock,leftBlock,rightBlock;
int flag;
char outWord[25];
char debug[25];
int starting;  //判断开始画面
int ending; //判断结束画面
HTEXTURE g_tex;
HTEXTURE srimtex;
HTEXTURE texbackground; //背景组成的三种图片

hgeAnimation *g_gun,*g_mis;  
hgeAnimation *srimpic;
float LittleG;		//重力系数
float firetime=0.1;	//开火时间延迟
float nohurttime=0;
float creattime=0;

bool RenderFunc()	//绘制函数，程序开始后HGE将不停调用它
{
	pHge->Gfx_BeginScene();//开始渲染
		
	//渲染开始
	if(starting==1)
	{
		startimage->Render(0,0);	  
	  pHge->Gfx_EndScene();//结束渲染 
	  return false;
	}
	if(hero.death()==1)
	{
		endimage->Render(0,0);

		 fnt->printf(400,300, HGETEXT_LEFT, "%d",slimeset.showScore());
	  pHge->Gfx_EndScene();//结束渲染 
	  return false;
	}
	background->Render(0,0);





	//渲染房间
	for(int i=0;i<=750;i=i+50){
		for(int j=0;j<=550;j=j+50){
			//if(room1.showBlock(i,j)==0) bloc0->Render(i,j);
			if(room1.showBlock(i,j)==1) bloc1->Render(i,j);
			if(room1.showBlock(i,j)==2) bloc2->Render(i,j);
			if(room1.showBlock(i,j)==3) bloc3->Render(i,j);
		    if(room1.showBlock(i,j)==4) bloc4->Render(i,j);
		}
	}

	if(hero.checkFace())		//这里太不清楚，要改一下
	{ 
		g_gun->SetFlip(0,0);    
		g_mis->SetFlip(0,0);  
	} 
	else
	{ 
		g_gun->SetFlip(1,0);
		g_mis->SetFlip(1,0);
	}
	//渲染受伤效果
	int hurt=nohurttime*100;
	if((hurt%5<=2  &&nohurttime<=2) || nohurttime>2 || nohurttime==0 )
	
	if(hero.showWeapon()==Gun)
	{
	g_gun->Render(hero.showPosition().x,hero.showPosition().y); //渲染英雄  
	}
	else
	{
	 	g_mis->Render(hero.showPosition().x,hero.showPosition().y); //渲染英雄  
	}
 	//渲染子弹
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

	//渲染一个demo怪
	for(int i=0;i<10;i++)
		if(slimeset.ExistForRender(i))
	{
		//判断怪物朝向

		if(slimeset.checkface(i))		//这里太不清楚，要改一下
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

	pHge->Gfx_EndScene();//结束渲染
	return false;//总是返回false
}


int way(int a)  //处理子弹正逆向
{
  if (a==0) return -1;
  return 1;
}

void checkblock()
{
	downBlock=upBlock=leftBlock=rightBlock=0;
	int x,y;
		 for(int i=10;i<=heroWide-10;i++)   //获取英雄地面,或者头顶
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
      for(int i=0;i<=heroHight-30;i++)     //获取英雄左右是否被阻挡
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
		if(starting==1) // 确认开始画面
		{
		  if (pHge->Input_GetKeyState(HGEK_ENTER))  
			{
			starting=0;
			}
		   return 0;
		}
		if(hero.death()==1) //确认结束画面
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
			if(downBlock==1)  hero.stopAir();           //下面阻挡就停止   
		
			if(downBlock==0)
			{
				hero.inAir(0,Up,upBlock);				//考虑掉下去的情况
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

					
			firetime=firetime+dt;   //开火并处理开火延迟
			if (pHge->Input_GetKeyState(HGEK_F)) 
			{
				          
				if((hero.showWeapon()==Gun&&firetime>0.2) ||(hero.showWeapon()==Missle&&firetime>1.0 )) 
					{
					 firetime=0;
					 //bulletset.CreateNew(hero.showPosition().x,hero.showPosition().y+50,bulletSpeed*way(hero.checkFace()),10);
					 bulletset.CreateNew(hero.attack());
					 if(hero.showWeapon()==Gun)
					 pHge->Effect_Play(shoutgun);//发射声音
					 if(hero.showWeapon()==Missle)
					 pHge->Effect_Play(shoutmis);//发射声音


					 //hero.attack 返回值为BulletMsg 会根据英雄持有的武器生成子弹信息，然后传入子弹集合生成。【2014 1.1 苏畅】
					 //如果想要调整两把武器的子弹信息,去hero.CPP的hero.attack（）调整。【2014 1.1 苏畅】
					//创建子弹
				   }
			}
			
			bulletset.Refresh(room1); //更新子弹坐标
			//处理子弹，中弹/打到墙 【12.30关于子弹撞墙已被 封装指refresh（） 苏畅】
			/*for(int i=0;i<19;i++)
			{
				if(bulletset.exsit(i))
				{
					
			        //下面是一个简易的判断子弹对单独一个怪的效果
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
			
			Position testpos=slimeset.BulletCheck(bulletset);// 【2014 1.1 苏畅】子弹进行对怪物的检测。。返回其中一个死掉的怪物的坐标 传入itemset 用于生成物品
			if(testpos.x!=0 || testpos.y!=0)
				itemset.CreatNew(testpos);
			itemset.Refresh();
			int tmp=itemset.Add(hero.showPosition()); //处理声音用

			hero.addhp(tmp);  //【2014 1.1 苏畅】秀出英雄的位置 传入进行itemset.ADD加血检测,ADD的返回值再传入给hero.addhp的加血函数
		  	if(tmp!=0)
			{
				pHge->Effect_Play(addlife); //播放加血音效
			}


			//后面的基本上是 怪物的逻辑更新【2014 1.1 苏畅】
			slimeset.CreateNew();//补满怪物 至其应有数量。。。详情看slimeset.h 里面的介绍【2014 1.1 苏畅】
        /*怪物在一个时刻的行为*/
		slimeset.Refresh(room1,hero,dt);//怪物行为更行【2014 1.1 苏畅】
		/*怪物行动结束*/

		//英雄受伤【2014 1.1 苏畅】
		if(nohurttime==0)
			if (   hero.hurt(slimeset.HurtHero(hero.showPosition()))      ) {hero.inAir(40,Up,upBlock);nohurttime+=dt;} else;
	   else {
			   nohurttime+=dt;
			   if (nohurttime>2) nohurttime=0;//受伤后 2秒无敌时间 加向上自动跳跃【2014 1.1 苏畅】
		}


	/*	if (pHge->Input_GetKeyState(HGEK_R))  //重制一下怪兽
		{
			room1.setMonstetNumber(1);
			//srim.life=100;
			slime.setHp(100);
		}*/

		return 0;

/*if (pHge->Input_GetKeyState(HGEK_ESCAPE))  return true; 
    return false; */
} 

/*void Init()  //初始化
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
	pHge->System_SetState(HGE_FRAMEFUNC, FrameFunc);             //指定逻辑函数
	pHge->System_SetState(HGE_WINDOWED, true); 
	pHge->System_SetState(HGE_USESOUND, false);		
	pHge->System_SetState(HGE_TITLE, "Big Sword"); 
	pHge->System_SetState(HGE_RENDERFUNC,RenderFunc);        //指定渲染函数
	pHge->System_SetState(HGE_FPS,60);                       //锁定fps
	pHge->System_SetState(HGE_USESOUND,true);//设置使用声音 
	
	//初始化
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
				fnt=new hgeFont("font2.fnt");  //加载字体
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
		startimage=new hgeSprite(pHge->Texture_Load("start.png"),0,0,800,600);  //开始画面
		endimage=new hgeSprite(pHge->Texture_Load("end.png"),0,0,800,600);  //结束画面


		shoutgun=pHge->Effect_Load("./shoutgun.mp3"); //加载发射音效
		shoutmis=pHge->Effect_Load("./shoutmis.mp3"); //加载发射音效
		addlife=pHge->Effect_Load("./addlife.mp3"); //加载加血音效

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