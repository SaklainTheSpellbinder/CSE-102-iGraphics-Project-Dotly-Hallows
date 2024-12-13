#include "iGraphics.h"
#include<time.h>
#include<stdlib.h>
#include<stdbool.h>
#include<Windows.h>
#define screenheight 850
#define screenwidth 800
#define mazepixel 40// all of the sprites...harry demnetors....snitches eveerything is 40*40

void drawmaze();
void Harrymove();
void newgame(int level);
void checkTrigger();
void dementorinitial();
void harryinitial();
void movedementor();
void movedem1();
void movedem2();
void movedem3();
void movebasil();
void Harrydeadcheck();
void lifecheck();
int dementortime=340;
int brickNum;
int snitchesNum;
int mazeHeight = 840;
int mazeWidth = 760;
int mazeX = (screenwidth / 2) - (mazeWidth / 2)+3;
int mazeY = (screenheight / 2) - (mazeHeight / 2)-5;
int mazeLevel = 1;
int mazeXcor[200];
int mazeYcor[200];
int snitchXcor[210][2];
int snitchYcor[210];
int hocrux[210];
int cellX;
int cellY;
int harryNow[2]={19,9};
int snitchCollected=0;
char score[1000];
int point=0;
int life=3;
bool harrydead=false;
bool gameover=false;
bool playgame=true;
typedef struct{
	int upInd, downInd, leftInd, rightInd;
    int x;
    int y;
    int lastcount;
    bool upCount, downCount, leftCount, rightCount;
    int right, left, up, down;
	bool dead;
    int direction;
	int now[2];
	int target[2];
}dementor;

dementor dem1,dem2,dem3,basil;


typedef struct {
    int upInd, downInd, leftInd, rightInd;
    int x;
    int y;
    int lastcount;
    bool upCount, downCount, leftCount, rightCount;
    int right, left, up, down;
} move;

move harry;


int maze[3][21][19] =
{
	{
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 2, 2, 3, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1,
		1, 2, 1, 1, 2, 1, 1, 1, 2, 1, 2, 1, 1, 1, 2, 1, 1, 2, 1,
		1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 2, 2, 1,
		1, 2, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 2, 1,
		1, 2, 2, 2, 2, 1, 2, 2, 2, 1, 2, 2, 2, 1, 2, 2, 2, 2, 1,
		1, 1, 1, 1, 2, 1, 1, 1, 2, 1, 3, 1, 1, 1, 2, 1, 1, 1, 1,
		0, 0, 0, 1, 2, 1, 2, 2, 2, 2, 2, 2, 2, 1, 2, 1, 0, 0, 0,
		1, 1, 1, 1, 2, 1, 2, 1, 1, 2, 1, 1, 2, 1, 2, 1, 1, 1, 1,
		1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1,
		1, 1, 1, 1, 2, 1, 2, 1, 1, 0, 1, 1, 2, 1, 2, 1, 1, 1, 1,
		0, 0, 0, 1, 2, 1, 2, 2, 2, 2, 3, 2, 2, 1, 2, 1, 0, 0, 0,
		1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1,
		1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1,
		1, 2, 1, 1, 2, 1, 1, 1, 2, 1, 2, 1, 2, 1, 2, 1, 1, 2, 1,
		1, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 1,
		1, 1, 3, 1, 2, 1, 2, 1, 1, 1, 1, 1, 2, 1, 2, 1, 2, 1, 1,
		1, 2, 2, 2, 2, 1, 2, 2, 2, 1, 2, 2, 2, 1, 2, 3, 2, 2, 1,
		1, 2, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 2, 1,
		1, 2, 2, 2, 2, 2, 2, 2, 2, 0, 2, 2, 2, 2, 2, 2, 2, 2, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	},
	{
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 2, 3, 2, 2, 2, 1, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 3, 1,
		1, 2, 1, 1, 1, 2, 1, 1, 2, 1, 2, 1, 1, 2, 1, 1, 1, 2, 1,
		1, 2, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1, 2, 1,
		1, 2, 2, 2, 1, 2, 1, 1, 2, 1, 2, 1, 1, 2, 1, 2, 2, 2, 1,
		1, 1, 1, 1, 1, 2, 2, 2, 2, 1, 3, 2, 2, 2, 1, 1, 1, 1, 1,
		1, 2, 2, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1, 2, 2, 2, 1,
		1, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 1,
		1, 2, 1, 1, 2, 1, 2, 1, 1, 2, 1, 1, 2, 1, 2, 1, 1, 2, 1,
		1, 2, 2, 2, 2, 1, 2, 1, 2, 3, 2, 1, 2, 1, 2, 2, 2, 2, 1,
		1, 2, 1, 2, 1, 1, 2, 1, 1, 0, 1, 1, 2, 1, 1, 3, 1, 2, 1,
		1, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 1,
		1, 2, 1, 1, 2, 1, 1, 1, 2, 1, 2, 1, 1, 1, 2, 1, 1, 2, 1,
		1, 2, 2, 2, 2, 1, 2, 2, 2, 1, 2, 2, 2, 1, 2, 2, 2, 2, 1,
		1, 1, 2, 1, 2, 1, 2, 1, 1, 1, 1, 1, 2, 1, 2, 1, 2, 1, 1,
		1, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 1, 2, 2, 1,
		1, 2, 1, 1, 2, 1, 1, 1, 2, 1, 2, 1, 1, 1, 2, 1, 1, 2, 1,
		1, 2, 3, 2, 2, 1, 2, 2, 2, 1, 2, 2, 2, 1, 2, 2, 2, 2, 1,
		1, 2, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 2, 1,
		1, 2, 2, 2, 2, 1, 2, 2, 2, 0, 2, 2, 2, 1, 2, 2, 2, 3, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
	}
    ,
    {

    }
};

char BGImg[4][30] = {"assets\\BG3.bmp"};
char mazeWall[2][30]={"assets\\wall.bmp"};
char snitch[2][39]={"assets\\snitch4.bmp","assets\\Sortinghat2.bmp"};
char harrydown[9][100]={"assets\\harry\\tile001.bmp","assets\\harry\\tile002.bmp"};
char harryup[9][100]={"assets\\harry\\tile009.bmp","assets\\harry\\tile010.bmp"};
char harryright[9][100]={"assets\\harry\\tile027.bmp","assets\\harry\\tile028.bmp"};
char harryleft[9][100]={"assets\\harry\\tile018.bmp","assets\\harry\\tile019.bmp"};
char dementorright[1][100]={"assets\\dementor\\rightdementor.bmp"};
char dementorleft[1][100]={"assets\\dementor\\leftdementor.bmp"};
char dementordown[1][100]={"assets\\dementor\\downdementor.bmp"};
char dementorup[1][100]={"assets\\dementor\\updementor.bmp"};
char basiliskright[3][100]={"assets\\basilisk\\tile000.bmp","assets\\basilisk\\tile001.bmp","assets\\basilisk\\tile002.bmp"};
char basiliskleft[3][100]={"assets\\basilisk\\left000.bmp","assets\\basilisk\\left001.bmp","assets\\basilisk\\left002.bmp"};
char heart[1][100]={"assets\\heart\\000.bmp"};
char harrydeadscene[1][100]={"assets\\harrydead\\000.bmp"};
char gameoverscene[1][100]={"assets\\Gameover.bmp"};
//int x=500, y = 300, r = 20;
/*
	function iDraw() is called again and again by the system.

	*/


void iDraw() {
	//place your drawing codes here
	iClear();
	iShowBMP(0,0,BGImg[0]);
	if(playgame){
		drawmaze();
		Harrydeadcheck();
		lifecheck();
		if(life==3){
			iShowBMP2(23,805,heart[0],0);
			iShowBMP2(63,805,heart[0],0);
			iShowBMP2(103,805,heart[0],0);
		}
		else if(life==2){
			iShowBMP2(23,805,heart[0],0);
			iShowBMP2(63,805,heart[0],0);
		}
		else if(life==1){
			iShowBMP2(23,805,heart[0],0);
		}
		iText(590, 815, "SCORE: ",GLUT_BITMAP_HELVETICA_18);
		sprintf(score,"%d",point);
		iText(662, 815, score,GLUT_BITMAP_HELVETICA_18);
		movedementor();

				if (harry.rightCount){
					Harrymove();
					iShowBMP2(harry.x, harry.y, harryright[harry.rightInd], 9283431);
					}
				else if (harry.leftCount){
					Harrymove();
					iShowBMP2(harry.x, harry.y, harryleft[harry.leftInd], 9283431);
				}
				else if (harry.upCount){
					Harrymove();
					iShowBMP2(harry.x, harry.y, harryup[harry.upInd], 9283431);
				}
				else if (harry.downCount){
					Harrymove();
					iShowBMP2(harry.x, harry.y, harrydown[harry.downInd], 9283431);
				}
				else{
					Harrymove();
					if(harry.lastcount==0)
						iShowBMP2(harry.x, harry.y, harryright[harry.rightInd], 9283431);
					else if(harry.lastcount==1)
						iShowBMP2(harry.x, harry.y, harryleft[harry.leftInd], 9283431);
					else if(harry.lastcount==2)
						iShowBMP2(harry.x, harry.y, harryup[harry.upInd], 9283431);
					else
						iShowBMP2(harry.x, harry.y, harrydown[harry.downInd], 9283431);
				}
	}
	if(gameover){
		iShowBMP(0,0,gameoverscene[0]);
	}
}
		
	void harryinitial(){
		harryNow[0]=19;
		harryNow[1]=9;
		cellX = 9;
		cellY = 19;
		harry.x = mazeX + cellX*mazepixel;
		harry.y = mazeY + (20-cellY)*mazepixel;
		harry.downCount=false;
		harry.rightCount=false;
		harry.upCount=false;
		harry.leftCount=false;
		harry.rightInd=0;
		harry.leftInd=0;
		harry.upInd=0;
		harry.downInd=0;
	}

	void drawmaze() {
		int c=0, p, t = 0, z;
			brickNum = 0;
			snitchesNum=0;
			if(snitchCollected==187 && mazeLevel==0){
				harryinitial();
				dementorinitial();
				mazeLevel=1;
				dementortime=290;
				//newgame(mazeLevel);
			}
    for (int i = 20; i >= 0; i--) {
        for (int j = 0; j < 19; j++) {
            if (maze[mazeLevel][i][j]==1) {
				brickNum=c++;
                mazeXcor[brickNum] = mazepixel * j;
                mazeYcor[brickNum] = mazepixel * (20-i);
				iShowBMP(mazeX + mazeXcor[brickNum], mazeY + mazeYcor[brickNum], mazeWall[0]);
			}
			else if(maze[mazeLevel][i][j]==2)
				{
					snitchesNum=t++;
					snitchXcor[snitchesNum][0] = mazepixel*j;
					snitchYcor[snitchesNum] = mazepixel*(20-i);
					snitchXcor[snitchesNum][1] = 0;
					iShowBMP2(mazeX + snitchXcor[snitchesNum][0], mazeY + snitchYcor[snitchesNum],snitch[0],0 );
				}
			else if(maze[mazeLevel][i][j]==3)
				{
					snitchesNum=t++;
					snitchXcor[snitchesNum][0] = mazepixel*j;
					snitchYcor[snitchesNum] = mazepixel*(20-i);
					snitchXcor[snitchesNum][1] = 0;
					iShowBMP2(mazeX + snitchXcor[snitchesNum][0], mazeY + snitchYcor[snitchesNum],snitch[1],0 );
				}
		}
	}
		
		// for (int i = 0; i < 201; i++)
		// {
		// 	hocrux[i] = 0;
		// }
        
    }


/* 
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
	*/
void iMouseMove(int mx, int my) {
	printf("x = %d, y= %d\n",mx,my);
	//place your codes here
}

/*
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
	*/
void iMouse(int button, int state, int mx, int my) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		//place your codes here
		//	printf("x = %d, y= %d\n",mx,my);
		// x += 10;
		// y += 10;
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		//place your codes here
		// x -= 10;
		// y -= 10;
	}
}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
	*/
void iKeyboard(unsigned char key) {
	if (key == 'q') {
		exit(0);
	}
	//place your codes for other keys here
}

/*
	function iSpecialKeyboard() is called whenver user hits special keys like-
	function keys, home, end, pg up, pg down, arraows etc. you have to use
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
	*/
void iSpecialKeyboard(unsigned char key) {

	if(key==GLUT_KEY_RIGHT){
		if ((maze[mazeLevel][harryNow[0]][harryNow[1]+1])!=1)
			{
				harry.downCount = false;
				harry.upCount = false;
				harry.leftCount = false;
				harry.rightCount = true;
				printf("%d %d\n",harryNow[0],harryNow[1]);
                harry.lastcount=0;
			}
			else
			{
				harry.downCount = false;
				harry.upCount = false;
				harry.leftCount = false;
				harry.rightCount = false;
			}
	}
	if(key==GLUT_KEY_LEFT){
		if ((maze[mazeLevel][harryNow[0]][harryNow[1]-1])!=1)
			{
				harry.downCount = false;
				harry.upCount = false;
				harry.leftCount = true;
				harry.rightCount = false;
				printf("%d %d\n",harryNow[0],harryNow[1]);
                harry.lastcount=1;
			}
			else
			{
				harry.downCount = false;
				harry.upCount = false;
				harry.leftCount = false;
				harry.rightCount = false;
			}
	}

	if(key==GLUT_KEY_UP){
		if ((maze[mazeLevel][harryNow[0]-1][harryNow[1]])!=1)
			{
				harry.downCount = false;
				harry.upCount = true;
				harry.leftCount = false;
				harry.rightCount = false;
                printf("%d %d\n",harryNow[0],harryNow[1]);
                harry.lastcount=2;
			}
			else
			{
				harry.downCount = false;
				harry.upCount = false;
				harry.leftCount = false;
				harry.rightCount = false;
			}
	}

	if(key==GLUT_KEY_DOWN){
		if ((maze[mazeLevel][harryNow[0]+1][harryNow[1]])!=1)
			{
				harry.downCount = true;
				harry.upCount = false;
				harry.leftCount = false;
				harry.rightCount = false;
				printf("%d %d\n",harryNow[0],harryNow[1]);
                harry.lastcount=3;
			}
			else
			{
				harry.downCount = false;
				harry.upCount = false;
				harry.leftCount = false;
				harry.rightCount = false;
			}
	}

	if (key == GLUT_KEY_END) {
		exit(0);
	}
	//place your codes for other keys here
}


void dementorinitial(){
		int dem1initX = 8;
		int dem1initY = 9;
		dem1.now[0]=9;
		dem1.now[1]=8;
		dem1.x = mazeX + dem1initX*mazepixel;
		dem1.y = mazeY + (20-dem1initY)*mazepixel;
		dem1.downCount=false;
		dem1.rightCount=false;
		dem1.upCount=false;
		dem1.leftCount=false;
		dem1.rightInd=0;
		dem1.leftInd=0;
		dem1.upInd=0;
		dem1.downInd=0;
		dem1.direction=0;
		dem1.dead=false;
		dem1.target[0]=harryNow[0];
		dem1.target[1]=harryNow[1];
		
		int dem2initX = 1;
		int dem2initY = 1;
		dem2.now[0]=1;
		dem2.now[1]=1;
		dem2.x = mazeX + dem2initX*mazepixel;
		dem2.y = mazeY + (20-dem2initY)*mazepixel;
		dem2.downCount=false;
		dem2.rightCount=false;
		dem2.upCount=false;
		dem2.leftCount=false;
		dem2.rightInd=0;
		dem2.leftInd=0;
		dem2.upInd=0;
		dem2.downInd=0;
		dem2.direction=0;
		dem2.dead=false;
		dem2.target[0]=harryNow[0];
		dem2.target[1]=harryNow[1];

		int dem3initX = 10;
		int dem3initY = 9;
		dem3.now[0]=9;
		dem3.now[1]=10;
		dem3.x = mazeX + dem3initX*mazepixel;
		dem3.y = mazeY + (20-dem3initY)*mazepixel;
		dem3.downCount=false;
		dem3.rightCount=false;
		dem3.upCount=false;
		dem3.leftCount=false;
		dem3.rightInd=0;
		dem3.leftInd=0;
		dem3.upInd=0;
		dem3.downInd=0;
		dem3.direction=0;
		dem3.dead=false;
		dem3.target[0]=harryNow[0];
		dem3.target[1]=harryNow[1];

		int basilinitX = 9;
		int basilinitY = 8;
		basil.now[0]=8;
		basil.now[1]=9;
		basil.x = mazeX + basilinitX*mazepixel;
		basil.y = mazeY + (20-basilinitY)*mazepixel;
		basil.downCount=false;
		basil.rightCount=false;
		basil.upCount=false;
		basil.leftCount=false;
		basil.rightInd=0;
		basil.leftInd=0;
		basil.upInd=0;
		basil.downInd=0;
		basil.direction=0;
		basil.dead=false;
		basil.target[0]=harryNow[0];
		basil.target[1]=harryNow[1];
}

//mara khawa AI editing starts
int NoWall(int arr[],int b){
    // up=2
    // down =3
    // right 0
    // left =1
    if(b==2){
        if ((maze[mazeLevel][arr[0]-1][arr[1]])!=1)
            return 1;
        else
            return 0;
    }
    if(b==3){
        if ((maze[mazeLevel][arr[0]+1][arr[1]])!=1)
            return 1;
        else
            return 0;
    }
    if(b==0){
        if ((maze[mazeLevel][arr[0]][arr[1]+1])!=1){
            return 1;
        }
        else
            return 0;
    }
    if(b==1){
        if ((maze[mazeLevel][arr[0]][arr[1]-1])!=1)
            return 1;
        else
            return 0;
    }
}

void movedem1(){
	dem1.target[0]=harryNow[0];
	dem1.target[1]=harryNow[1];
    if(dem1.direction==0){
        if(dem1.target[1]>dem1.now[1] && NoWall(dem1.now,0) ){
			dem1.now[1]++;
            dem1.x+=mazepixel;
        }
        else if(!NoWall(dem1.now,0)){
            if(dem1.target[0]>dem1.now[0] && NoWall(dem1.now,3)){
                dem1.direction=3;
				dem1.now[0]++;
                dem1.y-=mazepixel;
            }
            else if(dem1.target[0]<dem1.now[0] && NoWall(dem1.now,2)){
                dem1.direction=2;
				dem1.now[0]--;
                dem1.y+=mazepixel;
            }
			else if(dem1.target[1]<dem1.now[1] && NoWall(dem1.now,1)){
				dem1.direction=1;
				dem1.now[1]--;
				dem1.x-=mazepixel;
			}
			else if(NoWall(dem1.now,3)){
				dem1.direction=3;
				dem1.now[0]++;
				dem1.y-=mazepixel;
			}
			else if(NoWall(dem1.now,2)){
				dem1.direction=2;
				dem1.now[0]--;
				dem1.y+=mazepixel;
			}
			else if(NoWall(dem1.now,1)){
				dem1.direction=1;
				dem1.now[1]--;
				dem1.x-=mazepixel;
			}
        }
		else if(NoWall(dem1.now,0)){
			if(dem1.target[0]>dem1.now[0] && NoWall(dem1.now,3)){
                dem1.direction=3;
				dem1.now[0]++;
                dem1.y-=mazepixel;
            }
            else if(dem1.target[0]<dem1.now[0] && NoWall(dem1.now,2)){
                dem1.direction=2;
				dem1.now[0]--;
                dem1.y+=mazepixel;
            }
			else{
				dem1.direction=0;
				dem1.now[1]++;
				dem1.x+=mazepixel;
			}
		}
    }

	else if(dem1.direction==1){
		if(dem1.target[0]>dem1.now[0] && NoWall(dem1.now,3)){
			dem1.direction=3;
			dem1.now[0]++;
			dem1.y-=mazepixel;
		}
        else if(dem1.target[1]<dem1.now[1] && NoWall(dem1.now,1) ){
			dem1.now[1]--;
            dem1.x-=mazepixel;
        }
        else if(!NoWall(dem1.now,1)){
            if(dem1.target[0]>dem1.now[0] && NoWall(dem1.now,3)){
                dem1.direction=3;
				dem1.now[0]++;
                dem1.y-=mazepixel;
            }
            else if(dem1.target[0]<dem1.now[0] && NoWall(dem1.now,2)){
                dem1.direction=2;
				dem1.now[0]--;
                dem1.y+=mazepixel;
            }
			else if(dem1.target[1]>dem1.now[1] && NoWall(dem1.now,0)){
				dem1.direction=0;
				dem1.now[1]++;
				dem1.x+=mazepixel;
			}
			else if(NoWall(dem1.now,3)){
				dem1.direction=3;
				dem1.now[0]++;
				dem1.y-=mazepixel;
			}
			else if(NoWall(dem1.now,2)){
				dem1.direction=2;
				dem1.now[0]--;
				dem1.y+=mazepixel;
			}
			else if(NoWall(dem1.now,0)){
				dem1.direction=0;
				dem1.now[1]++;
				dem1.x+=mazepixel;
			}
        }
		else if(NoWall(dem1.now,1)){
			if(dem1.target[0]>dem1.now[0] && NoWall(dem1.now,3)){
                dem1.direction=3;
				dem1.now[0]++;
                dem1.y-=mazepixel;
            }
            else if(dem1.target[0]<dem1.now[0] && NoWall(dem1.now,2)){
                dem1.direction=2;
				dem1.now[0]--;
                dem1.y+=mazepixel;
            }
			else{
				dem1.now[1]--;
				dem1.x-=mazepixel;
			}
		}
    }
	
	else if(dem1.direction==2){
		if(dem1.target[1]<dem1.now[1] && NoWall(dem1.now,1)){
			dem1.direction=1;
			dem1.now[1]--;
			dem1.x-=mazepixel;	
		}
        else if(dem1.target[0]<dem1.now[0] && NoWall(dem1.now,2) ){
			dem1.direction=2;
			dem1.now[0]--;
            dem1.y+=mazepixel;
        }
        else if(!NoWall(dem1.now,2)){
            if(dem1.target[1]>dem1.now[1] && NoWall(dem1.now,0)){
				dem1.direction=0;
				dem1.now[1]++;
				dem1.x+=mazepixel;
			}
            else if(dem1.target[1]<dem1.now[1] && NoWall(dem1.now,1)){
                dem1.direction=1;
				dem1.now[1]--;
                dem1.x-=mazepixel;
            }
			else if(dem1.target[0]>dem1.now[0] && NoWall(dem1.now,3)){
                dem1.direction=3;
				dem1.now[0]++;
                dem1.y-=mazepixel;
            }
			else if(NoWall(dem1.now,1)){
				dem1.direction=1;
				dem1.now[1]--;
				dem1.x-=mazepixel;
			}
			else if(NoWall(dem1.now,3)){
				dem1.direction=3;
				dem1.now[0]++;
				dem1.y-=mazepixel;
			}
			else if(NoWall(dem1.now,0)){
				dem1.direction=0;
				dem1.now[1]++;
				dem1.x+=mazepixel;
			}
        }
		else if(NoWall(dem1.now,2)){
			if(dem1.target[1]>dem1.now[1] && NoWall(dem1.now,0)){
				dem1.direction=0;
				dem1.now[1]++;
				dem1.x+=mazepixel;
			}
			else if(dem1.target[1]<dem1.now[1] && NoWall(dem1.now,1)){
                dem1.direction=1;
				dem1.now[1]--;
                dem1.x-=mazepixel;
            }
			else{
				dem1.now[0]--;
				dem1.y+=mazepixel;
			}
		}
    }

	else if(dem1.direction==3){
		// if(dem1.target[1]>dem1.now[1] && NoWall(dem1.now,0)){
		// 	dem1.direction=0;
		// 	dem1.now[1]++;
		// 	dem1.x+=mazepixel;	
		// }
        if(dem1.target[0]>dem1.now[0] && NoWall(dem1.now,3) ){
			dem1.now[0]++;
            dem1.y-=mazepixel;
        }
        else if(!NoWall(dem1.now,3 )){
            if(dem1.target[0]<dem1.now[0] && NoWall(dem1.now,2)){
                dem1.direction=2;
				dem1.now[0]--;
                dem1.y+=mazepixel;
            }
            else if(dem1.target[1]<dem1.now[1] && NoWall(dem1.now,1)){
                dem1.direction=1;
				dem1.now[1]--;
                dem1.x-=mazepixel;
            }
			else if(dem1.target[1]>dem1.now[1] && NoWall(dem1.now,0)){
				dem1.direction=0;
				dem1.now[1]++;
				dem1.x+=mazepixel;
			}
			else if(NoWall(dem1.now,1)){
				dem1.direction=1;
				dem1.now[1]--;
				dem1.x-=mazepixel;
			}
			else if(NoWall(dem1.now,2)){
				dem1.direction=2;
				dem1.now[0]--;
				dem1.y+=mazepixel;
			}
			else if(NoWall(dem1.now,0)){
				dem1.direction=0;
				dem1.now[1]++;
				dem1.x+=mazepixel;
			}
        }
		else if(NoWall(dem1.now,3)){
			if(dem1.target[1]>dem1.now[1] && NoWall(dem1.now,0)){
				dem1.direction=0;
				dem1.now[1]++;
				dem1.x+=mazepixel;
			}
			else if(dem1.target[1]<dem1.now[1] && NoWall(dem1.now,1)){
                dem1.direction=1;
				dem1.now[1]--;
                dem1.x-=mazepixel;
            }
			else{
				dem1.now[0]++;
				dem1.y-=mazepixel;
			}
		}
    }	
}

void movedem2(){
	dem2.target[0]=harryNow[0];
	dem2.target[1]=harryNow[1];
    if(dem2.direction==0){
        if(dem2.target[1]>dem2.now[1] && NoWall(dem2.now,0) ){
			dem2.now[1]++;
            dem2.x+=mazepixel;
        }
        else if(!NoWall(dem2.now,0)){
            if(dem2.target[0]>dem2.now[0] && NoWall(dem2.now,3)){
                dem2.direction=3;
				dem2.now[0]++;
                dem2.y-=mazepixel;
            }
            else if(dem2.target[0]<dem2.now[0] && NoWall(dem2.now,2)){
                dem2.direction=2;
				dem2.now[0]--;
                dem2.y+=mazepixel;
            }
			else if(dem2.target[1]<dem2.now[1] && NoWall(dem2.now,1)){
				dem2.direction=1;
				dem2.now[1]--;
				dem2.x-=mazepixel;
			}
			else if(NoWall(dem2.now,3)){
				dem2.direction=3;
				dem2.now[0]++;
				dem2.y-=mazepixel;
			}
			else if(NoWall(dem2.now,2)){
				dem2.direction=2;
				dem2.now[0]--;
				dem2.y+=mazepixel;
			}
			else if(NoWall(dem2.now,1)){
				dem2.direction=1;
				dem2.now[1]--;
				dem2.x-=mazepixel;
			}
        }
		else if(NoWall(dem2.now,0)){
				dem2.direction=0;
				dem2.now[1]++;
				dem2.x+=mazepixel;	
		}
    }

	else if(dem2.direction==1){
		if(dem2.target[0]>dem2.now[0] && NoWall(dem2.now,3)){
			dem2.direction=3;
			dem2.now[0]++;
			dem2.y-=mazepixel;
		}
        else if(dem2.target[1]<dem2.now[1] && NoWall(dem2.now,1) ){
			dem2.now[1]--;
            dem2.x-=mazepixel;
        }
        else if(!NoWall(dem2.now,1)){
            if(dem2.target[0]>dem2.now[0] && NoWall(dem2.now,3)){
                dem2.direction=3;
				dem2.now[0]++;
                dem2.y-=mazepixel;
            }
            else if(dem2.target[0]<dem2.now[0] && NoWall(dem2.now,2)){
                dem2.direction=2;
				dem2.now[0]--;
                dem2.y+=mazepixel;
            }
			else if(dem2.target[1]>dem2.now[1] && NoWall(dem2.now,0)){
				dem2.direction=0;
				dem2.now[1]++;
				dem2.x+=mazepixel;
			}
			else if(NoWall(dem2.now,3)){
				dem2.direction=3;
				dem2.now[0]++;
				dem2.y-=mazepixel;
			}
			else if(NoWall(dem2.now,2)){
				dem2.direction=2;
				dem2.now[0]--;
				dem2.y+=mazepixel;
			}
			else if(NoWall(dem2.now,0)){
				dem2.direction=0;
				dem2.now[1]++;
				dem2.x+=mazepixel;
			}
        }
		else if(NoWall(dem2.now,1)){
			if(dem2.target[0]<dem2.now[0] && NoWall(dem2.now,2)){
                dem2.direction=2;
				dem2.now[0]--;
                dem2.y+=mazepixel;
            }
			else if(dem2.target[0]>dem2.now[0] && NoWall(dem2.now,3)){
                dem2.direction=3;
				dem2.now[0]++;
                dem2.y-=mazepixel;
            }
			else{
				dem2.now[1]--;
				dem2.x-=mazepixel;
			}
		}
    }
	
	else if(dem2.direction==2){
		// if(dem1.target[1]<dem1.now[1] && NoWall(dem1.now,1)){
		// 	dem1.direction=1;
		// 	dem1.now[1]--;
		// 	dem1.x-=mazepixel;	
		// }
        if(dem2.target[0]<dem2.now[0] && NoWall(dem2.now,2) ){
			dem2.now[0]--;
            dem2.y+=mazepixel;
        }
        else if(!NoWall(dem2.now,2)){
            if(dem2.target[0]>dem2.now[0] && NoWall(dem2.now,3)){
                dem2.direction=3;
				dem2.now[0]++;
                dem2.y-=mazepixel;
            }
			else if(dem2.target[1]>dem2.now[1] && NoWall(dem2.now,0)){
				dem2.direction=0;
				dem2.now[1]++;
				dem2.x+=mazepixel;
			}
            else if(dem2.target[1]<dem2.now[1] && NoWall(dem2.now,1)){
                dem2.direction=1;
				dem2.now[1]--;
                dem2.x-=mazepixel;
            }
			else if(NoWall(dem2.now,3)){
				dem2.direction=3;
				dem2.now[0]++;
				dem2.y-=mazepixel;
			}
			else if(NoWall(dem2.now,0)){
				dem2.direction=0;
				dem2.now[1]++;
				dem2.x+=mazepixel;
			}
			else if(NoWall(dem2.now,1)){
				dem2.direction=1;
				dem2.now[1]--;
				dem2.x-=mazepixel;
			}
        }
		else if(NoWall(dem2.now,2)){
			// if(dem1.target[1]<dem1.now[1] && NoWall(dem1.now,1)){
            //     dem1.direction=1;
			// 	dem1.now[1]--;
            //     dem1.x-=mazepixel;
            // }
			// else if(dem1.target[1]>dem1.now[1] && NoWall(dem1.now,0)){
			// 	dem1.direction=0;
			// 	dem1.now[1]++;
			// 	dem1.x+=mazepixel;
			// }
			// else{
				dem2.now[0]--;
				dem2.y+=mazepixel;
			//}
		}
    }

	else if(dem2.direction==3){
		// if(dem2.target[1]>dem2.now[1] && NoWall(dem2.now,0)){
		// 	dem2.direction=0;
		// 	dem2.now[1]++;
		// 	dem2.x+=mazepixel;	
		// }
        if(dem2.target[0]>dem2.now[0] && NoWall(dem2.now,3) ){
			dem2.now[0]++;
            dem2.y-=mazepixel;
        }
        else if(!NoWall(dem2.now,3)){
            if(dem2.target[0]<dem2.now[0] && NoWall(dem2.now,2)){
                dem2.direction=2;
				dem2.now[0]--;
                dem2.y+=mazepixel;
            }
			else if(dem2.target[1]>dem2.now[1] && NoWall(dem2.now,0)){
				dem2.direction=0;
				dem2.now[1]++;
				dem2.x+=mazepixel;
			}
            else if(dem2.target[1]<dem2.now[1] && NoWall(dem2.now,1)){
                dem2.direction=1;
				dem2.now[1]--;
                dem2.x-=mazepixel;
            }
			else if(NoWall(dem2.now,0)){
				dem2.direction=0;
				dem2.now[1]++;
				dem2.x+=mazepixel;
			}
			else if(NoWall(dem2.now,2)){
				dem2.direction=2;
				dem2.now[0]--;
				dem2.y+=mazepixel;
			}
			else if(NoWall(dem2.now,1)){
				dem2.direction=1;
				dem2.now[1]--;
				dem2.x-=mazepixel;
			}
        }
		else if(NoWall(dem2.now,3)){
			if(dem2.target[1]<dem2.now[1] && NoWall(dem2.now,1)){
                dem2.direction=1;
				dem2.now[1]--;
                dem2.x-=mazepixel;
            }
			else if(dem2.target[1]>dem2.now[1] && NoWall(dem2.now,0)){
				dem2.direction=0;
				dem2.now[1]++;
				dem2.x+=mazepixel;
			}
			else{
				dem2.now[0]++;
				dem2.y-=mazepixel;
			}
		}
    }	
}

void movedem3(){
	dem3.target[0]=harryNow[0];
	dem3.target[1]=harryNow[1];
    if(dem3.direction==0){
        if(dem3.target[1]>dem3.now[1] && NoWall(dem3.now,0) ){
			dem3.now[1]++;
            dem3.x+=mazepixel;
        }
        else if(!NoWall(dem3.now,0)){
            if(dem3.target[0]>dem3.now[0] && NoWall(dem3.now,3)){
                dem3.direction=3;
				dem3.now[0]++;
                dem3.y-=mazepixel;
            }
			else if(dem3.target[1]<dem3.now[1] && NoWall(dem3.now,1)){
				dem3.direction=1;
				dem3.now[1]--;
				dem3.x-=mazepixel;
			}
            else if(dem3.target[0]<dem3.now[0] && NoWall(dem3.now,2)){
                dem3.direction=2;
				dem3.now[0]--;
                dem3.y+=mazepixel;
            }
			else if(NoWall(dem3.now,1)){
				dem3.direction=1;
				dem3.now[1]--;
				dem3.x-=mazepixel;
			}
			else if(NoWall(dem3.now,3)){
				dem3.direction=3;
				dem3.now[0]++;
				dem3.y-=mazepixel;
			}
			else if(NoWall(dem3.now,2)){
				dem3.direction=2;
				dem3.now[0]--;
				dem3.y+=mazepixel;
			}
        }
		else if(NoWall(dem3.now,0)){
			// if(dem3.target[0]>dem3.now[0] && NoWall(dem3.now,3)){
            //     dem3.direction=3;
			// 	dem3.now[0]++;
            //     dem3.y-=mazepixel;
            // }
            // else if(dem3.target[0]<dem3.now[0] && NoWall(dem3.now,2)){
            //     dem3.direction=2;
			// 	dem3.now[0]--;
            //     dem3.y+=mazepixel;
            // }
			//else{
				dem3.direction=0;
				dem3.now[1]++;
				dem3.x+=mazepixel;
			//}
		}
    }

	else if(dem3.direction==1){
		if(dem3.target[0]>dem3.now[0] && NoWall(dem3.now,3)){
			dem3.direction=3;
			dem3.now[0]++;
			dem3.y-=mazepixel;
		}
        else if(dem3.target[1]<dem3.now[1] && NoWall(dem3.now,1) ){
			dem3.now[1]--;
            dem3.x-=mazepixel;
        }
        else if(!NoWall(dem3.now,1)){
            if(dem3.target[0]>dem3.now[0] && NoWall(dem3.now,3)){
                dem3.direction=3;
				dem3.now[0]++;
                dem3.y-=mazepixel;
            }
			else if(dem3.target[1]>dem3.now[1] && NoWall(dem3.now,0)){
				dem3.direction=0;
				dem3.now[1]++;
				dem3.x+=mazepixel;
			}
            else if(dem3.target[0]<dem3.now[0] && NoWall(dem3.now,2)){
                dem3.direction=2;
				dem3.now[0]--;
                dem3.y+=mazepixel;
            }
			else if(NoWall(dem3.now,3)){
				dem3.direction=3;
				dem3.now[0]++;
				dem3.y-=mazepixel;
			}
			else if(NoWall(dem3.now,0)){
				dem3.direction=0;
				dem3.now[1]++;
				dem3.x+=mazepixel;
			}
			else if(NoWall(dem3.now,2)){
				dem3.direction=2;
				dem3.now[0]--;
				dem3.y+=mazepixel;
			}
        }
		else if(NoWall(dem3.now,1)){
			// if(dem3.target[0]>dem3.now[0] && NoWall(dem3.now,3)){
            //     dem3.direction=3;
			// 	dem3.now[0]++;
            //     dem3.y-=mazepixel;
            // }
            // if(dem3.target[0]<dem3.now[0] && NoWall(dem3.now,2)){
            //     dem3.direction=2;
			// 	dem3.now[0]--;
            //     dem3.y+=mazepixel;
            // }
			//else{
				dem3.now[1]--;
				dem3.x-=mazepixel;
			//}
		}
    }
	
	else if(dem3.direction==2){
		if(dem3.target[1]<dem3.now[1] && NoWall(dem3.now,1)){
			dem3.direction=1;
			dem3.now[1]--;
			dem3.x-=mazepixel;	
		}
        else if(dem3.target[0]<dem3.now[0] && NoWall(dem3.now,2) ){
			dem3.direction=2;
			dem3.now[0]--;
            dem3.y+=mazepixel;
        }
        else if(!NoWall(dem3.now,2)){
            if(dem3.target[1]>dem3.now[1] && NoWall(dem3.now,0)){
				dem3.direction=0;
				dem3.now[1]++;
				dem3.x+=mazepixel;
			}
			else if(dem3.target[0]>dem3.now[0] && NoWall(dem3.now,3)){
                dem3.direction=3;
				dem3.now[0]++;
                dem3.y-=mazepixel;
            }
            else if(dem3.target[1]<dem3.now[1] && NoWall(dem3.now,1)){
                dem3.direction=1;
				dem3.now[1]--;
                dem3.x-=mazepixel;
            }
			else if(NoWall(dem3.now,1)){
				dem3.direction=1;
				dem3.now[1]--;
				dem3.x-=mazepixel;
			}
			else if(NoWall(dem3.now,0)){
				dem3.direction=0;
				dem3.now[1]++;
				dem3.x+=mazepixel;
			}
			else if(NoWall(dem3.now,3)){
				dem3.direction=3;
				dem3.now[0]++;
				dem3.y-=mazepixel;
			}
        }
		else if(NoWall(dem3.now,2)){
			if(dem3.target[1]>dem3.now[1] && NoWall(dem3.now,0)){
				dem3.direction=0;
				dem3.now[1]++;
				dem3.x+=mazepixel;
			}
			else if(dem3.target[1]<dem3.now[1] && NoWall(dem3.now,1)){
                dem3.direction=1;
				dem3.now[1]--;
                dem3.x-=mazepixel;
            }
			else{
				dem3.now[0]--;
				dem3.y+=mazepixel;
			}
		}
    }

	else if(dem3.direction==3){
		if(dem3.target[1]>dem1.now[1] && NoWall(dem3.now,0)){
			dem3.direction=0;
			dem3.now[1]++;
			dem3.x+=mazepixel;	
		}
        if(dem3.target[0]>dem3.now[0] && NoWall(dem3.now,3) ){
			dem3.now[0]++;
            dem3.y-=mazepixel;
        }
        else if(!NoWall(dem3.now,3 )){
			if(dem3.target[1]>dem3.now[1] && NoWall(dem3.now,0)){
				dem3.direction=0;
				dem3.now[1]++;
				dem3.x+=mazepixel;
			}
            else if(dem3.target[0]<dem3.now[0] && NoWall(dem3.now,2)){
                dem3.direction=2;
				dem3.now[0]--;
                dem3.y+=mazepixel;
            }
            else if(dem3.target[1]<dem3.now[1] && NoWall(dem3.now,1)){
                dem3.direction=1;
				dem3.now[1]--;
                dem3.x-=mazepixel;
            }
			else if(NoWall(dem3.now,2)){
				dem3.direction=2;
				dem3.now[0]--;
				dem3.y+=mazepixel;
			}
			else if(NoWall(dem3.now,1)){
				dem3.direction=1;
				dem3.now[1]--;
				dem3.x-=mazepixel;
			}
			else if(NoWall(dem3.now,0)){
				dem3.direction=0;
				dem3.now[1]++;
				dem3.x+=mazepixel;
			}
        }
		else if(NoWall(dem3.now,3)){
			if(dem3.target[1]>dem3.now[1] && NoWall(dem3.now,0)){
				dem3.direction=0;
				dem3.now[1]++;
				dem3.x+=mazepixel;
			}
			else if(dem3.target[1]<dem3.now[1] && NoWall(dem3.now,1)){
                dem3.direction=1;
				dem3.now[1]--;
                dem3.x-=mazepixel;
            }
			else{
				dem3.now[0]++;
				dem3.y-=mazepixel;
			}
		}
    }	
}

void movebasil(){
	basil.target[0]=harryNow[0];
	basil.target[1]=harryNow[1];
    if(basil.direction==0){
        if(basil.target[1]>basil.now[1] && NoWall(basil.now,0) ){
			basil.now[1]++;
            basil.x+=mazepixel;
        }
        else if(!NoWall(basil.now,0)){
            if(basil.target[0]>basil.now[0] && NoWall(basil.now,3)){
                basil.direction=3;
				basil.now[0]++;
                basil.y-=mazepixel;
            }
            else if(basil.target[0]<basil.now[0] && NoWall(basil.now,2)){
                basil.direction=2;
				basil.now[0]--;
                basil.y+=mazepixel;
            }
			else if(basil.target[1]<basil.now[1] && NoWall(basil.now,1)){
				basil.direction=1;
				basil.now[1]--;
				basil.x-=mazepixel;
			}
			else if(NoWall(basil.now,3)){
				basil.direction=3;
				basil.now[0]++;
				basil.y-=mazepixel;
			}
			else if(NoWall(basil.now,2)){
				basil.direction=2;
				basil.now[0]--;
				basil.y+=mazepixel;
			}
			else if(NoWall(basil.now,1)){
				basil.direction=1;
				basil.now[1]--;
				basil.x-=mazepixel;
			}
        }
		else if(NoWall(basil.now,0)){
			if(basil.target[0]>basil.now[0] && NoWall(basil.now,3)){
                basil.direction=3;
				basil.now[0]++;
                basil.y-=mazepixel;
            }
            else if(basil.target[0]<basil.now[0] && NoWall(basil.now,2)){
                basil.direction=2;
				basil.now[0]--;
                basil.y+=mazepixel;
            }
			else{
				basil.direction=0;
				basil.now[1]++;
				basil.x+=mazepixel;
			}
		}
    }

	else if(basil.direction==1){
		if(basil.target[0]>basil.now[0] && NoWall(basil.now,3)){
			basil.direction=3;
			basil.now[0]++;
			basil.y-=mazepixel;
		}
        else if(basil.target[1]<basil.now[1] && NoWall(basil.now,1) ){
			basil.now[1]--;
            basil.x-=mazepixel;
        }
        else if(!NoWall(basil.now,1)){
            if(basil.target[0]>basil.now[0] && NoWall(basil.now,3)){
                basil.direction=3;
				basil.now[0]++;
                basil.y-=mazepixel;
            }
            else if(basil.target[0]<basil.now[0] && NoWall(basil.now,2)){
                basil.direction=2;
				basil.now[0]--;
                basil.y+=mazepixel;
            }
			else if(basil.target[1]>basil.now[1] && NoWall(basil.now,0)){
				basil.direction=0;
				basil.now[1]++;
				basil.x+=mazepixel;
			}
			else if(NoWall(basil.now,3)){
				basil.direction=3;
				basil.now[0]++;
				basil.y-=mazepixel;
			}
			else if(NoWall(basil.now,2)){
				basil.direction=2;
				basil.now[0]--;
				basil.y+=mazepixel;
			}
			else if(NoWall(basil.now,0)){
				basil.direction=0;
				basil.now[1]++;
				basil.x+=mazepixel;
			}
        }
		else if(NoWall(basil.now,1)){
			if(basil.target[0]>basil.now[0] && NoWall(basil.now,3)){
                basil.direction=3;
				basil.now[0]++;
                basil.y-=mazepixel;
            }
            else if(basil.target[0]<basil.now[0] && NoWall(basil.now,2)){
                basil.direction=2;
				basil.now[0]--;
                basil.y+=mazepixel;
            }
			else{
				basil.now[1]--;
				basil.x-=mazepixel;
			}
		}
    }
	
	else if(basil.direction==2){
        if(basil.target[0]<basil.now[0] && NoWall(basil.now,2) ){
			basil.direction=2;
			basil.now[0]--;
            basil.y+=mazepixel;
        }
        else if(!NoWall(basil.now,2)){
            if(basil.target[1]>basil.now[1] && NoWall(basil.now,0)){
				basil.direction=0;
				basil.now[1]++;
				basil.x+=mazepixel;
			}
            else if(basil.target[1]<basil.now[1] && NoWall(basil.now,1)){
                basil.direction=1;
				basil.now[1]--;
                basil.x-=mazepixel;
            }
			else if(basil.target[0]>basil.now[0] && NoWall(basil.now,3)){
                basil.direction=3;
				basil.now[0]++;
                basil.y-=mazepixel;
            }
			else if(NoWall(basil.now,1)){
				basil.direction=1;
				basil.now[1]--;
				basil.x-=mazepixel;
			}
			else if(NoWall(basil.now,3)){
				basil.direction=3;
				basil.now[0]++;
				basil.y-=mazepixel;
			}
			else if(NoWall(basil.now,0)){
				basil.direction=0;
				basil.now[1]++;
				basil.x+=mazepixel;
			}
        }
		else if(NoWall(basil.now,2)){
			// if(basil.target[1]>basil.now[1] && NoWall(basil.now,0)){
			// 	basil.direction=0;
			// 	basil.now[1]++;
			// 	basil.x+=mazepixel;
			// }
			// else if(basil.target[1]<basil.now[1] && NoWall(basil.now,1)){
            //     basil.direction=1;
			// 	basil.now[1]--;
            //     basil.x-=mazepixel;
            // }
			//else{
				basil.now[0]--;
				basil.y+=mazepixel;
			//}
		}
    }

	else if(basil.direction==3){
		// if(basil.target[1]>dem1.now[1] && NoWall(basil.now,0)){
		// 	basil.direction=0;
		// 	basil.now[1]++;
		// 	basil.x+=mazepixel;	
		// }
        if(basil.target[0]>basil.now[0] && NoWall(basil.now,3) ){
			basil.now[0]++;
            basil.y-=mazepixel;
        }
        else if(!NoWall(basil.now,3 )){
			if(basil.target[1]>basil.now[1] && NoWall(basil.now,0)){
				basil.direction=0;
				basil.now[1]++;
				basil.x+=mazepixel;
			}
            else if(basil.target[1]<basil.now[1] && NoWall(basil.now,1)){
                basil.direction=1;
				basil.now[1]--;
                basil.x-=mazepixel;
            }
			else if(basil.target[0]<basil.now[0] && NoWall(basil.now,2)){
                basil.direction=2;
				basil.now[0]--;
                basil.y+=mazepixel;
            }
			else if(NoWall(basil.now,2)){
				basil.direction=2;
				basil.now[0]--;
				basil.y+=mazepixel;
			}
			else if(NoWall(basil.now,1)){
				basil.direction=1;
				basil.now[1]--;
				basil.x-=mazepixel;
			}
			else if(NoWall(basil.now,0)){
				basil.direction=0;
				basil.now[1]++;
				basil.x+=mazepixel;
			}
        }
		else if(NoWall(basil.now,3)){
			// if(basil.target[1]>basil.now[1] && NoWall(basil.now,0)){
			// 	basil.direction=0;
			// 	basil.now[1]++;
			// 	basil.x+=mazepixel;
			// }
			// else if(basil.target[1]<basil.now[1] && NoWall(basil.now,1)){
            //     basil.direction=1;
			// 	basil.now[1]--;
            //     basil.x-=mazepixel;
            // }
			//else{
				basil.now[0]++;
				basil.y-=mazepixel;
			//}
		}
    }	
}

void movedementor(){
	iShowBMP2(dem1.x, dem1.y, dementorright[0], 255);
	iShowBMP2(dem2.x, dem2.y, dementorright[0], 255);
	iShowBMP2(dem3.x, dem3.y, dementorright[0], 255);
	iShowBMP2(basil.x, basil.y, basiliskright[0], 0);
}

void Harrymove(){
	if(harry.rightCount){
		harry.x+=mazepixel;
        harryNow[1]++;
		if(maze[mazeLevel][harryNow[0]][harryNow[1]]==2){
			snitchCollected++;
			point++;
			maze[mazeLevel][harryNow[0]][harryNow[1]]=0;
		}
		if(maze[mazeLevel][harryNow[0]][harryNow[1]]==3){
			snitchCollected++;
			point+=5;
			maze[mazeLevel][harryNow[0]][harryNow[1]]=0;
		}
		harry.rightInd++;
        if(harry.rightInd>1) harry.rightInd=0;
        harry.rightCount=false;
	}
	if(harry.leftCount){
		harry.x-=mazepixel;
        harryNow[1]--;
		if(maze[mazeLevel][harryNow[0]][harryNow[1]]==2){
			snitchCollected++;
			point++;
			maze[mazeLevel][harryNow[0]][harryNow[1]]=0;
		}
		if(maze[mazeLevel][harryNow[0]][harryNow[1]]==3){
			snitchCollected++;
			point+=5;
			maze[mazeLevel][harryNow[0]][harryNow[1]]=0;
		}
		harry.leftInd++;
        if(harry.leftInd>1) harry.leftInd=0;
        harry.leftCount=false;
	}
	if(harry.upCount){
		harry.y+=mazepixel;
        harryNow[0]--;
		if(maze[mazeLevel][harryNow[0]][harryNow[1]]==2){
			snitchCollected++;
			point++;
			maze[mazeLevel][harryNow[0]][harryNow[1]]=0;
		}
		if(maze[mazeLevel][harryNow[0]][harryNow[1]]==3){
			snitchCollected++;
			point+=5;
			maze[mazeLevel][harryNow[0]][harryNow[1]]=0;
		}
		harry.upInd++;
        if(harry.upInd>1) harry.upInd=0;
        harry.upCount=false;
	}
	if(harry.downCount){
		harry.y-=mazepixel;
        harryNow[0]++;
		if(maze[mazeLevel][harryNow[0]][harryNow[1]]==2){
			snitchCollected++;
			point++;
			maze[mazeLevel][harryNow[0]][harryNow[1]]=0;
		}
		if(maze[mazeLevel][harryNow[0]][harryNow[1]]==3){
			snitchCollected++;
			point+=5;
			maze[mazeLevel][harryNow[0]][harryNow[1]]=0;
		}
		harry.downInd++;
        if(harry.downInd>1) harry.downInd=0;
        harry.downCount=false;
	}
}

void  Harrydeadcheck(){
	if(harryNow[0]==dem1.now[0] && harryNow[1]==dem1.now[1]){
		harrydead=true;
	}
	else if(harryNow[0]==dem2.now[0] && harryNow[1]==dem2.now[1]){
		harrydead=true;
	}
	else if(harryNow[0]==dem3.now[0] && harryNow[1]==dem3.now[1]){
		harrydead=true;
	}
	else if(harryNow[0]==basil.now[0] && harryNow[1]==basil.now[1]){
		harrydead=true;
	}
}

void lifecheck(){
	if(harrydead){
		harrydead=false;
		iShowBMP2(harry.x,harry.y,harrydeadscene[0],0);
		harryinitial();
		dementorinitial();
		if(life==3){
			life=2;
		}
		else if(life==2){
			life=1;
		}
		else if(life==1){
			gameover=true;
			playgame=false;
		}
	}
}

int main() {
	harryinitial();
	dementorinitial();
	iSetTimer(dementortime,movedem1);
	iSetTimer(dementortime,movedem2);
	iSetTimer(dementortime,movedem3);
	iSetTimer(dementortime,movebasil);
	// iSetTimer(10, Harrydeadcheck);
	// iSetTimer(10,lifecheck);
	//iSetTimer(harrytime,Harrymove);
	//place your own initialization codes here.
	iInitialize(screenwidth, screenheight, "Dotly Hallows");
	return 0;
}
