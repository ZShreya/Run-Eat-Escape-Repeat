#include "iGraphics.h"

#define JUMPLIMIT 110
int t1,t2,t3,t4;

int boi[8]; //ARRAY (CHARACTER)

int run = 0; // ARRAY (CHARACTER RUN)

int back[30]; //ARRAY (BACKGROUND)

int menu[10]; //ARRAY (MENU)

int element[9];

int hover[12]; //HOVER (MENU)

int game[5];

int gameState = 0; //GAME STATE	

char StrPoint[50];

bool jump = false;
bool jumpUp = false;

int benCoordinateJump = 0;
int xBox=25,yBox=20,dxBox=100,dyBox=100;

int d = 0;
int current_colCh= 0;
int last_colCh= 0;
int current_colOr= 0;
int last_colOr= 0;
int current_colGa= 0;
int last_colGa= 0;
int current_colPo= 0, last_colPo= 0;

int p=0;

int heart[5];
int bar = 3;
bool coll_count = true;

int over = 0;
bool flag = true ;

bool life_rim=false;
void gameover()
{
	iClear();
	life_rim =true;
	if(life_rim =true){
	iShowImage(0, 0, 1200, 600, menu[4]);
	}
	flag = false; 
	if (flag == false){
	iPauseTimer(t1);
	iPauseTimer(t2);
	iPauseTimer(t3);
	iPauseTimer(t4);
	}		

}

void show_bar() //LIFE BAR
{
	if(bar == 3)
	{
		iShowImage(1032,540, 146, 50, element[5]);
	}
	else if(bar  == 2)
	{
		iShowImage(1032,540, 146, 50, element[6]);
	}
	else if(bar == 1)
	{	
		iShowImage(1032,540, 146, 50, element[7]);
	}
	else if (bar ==0)
	{
		gameover();
	}
}

void collisionCheck();

bool musicOn = false;
bool musicOn_poison = false;

struct background //BACKGROUND STRUCTURE
{
	int x;
	int y;
}bg[30];

struct hover_menu //HOVER STRUCTURE
{
	bool hover;

}start_hover, hs_hover, ins_hover, cred_hover, main_hover, exit_hover;

void loadMenu(){

	menu[0]=iLoadImage("menu\\main.jpg");
	menu[1]=iLoadImage("menu\\instruction.jpg");
	menu[2]=iLoadImage("menu\\credit.jpg");
	menu[3]=iLoadImage("menu\\highscore.jpg");
	menu[4]=iLoadImage("menu\\over.jpg");
}

void loadHover(){
	hover[0]=iLoadImage("menu\\back_button.jpg");
	hover[1]=iLoadImage("menu\\back_button2.jpg");
	hover[2]=iLoadImage("menu\\start.png");
	hover[3]=iLoadImage("menu\\start_hover.png");
	hover[4]=iLoadImage("menu\\leader.png");
	hover[5]=iLoadImage("menu\\leader_hover.png");
	hover[6]=iLoadImage("menu\\instruct.png");
	hover[7]=iLoadImage("menu\\instruct_hover.png");
	hover[8]=iLoadImage("menu\\credits.png");
	hover[9]=iLoadImage("menu\\credits_hover.png");
	hover[10]=iLoadImage("menu\\exit.png");
	hover[11]=iLoadImage("menu\\exit_hover.png");

}

void loadBoy()
{
	boi[0]=iLoadImage("boi\\1.png");
	boi[1]=iLoadImage("boi\\2.png");
	boi[2]=iLoadImage("boi\\3.png");
	boi[3]=iLoadImage("boi\\4.png");
	boi[4]=iLoadImage("boi\\5.png");
	boi[5]=iLoadImage("boi\\6.png");
	boi[6]=iLoadImage("boi\\7.png");
	boi[7]=iLoadImage("boi\\8.png");
}

void loadBack()
{
	back[0]=iLoadImage("back\\1.png");
	back[1]=iLoadImage("back\\2.png");
	back[2]=iLoadImage("back\\3.png");
	back[3]=iLoadImage("back\\4.png");
	back[4]=iLoadImage("back\\5.png");
	back[5]=iLoadImage("back\\6.png");
	back[6]=iLoadImage("back\\7.png");
	back[7]=iLoadImage("back\\8.png");
	back[8]=iLoadImage("back\\9.png");
	back[9]=iLoadImage("back\\10.png");
	back[10]=iLoadImage("back\\11.png");
	back[11]=iLoadImage("back\\12.png");
	back[12]=iLoadImage("back\\13.png");
	back[13]=iLoadImage("back\\14.png");
	back[14]=iLoadImage("back\\15.png");
	back[15]=iLoadImage("back\\16.png");
	back[16]=iLoadImage("back\\17.png");
	back[17]=iLoadImage("back\\18.png");
	back[18]=iLoadImage("back\\19.png");
	back[19]=iLoadImage("back\\20.png");
	back[20]=iLoadImage("back\\21.png");
	back[21]=iLoadImage("back\\22.png");
	back[22]=iLoadImage("back\\23.png");
	back[23]=iLoadImage("back\\24.png");
	back[24]=iLoadImage("back\\25.png");
	back[25]=iLoadImage("back\\26.png");
	back[26]=iLoadImage("back\\27.png");
	back[27]=iLoadImage("back\\28.png");
	back[28]=iLoadImage("back\\29.png");
	back[29]=iLoadImage("back\\30.png");
}

void loadElements()
{
	element[0]=iLoadImage("elements\\apple.png");
	element[1]=iLoadImage("elements\\cherry.png");
	element[2]=iLoadImage("elements\\orange.png");
	element[3]=iLoadImage("elements\\poison.png");
	element[4]=iLoadImage("elements\\steps.png");
	element[5]=iLoadImage("elements\\heart3.png");
	element[6]=iLoadImage("elements\\heart2.png");
	element[7]=iLoadImage("elements\\heart1.png");
	game[0]=iLoadImage("elements\\score.png");
	game[1]=iLoadImage("elements\\life.png");
}

//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::FOR LOWER FRUITS ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::://

struct fruit
{
	int x,  y;
	int fruit_type;
	int h ;
	fruit(){
		x=rand()%15000+1200;
		y=48;	
	}
}ft[10];

void set_all(){
	for(int i=0;i<100;i++)
		ft[i].fruit_type= rand()%3+1;

}

void move()
{
	for(int i=0;i<100;i++)
	{
		ft[i].x-=10;
		ft[i].h =rand()%2+1;
		if(ft[i].x <= 0)
		{
			ft[i].x = rand()%15000+1200;
		}
		if(ft[i].h == 1 &&(ft[i].x>1200) && !(ft[i].fruit_type==3) )
		{
		ft[i].y=48;
		}
		if(ft[i].h == 2 &&(ft[i].x>1200) && (ft[i].fruit_type==3) )
		{
		ft[i].y=200;
		}

	}
}

void low_fruit()
{
	for(int i=0;i<30;i++)
	{
		for(int j=0;j<30;j++)
		{
			if ((ft[i].x > ft[j].x && (ft[i].x < ft[j].x+50 || ft[i].x < ft[j].x+200)))
			{	
				ft[i].x+=400;
			}
		}
		if(ft[i].fruit_type == 1)
		{
			iShowImage(ft[i].x,ft[i].y, 50, 50, element[2]);	
		}
		else  if(ft[i].fruit_type == 2)
		{
			iShowImage(ft[i].x,ft[i].y, 50, 50, element[1]);
		
		}	
		else if(ft[i].fruit_type == 3 )
		{
			
			iShowImage(ft[i].x,ft[i].y, 50, 50, element[0]);
			
		}
		
		
		}
}


// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: POISON :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::://

struct obs2
{
	int obs2_x,  obs2_y;
	int obs2_type;
	obs2(){
		obs2_x=rand()%1000+1200;
		obs2_y=50;	
	}
}ob2[10];

void set_allObs()
{
    for(int i=0;i<100;i++)
        ob2[i].obs2_type = 1;
}

void move_obs2()
{
	for(int i=0;i<1;i++)
	{
		ob2[i].obs2_x-=10;
		if(ob2[i].obs2_x<= 0)
		{
			ob2[i].obs2_x = rand()%1000+1200;

		}
		ob2[i].obs2_y=50;
	}
}

void low_obs2()
{
	for(int i=0;i<1;i++)
	{
		for(int j=0;j<1;j++)
		{
			if ((ob2[i].obs2_x > ob2[j].obs2_x && ob2[i].obs2_x < ob2[j].obs2_x+50))
			{	
				ob2[i].obs2_x+=400;
			}
		}
			iShowImage(ob2[i].obs2_x,ob2[i].obs2_y, 27, 50, element[3]);
		}
}

// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: COLLISION CHECK FOR FRUITS ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::://
void collisionCheck()
{
	for(int i=0;i<30;i++)
	{
		if(ft[i].fruit_type==1){
		
			current_colCh = ((270+20 + 120-50 > ft[i].x && 270+20 < ft[i].x + 50) && (60 + 140 > ft[i].y && 60 < ft[i].y + 61) ); //orange
	
			if(!last_colCh && current_colCh)
			{
				last_colCh = current_colCh;
				if(jump ==  true )
				{
					break ;
				}

		
			p = p+ 20;
			printf("point %d\n",p);
			ft[i].y = -1200;

			musicOn = true;
			if(musicOn)
				PlaySound("Music\\smb_stomp.wav", NULL,SND_ASYNC);

			}
			else if (last_colCh && !current_colCh)
			{
				last_colCh = current_colCh;
		
			}
		}
		
		else if(ft[i].fruit_type==2) // cherry collision
		{
			current_colOr = ((270 +20 + 120 -50 > ft[i].x && 270+20 < ft[i].x + 50) && (60 + 140 > ft[i].y && 60 < ft[i].y + 61) );
	
			if(!last_colOr && current_colOr)
			{
				last_colOr = current_colOr;
		
			if(jump ==  true )
				{
					break ;
				}	
			
			p += 40;
			printf("point %d\n",p);
			ft[i].y = -1200;
			musicOn = true;
			if(musicOn)
				PlaySound("Music\\smb_stomp.wav", NULL,SND_ASYNC);
				
			}
			else if (last_colOr && !current_colOr)
			{
				last_colOr = current_colOr;
		
			}
		}
		else if(ft[i].fruit_type==3) // green apple collision
		{
			current_colGa = ((270 +20 + 120 -50> ft[i].x && 270+20 < ft[i].x + 50) && (70+140 > ft[i].y && 70 < ft[i].y + 61) );
	
			if(!last_colGa && current_colGa)
			{
				last_colGa = current_colGa;
		
						
			if(jump ==  false )
				{

					break ;
				}
			p += 60;
			printf("point %d\n",p);
			ft[i].y = 1200;
			musicOn = true;
			if(musicOn)
				PlaySound("Music\\smb_stomp.wav", NULL,SND_ASYNC);
	
			}
			else if (last_colGa && !current_colGa)
			{
				last_colGa = current_colGa;
		
			}
		}
	}
	
}
//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::COLLISION CHECK FOR POISON ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::://
void collisionCheck_poison()

{
	for(int i=0;i<30;i++)
	{
		if(ob2[i].obs2_type==1)               // poison collision
		{
		current_colPo = ((270 +20 + 120 -50 > ob2[i].obs2_x && 270+20  < ob2[i].obs2_x + 27) && (60 + 140 > ob2[i].obs2_y && 60< ob2[i].obs2_y + 50 ));          //poison
		
			if(!last_colPo && current_colPo)
			{
				coll_count= true;
				printf("%d",coll_count);
				last_colPo = current_colPo;

				if(jump ==  true )
				{
					break;
				}
				ob2[i].obs2_x = rand()%1000+1200;
				 musicOn_poison  = true;
				if (musicOn_poison = true )
				{	
					PlaySound("Music\\smb_bump.wav", NULL,SND_ASYNC);
				}
				if(coll_count= true)
				{
					bar --;
					coll_count= false ;
				}

			}
			
			else if (last_colPo && !current_colPo)
			{
				last_colPo = current_colPo;
		
			}
		}
	}
}

void Pointshow(){
	itoa(p,StrPoint,10); //converting int to string 
	iText(161, 553, StrPoint, GLUT_BITMAP_TIMES_ROMAN_24);
}

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::HIGHSCORE :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::://
int numberArray[100];
int arrayIndex = 0;
int numberIndex = 0;

void appendHighScore(int p) //FILE APPEND
{
	FILE *fp = fopen("HighScore.txt", "a");
	
	if (fp != NULL)
	{
		fprintf(fp, "%d\n", p);
	}

	fclose(fp);
}

void readHighScore() //FILE READ
{
	FILE *fp = fopen("HighScore.txt", "r");
	char str[100];
	
	if (fp != NULL)
	{
		while (fgets(str, 15, fp) != NULL)
		{
			numberArray[arrayIndex++] = atoi(str);
		}
	}

	fclose(fp);

}

void SortingHighScore() //SORTING
{
	int temp;

	for (int i = 0; i < arrayIndex - 1; i++)
	{
		for (int j = 0; j < arrayIndex - 1; j++)
		{
			if (numberArray[j] < numberArray[j + 1])
			{
				temp = numberArray[j];
				numberArray[j] = numberArray[j + 1];
				numberArray[j + 1] = temp;
			}
		}
	}
}

char str[100];
void highScoreShow() //HIGH SCORE SHOW
{
	int x = 570;
	int y = 400;

	SortingHighScore();

	for(int i=0;i<5;i++)
	{
		itoa(numberArray[i], str, 10);
		iText(x, y, str,GLUT_BITMAP_HELVETICA_18);
		y-=50;
	}
}
//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::iDraw:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::://
void iDraw()
{
	iClear();
	
	if(gameState == 0){ //MAIN MENU

		iShowImage(0, 0, 1200, 600, menu[0]); //MAIN MENU IMG

		iShowImage(493, 316, 215, 50, hover[2]); 
		iShowImage(493, 251, 215, 50, hover[4]);
		iShowImage(493, 186, 215, 50, hover[6]);
		iShowImage(493, 121, 215, 50, hover[8]);
		iShowImage(493, 56, 215, 50, hover[10]);

		if(start_hover.hover == true)
		{
			iShowImage(493, 316, 215, 50, hover[3]); //start
		}
		else if(hs_hover.hover == true)
		{
			iShowImage(493, 251, 215, 50, hover[5]); //hscore
		}
		else if(ins_hover.hover == true)
		{
			iShowImage(493, 186, 215, 50, hover[7]); //instruction
		}
		else if(cred_hover.hover == true)
		{
			iShowImage(493, 121, 215, 50, hover[9]); //creds
		}
		else if(exit_hover.hover == true)
		{
			iShowImage(493, 56, 215, 50, hover[11]); //exit
		}
	}
	else if(gameState == 1){ //IN GAME
		for(int i = 0 ; i < 30; i++)
	{
		iShowImage(bg[i].x, bg[i].y, 48, 600, back[i]); //BACKGROUND IMGS
	}

	if (jump)
	{
		if (jumpUp)
		{

			iShowImage(270, 30 + benCoordinateJump, 110, 135, boi[1]); //JUMPS UP
		}
		else
		{
			iShowImage(270, 30 + benCoordinateJump, 110, 135, boi[3]); //JUMPS DOWN
		}
	}
	else
	{
		iShowImage(270, 30, 120, 155, boi[run]); //CHARACTER IMGS
	}
	
	low_fruit();
	low_obs2();

	show_bar();
	
	collisionCheck();
	collisionCheck_poison();

	iShowImage(50, 550, 99, 23, game[0]); //POINTS
	if(life_rim == false)
	{
	iShowImage(810, 535, 215, 50, game[1]); //LIFE REMAINING
	
	}
	Pointshow();
	}
	else if(gameState == 2){ //HIGH SCORE

		iShowImage(0, 0, 1200, 600, menu[3]); //HIGH SCORE IMG

		if(main_hover.hover == false)
		{
			iShowImage(1020, 40, 150, 44, hover[1]);
		}
		else if(main_hover.hover == true)
		{
			iShowImage(1020, 40, 150, 44, hover[0]);
		}

		highScoreShow();
	}
	else if(gameState == 3){ //INSTRUCTION

		iShowImage(0, 0, 1200, 600, menu[1]); //INSTRUCTION IMG

		if(main_hover.hover == false)
		{
			iShowImage(1020,40, 150, 44, hover[1]);
		}
		else if(main_hover.hover == true)
		{
			iShowImage(1020,40, 150, 44, hover[0]);
		}
	}
	else if(gameState == 4){ //CREDITS

		iShowImage(0, 0, 1200, 600, menu[2]); //CREDITS IMG

		if(main_hover.hover == false)
		{
			iShowImage(1020,40, 150, 44, hover[1]);
		}
		else if(main_hover.hover == true)
		{
			iShowImage(1020,40, 150, 44, hover[0]);
		}
	}
}

void iMouseMove(int mx, int my){
	
}
//*******************************************************************iPassiveMouse***********************************************************************//
void iPassiveMouseMove(int mx, int my)
{
	if(mx>=493 && mx<=708 && my>= 315 && my<= 365) //START BUTTON
	{
		start_hover.hover = true;
	}
	else
	{
		start_hover.hover = false;
	}
	if(mx>=493 && mx<=708 && my>= 250 && my<= 300) //HIGHSCORE BUTTON
	{
		hs_hover.hover = true;
	}
	else
	{
		hs_hover.hover = false;
	}
	if(mx>=493 && mx<=708 && my>= 185 && my<= 235) //INS BUTTON
	{
		ins_hover.hover = true;
	}
	else
	{
		ins_hover.hover = false;
	}
	if(mx>=493 && mx<=708 && my>= 120 && my<= 170) //CREDS BUTTON
	{
		cred_hover.hover = true;
	}
	else
	{
		cred_hover.hover = false;
	}
	if(mx>=493 && mx<=708 && my>= 55 && my<= 105) //EXIT BUTTON
	{
		exit_hover.hover = true;
	}
	else
	{
		exit_hover.hover = false;
	}

	if(gameState == 2 || gameState == 3 || gameState == 4) //BACK TO MENU BUTTON
	{
		if(mx>=1020 && mx<=1170 && my>=40 && my<= 84)
		{
			main_hover.hover = true;
		}
		else
		{
			main_hover.hover = false;
		}
	}
}
//*******************************************************************iMouse***********************************************************************//
void iMouse(int button, int state, int mx, int my)
{

	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		printf("%d %d\n", mx, my);

		if(gameState == 0) //MAIN MENU
		{
			if(mx>=493 && mx<=708 && my>= 315 && my<= 365) //START BUTTON
			{
				gameState = 1;
				iResumeTimer(t1);
				iResumeTimer(t2);
				iResumeTimer(t3);
				iResumeTimer(t4);
			}	
			else if(mx>=493 && mx<=708 && my>= 250 && my<= 300) //HIGHSCORE BUTTON
			{
				gameState = 2;
				readHighScore();
			}
			else if(mx>=493 && mx<=708 && my>= 185 && my<= 235) //INSTRUCTION BUTTON
			{
				gameState = 3;
			}
			else if(mx>=493 && mx<=708 && my>= 120 && my<= 170) //CREDITS BUTTON
			{
				gameState = 4;
			}
			else if(mx>=493 && mx<=708 && my>= 55 && my<= 105) //EXIT BUTTON
			{
				exit(0);
			}
		}

		else if(gameState == 2 || gameState == 3 || gameState == 4) //BACK BUTTON
		{
			if(mx>=1020 && mx<=1170 && my>=40 && my<= 84) //BACK TO MAIN MENU
			{
				gameState = 0;
			}
		}		
	}
}

void iKeyboard(unsigned char key)
{
	if (key == ' ')
	{
		if(!jump)
		{
			jump = true;
			jumpUp = true;
		}
	}
	if (key == 'R' || key == 'r')
	{
		iPauseTimer(t1);
		iPauseTimer(t2);
		iPauseTimer(t3);
		iPauseTimer(t4);

		appendHighScore(p);
		p = 0;
		gameState = 0;
		bar = 3 ;
	}
}

void iSpecialKeyboard(unsigned char key)
{	
	if (key == GLUT_KEY_RIGHT)
	{
				
	}
	if (key == GLUT_KEY_LEFT)
	{
		
	}
	
	if (key == GLUT_KEY_HOME)
	{
		
	}
}

//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::CHARACTER & BACKGROUND ANIMATION:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::://
void runboi() //CHARACTER ANIMATION
{
	run++;
	if(run>=8)
		run = 0;
	if(jump)
	{
		if(jumpUp)
		{
			benCoordinateJump += 15;
			if(benCoordinateJump >= JUMPLIMIT)
			{
				jumpUp = false;
			}
		}
		else
		{
			benCoordinateJump -= 15;
			if(benCoordinateJump < 0)
			{
				jump = false;
				benCoordinateJump = 0;
			}
		}
	}
}

void setBG() //SETS BACKGROUND
{
	int sum = 0;
	for(int i = 0; i < 30; i++)
	{
		 bg[i].y = 0;
		 bg[i].x = sum;
		 sum+=48; //width per slice
	}
}

void animationBG() //BACKGROUND ANIMATION
{
	for(int i=0; i < 30; i++)
	{
		bg[i].x -= 3;

		if(bg[i].x <= -48)
		{
			bg[i].x = 1200;
		}
	}
}

int main()
{
	srand((unsigned)time(NULL)) ;
	if(flag == true){
	 t1=iSetTimer(40,move); //FRUITS

	 t2=iSetTimer(40,move_obs2); //POISON

	 t3=iSetTimer(1, animationBG); //BACKGROUND ANIMATION

	 t4=iSetTimer(70, runboi); //CHARACTER ANIMATION
	}

	if (flag == false){
		iPauseTimer(t1);
		iPauseTimer(t2);
		iPauseTimer(t3);
		iPauseTimer(t4);
	}

	set_all(); //FRUIT ANIMATION
	set_allObs(); //POISON ANIMATION
	setBG(); //SETS BACKGROUND

	iInitialize(1200, 600, "RUN EAT ESCAPE REPEAT");

	loadMenu();
	loadBack();
	loadBoy();
	loadElements();
	loadHover();

	iStart();

	return 0;
}