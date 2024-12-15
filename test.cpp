
#include "iGraphics.h"
#include<time.h>
#include<stdlib.h>
#include<stdbool.h>
#include<Windows.h>
#include<iostream>
#include<string>
#define screenheight 850
#define screenwidth 800
#define mazepixel 40// all of the sprites...harry demnetors....snitches eveerything is 40*40

void drawmaze();
void Harrymove();
void dementorinitial();
void harryinitial();
void movedementor();
void movedem1();
void movedem2();
void movedem3();
void movebasil();
void Harrydeadcheck();
void lifecheck();
void soundMoldy();
void newgame();
void targetchange();
void timerFunction();
void dem1deadtolife ();
void dem2deadtolife ();
void dem3deadtolife ();
void update();
void timeID();
void appendScoreToFile(const char* name, int score);
void sortScoresInFile();
void showHighScore();
int compareScores(const void *a, const void *b);
int dementortime=340;
int brickNum;
int snitchesNum;
int mazeHeight = 840;
int mazeWidth = 760;
int mazeX = (screenwidth / 2) - (mazeWidth / 2)+3;
int mazeY = (screenheight / 2) - (mazeHeight / 2)-5;
int mazeLevel = 0;
int mazeXcor[200];
int mazeYcor[200];
int snitchXcor[210][2];
int snitchYcor[210];
int hocrux[210];
int harryNow[2]={19,9};
int snitchCollected=0;
int deathtime=5;
char score[1000];
int point=0;
int life=3;
bool harrydead=false;
bool gameover=false;
bool playgame=false;
bool gamewin=false;
bool gamewinsound=false;
bool mainmenu=true;
bool musicOn=true;
bool deaddialouge=false;
bool powerup=false;
int power_counter=0;
int morse_na_morenai[4]={0,0,0,0};
bool instructions=false;
bool HallOfFame=false;
bool nameinput=false;
int dem1initX = 8;
int dem1initY = 9;
int dem2initX = 1;
int dem2initY = 1;
int dem3initX = 10;
int dem3initY = 9;
int basilinitX = 9;
int basilinitY = 8;
bool entername=false;
int timerCount=0;
int timerID;
int indexnumber=0;
int poweruptime=9;
char str[1000]="";
bool totalsound=true;

#define MAX_ENTRIES 100
#define MAX_DISPLAYED_SCORES 3
#define MAX_LINE_LENGTH 100
typedef struct {
    char name[MAX_LINE_LENGTH];
    int score;
} Entry;

typedef struct{
	int upInd, downInd, leftInd, rightInd;
    int x;
    int y;
    int lastcount;
    bool upCount, downCount, leftCount, rightCount;
    int right, left, up, down;
	bool dead;
	int deadtime;
    int direction;
	int now[2];
	int target[2];
	int timerid;
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

int original[3][21][19] =
{
	{
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,2,2,3,2,2,2,2,2,1,2,2,2,2,2,2,2,2,1,
		1,2,1,1,2,1,1,1,2,1,2,1,1,1,2,1,1,2,1,
		1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,3,2,2,1,
		1,2,1,1,2,1,2,1,1,1,1,1,2,1,2,1,1,2,1,
		1,2,2,2,2,1,2,2,2,1,2,2,2,1,2,2,2,2,1,
		1,1,1,1,2,1,1,1,2,1,3,1,1,1,2,1,1,1,1,
		0,0,0,1,2,1,2,2,2,2,2,2,2,1,2,1,0,0,0,
		1,1,1,1,2,1,2,1,1,2,1,1,2,1,2,1,1,1,1,
		1,2,2,2,2,2,2,1,2,2,2,1,2,2,2,2,2,2,1,
		1,1,1,1,2,1,2,1,1,0,1,1,2,1,2,1,1,1,1,
		0,0,0,1,2,1,2,2,2,2,3,2,2,1,2,1,0,0,0,
		1,1,1,1,2,1,2,1,1,1,1,1,2,1,2,1,1,1,1,
		1,2,2,2,2,2,3,2,2,1,2,2,2,2,2,2,2,2,1,
		1,2,1,1,2,1,1,1,2,1,2,1,2,1,2,1,1,2,1,
		1,2,2,1,2,2,2,2,2,2,2,2,2,2,2,1,2,2,1,
		1,1,2,1,2,1,2,1,1,1,1,1,2,1,2,1,2,1,1,
		1,2,2,2,2,1,2,2,2,1,2,2,2,1,2,3,2,2,1,
		1,2,1,1,1,1,1,1,2,1,2,1,1,1,1,1,1,2,1,
		1,2,2,2,2,2,2,2,2,0,2,2,2,2,2,2,2,2,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	},
	{
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,2,3,2,2,2,1,2,2,2,2,2,1,2,2,2,2,3,1,
		1,2,1,1,1,2,1,1,2,1,2,1,1,2,1,1,1,2,1,
		1,2,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1,2,1,
		1,2,2,2,1,2,1,1,2,1,2,1,1,2,1,2,2,2,1,
		1,1,1,1,1,2,2,2,2,1,3,2,2,2,1,1,1,1,1,
		1,2,2,2,1,2,1,1,1,1,1,1,1,2,1,2,2,2,1,
		1,2,1,2,2,2,2,2,2,2,2,2,2,2,2,2,1,2,1,
		1,2,1,1,2,1,2,1,1,2,1,1,2,1,2,1,1,2,1,
		1,2,2,2,2,1,2,1,2,3,2,1,2,1,2,2,2,2,1,
		1,2,1,2,1,1,2,1,1,0,1,1,2,1,1,3,1,2,1,
		1,2,1,2,2,2,2,2,2,2,2,2,2,2,2,2,1,2,1,
		1,2,1,1,2,1,1,1,2,1,2,1,1,1,2,1,1,2,1,
		1,2,2,2,2,1,2,2,2,1,2,2,2,1,2,2,2,2,1,
		1,1,2,1,2,1,2,1,1,1,1,1,2,1,2,1,2,1,1,
		1,2,2,1,2,2,2,2,2,2,2,2,2,2,3,1,2,2,1,
		1,2,1,1,2,1,1,1,2,1,2,1,1,1,2,1,1,2,1,
		1,2,3,2,2,1,2,2,2,1,2,2,2,1,2,2,2,2,1,
		1,2,1,1,2,1,2,1,1,1,1,1,2,1,2,1,1,2,1,
		1,2,2,2,2,1,2,2,2,0,2,2,2,1,2,2,2,3,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
	}
    ,
    {
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,2,2,1,2,2,2,2,2,2,2,1,2,2,2,2,2,2,1,
		1,2,1,1,1,2,1,1,1,1,1,1,1,1,1,2,1,2,1,
		1,2,1,2,2,2,1,2,2,2,2,2,2,2,2,2,1,2,1,
		1,2,1,2,1,2,1,1,1,1,1,1,1,1,1,1,1,2,1,
		1,2,1,2,1,2,2,2,2,2,2,2,2,2,1,1,1,2,1,
		1,2,1,2,1,2,1,1,1,1,1,1,1,2,2,2,2,2,1,
		1,2,2,2,1,2,2,1,2,2,2,1,1,2,1,1,1,2,1,
		1,2,1,2,1,2,1,1,2,5,2,1,2,2,1,2,1,2,1,
		1,2,1,2,1,2,2,1,1,2,1,1,1,2,1,2,1,2,1,
		1,1,1,2,1,2,1,1,2,2,2,2,2,2,1,2,1,1,1,
		1,2,1,1,1,2,2,2,2,1,1,1,1,1,1,2,1,2,1,
		1,2,1,2,1,2,1,1,1,1,2,2,2,2,2,2,1,2,1,
		1,2,1,2,1,2,2,2,1,2,2,1,2,2,1,2,2,2,1,
		1,2,2,2,1,2,1,1,1,2,2,1,2,1,1,1,1,2,1,
		1,2,1,2,1,2,2,2,2,2,2,1,1,1,1,1,1,2,1,
		1,2,1,2,1,1,1,1,1,1,2,2,2,2,2,2,1,2,1,
		1,2,1,2,2,2,2,2,2,1,2,2,1,2,2,1,1,2,1,
		1,2,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,2,1,
		1,2,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1

    }
};

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
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,2,2,2,1,1,2,2,3,1,2,2,2,2,2,1,2,2,1,
		1,2,2,2,2,2,2,2,1,2,2,2,2,1,2,1,2,2,1,
		1,2,1,1,2,1,2,2,1,2,2,2,1,1,2,2,3,1,1,
		1,2,1,2,2,1,2,1,1,2,2,2,1,1,1,2,2,1,1,
		1,2,1,3,2,1,2,1,2,2,1,2,1,2,1,2,2,2,1,
		1,2,1,2,2,1,2,1,2,1,1,2,1,2,1,1,2,2,1,
		1,3,1,2,1,1,1,1,2,2,1,2,1,2,1,2,2,2,1,
		1,2,1,2,1,1,1,1,1,2,1,1,1,2,2,2,2,2,1,
		1,2,1,2,2,2,2,1,2,5,2,1,1,1,1,1,2,1,1,
		1,2,1,1,2,1,2,1,1,2,1,1,1,2,2,2,2,1,1,
		1,2,1,3,2,2,2,2,1,3,1,2,2,2,1,2,3,1,1,
		1,2,1,2,2,1,1,1,1,2,1,2,1,1,1,1,2,2,1,
		1,2,1,2,2,2,2,2,2,2,2,2,1,2,1,2,2,1,1,
		1,2,1,1,2,2,1,2,1,1,2,1,2,2,2,2,2,2,1,
		1,2,2,1,2,2,1,1,1,1,1,1,1,1,1,1,2,2,1,
		1,2,2,1,1,2,2,2,1,2,2,2,1,2,2,2,2,2,1,
		1,2,1,1,1,3,1,2,2,3,1,2,2,2,2,2,1,2,1,
		1,2,1,1,1,2,1,1,1,1,2,1,1,1,1,2,1,2,1,
		1,2,2,2,2,2,2,2,1,2,2,2,2,2,2,2,1,3,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
    }
};

char BGImg[4][30] = {"assets\\BG2.bmp","assets\\BG3.bmp"};
char mazeWall[2][30]={"assets\\wall.bmp","assets\\tree.bmp"};
char snitch[3][39]={"assets\\snitch4.bmp","assets\\Sortinghat2.bmp","assets\\cup\\cup.bmp"};
char harrydown[9][100]={"assets\\harry3\\tile001.bmp","assets\\harry3\\tile002.bmp"};
char harryup[9][100]={"assets\\harry3\\tile009.bmp","assets\\harry3\\tile010.bmp"};
char harryright[9][100]={"assets\\harry3\\tile027.bmp","assets\\harry3\\tile028.bmp"};
char harryleft[9][100]={"assets\\harry3\\tile018.bmp","assets\\harry3\\tile019.bmp"};
char dementorright[1][100]={"assets\\dementor\\rightdementor.bmp"};
char dementorleft[1][100]={"assets\\dementor\\leftdementor.bmp"};
char dementordown[1][100]={"assets\\dementor\\downdementor.bmp"};
char dementorup[1][100]={"assets\\dementor\\updementor.bmp"};
char basiliskright[3][100]={"assets\\basilisk\\tile000.bmp","assets\\basilisk\\tile001.bmp","assets\\basilisk\\tile002.bmp"};
char basiliskleft[3][100]={"assets\\basilisk\\left000.bmp","assets\\basilisk\\left001.bmp","assets\\basilisk\\left002.bmp"};
char heart[1][100]={"assets\\heart\\000.bmp"};
char harrydeadscene[1][100]={"assets\\harrydead\\000.bmp"};
char gameoverscene[1][100]={"assets\\Gameover.bmp"};
char mainmenuscene[1][100]={"assets\\mainmenu.bmp"};
char instructionscene[1][100]={"assets\\instructions.bmp"};
char deaddementor[1][100]={"assets\\dead\\deaddementor.bmp"};
char gamewinscene[1][100]={"assets\\GameWin.bmp"};
char HallOfFamescene[1][100]={"assets\\HallOfFame.bmp"};
char nameinputscene[1][100]={"assets\\NameInput.bmp"};
char soundscene[2][100]={"assets\\pic\\On.bmp","assets\\pic\\off.bmp"};
//int x=500, y = 300, r = 20;
/*
	function iDraw() is called again and again by the system.

	*/


void iDraw() {
	//place your drawing codes here
	iClear();
	iShowBMP(0,0,BGImg[0]);
	if(mainmenu){
		iShowBMP(0,0,mainmenuscene[0]);
		if(totalsound)
			iShowBMP2(720,770,soundscene[0],0);
		else
			iShowBMP2(720,770,soundscene[1],0);
	}
	if(HallOfFame){
		iShowBMP(0,0,HallOfFamescene[0]);
		sortScoresInFile(); 
		showHighScore();
	}
	if(instructions){
		iShowBMP(0,0,instructionscene[0]);
	}
	if(nameinput){
		iShowBMP(0,0,nameinputscene[0]);
		iSetColor(0,0,0);
		iText(350,282,str,GLUT_BITMAP_HELVETICA_18);
	}
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
		iSetColor(255,255,255);
		iText(590, 815, "SCORE: ",GLUT_BITMAP_HELVETICA_18);
		sprintf(score,"%d",point);
		iText(662, 815, score,GLUT_BITMAP_HELVETICA_18);
		movedementor();

				if (harry.rightCount){
					Harrymove();
					iShowBMP2(harry.x, harry.y, harryright[harry.rightInd], 16777215);
					}
				else if (harry.leftCount){
					Harrymove();
					iShowBMP2(harry.x, harry.y, harryleft[harry.leftInd], 16777215);
				}
				else if (harry.upCount){
					Harrymove();
					iShowBMP2(harry.x, harry.y, harryup[harry.upInd], 16777215);
				}
				else if (harry.downCount){
					Harrymove();
					iShowBMP2(harry.x, harry.y, harrydown[harry.downInd], 16777215);
				}
				else{
					Harrymove();
					if(harry.lastcount==0)
						iShowBMP2(harry.x, harry.y, harryright[harry.rightInd], 16777215);
					else if(harry.lastcount==1)
						iShowBMP2(harry.x, harry.y, harryleft[harry.leftInd], 16777215);
					else if(harry.lastcount==2)
						iShowBMP2(harry.x, harry.y, harryup[harry.upInd], 16777215);
					else
						iShowBMP2(harry.x, harry.y, harrydown[harry.downInd], 16777215);
				}
	}
	if(gameover){
		iShowBMP(0,0,gameoverscene[0]);
	}
	if(gamewin){
		iShowBMP(0,0,gamewinscene[0]);
	}
}
		
	void harryinitial(){
		harryNow[0]=19;
		harryNow[1]=9;
		harry.x = mazeX + harryNow[1]*mazepixel;
		harry.y = mazeY + (20-harryNow[0])*mazepixel;
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
				powerup=false;
				timerCount=0;
				dem1.deadtime=0;
				dem2.deadtime=0;
				dem3.deadtime=0;
				dem1.dead=false;
				dem2.dead=false;
				dem3.dead=false;
				poweruptime=7;
				deathtime=3;
				//newgame(mazeLevel);
			}
			if(snitchCollected==385 && mazeLevel==1){
				harryinitial();
				dementorinitial();
				mazeLevel=2;
				dementortime=250;
				poweruptime=5;
				deathtime=2;
				powerup=false;
				timerCount=0;
				dem1.deadtime=0;
				dem2.deadtime=0;
				dem3.deadtime=0;
				dem1.dead=false;
				dem2.dead=false;
				dem3.dead=false;
			}
    for (int i = 20; i >= 0; i--) {
        for (int j = 0; j < 19; j++) {
            if (maze[mazeLevel][i][j]==1) {
				brickNum=c++;
                mazeXcor[brickNum] = mazepixel * j;
                mazeYcor[brickNum] = mazepixel * (20-i);
				iShowBMP(mazeX + mazeXcor[brickNum], mazeY + mazeYcor[brickNum], mazeWall[1]);
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
			else if(maze[mazeLevel][i][j]==5)
				{
					snitchesNum=t++;
					snitchXcor[snitchesNum][0] = mazepixel*j;
					snitchYcor[snitchesNum] = mazepixel*(20-i);
					snitchXcor[snitchesNum][1] = 0;
					iShowBMP2(mazeX + snitchXcor[snitchesNum][0], mazeY + snitchYcor[snitchesNum],snitch[2],0 );
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
		if(mainmenu){
			if((mx>=337 && mx<=460) && (my>=302 && my<=380)){
				mainmenu=false;
				nameinput=true;
			}
			if((mx>=287 && mx<=535) && (my>=101 && my<=162)){
				mainmenu=false;
				instructions=true;
			}
			if((mx>=267 && mx<=554) && (my>=213 && my<=272)){
				mainmenu=false;
				HallOfFame=true;
			}
			if((mx>=720 && mx<=800) && (my>=770 && my<=850)){
				if(totalsound){
					totalsound=false;
					musicOn=false;
					PlaySound(0,0,0);
				}
				else{
					totalsound=true;
					musicOn=true;
					soundMoldy();
				}
			}
		}
		if(HallOfFame){
			if((mx>=4 && mx<=114) && (my>=800 && my<=850)){
				HallOfFame=false;
				mainmenu=true;
			}
		}
		if(instructions){
			if((mx>=21 && mx<=149) && (my>=777 && my<=828)){
				instructions=false;
				mainmenu=true;
			}
		}
		if(gameover){
			if((mx>=277 && mx<=517) && (my>=207 && my<=281)){
				gameover=false;
				mainmenu=true;
				if(totalsound){
					if(deaddialouge){
						deaddialouge=false;
						PlaySound(0,0,0);
						musicOn=true;
						if(musicOn){
							PlaySound(TEXT("assets\\sound\\gamesound.WAV"), NULL,SND_LOOP | SND_ASYNC );
						}
					}
				}
			}
			if((mx>=291 && mx<=507) && (my>=102 && my<=172)){
				exit(0);
			}
		}
		if(gamewin){
			if((mx>=249 && mx<=551) && (my>=146 && my<=235)){
				gamewin=false;
				mainmenu=true;
				if(totalsound){
					if(gamewinsound){
						gamewinsound=false;
						PlaySound(0,0,0);
						musicOn=true;
						if(musicOn){
							PlaySound(TEXT("assets\\sound\\gamesound.WAV"), NULL,SND_LOOP | SND_ASYNC );
						}
					}
				}
			}
			if((mx>=260 && mx<=537) && (my>=36 && my<=112)){
				exit(0);
			}
		}
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
	//printf("Key pressed: %c (%d)\n", key, key);
	if (nameinput) {
        if (key == '\r') {  
			//sortScoresInFile();
            nameinput = false;
            playgame = true;
            newgame();  
        } else if (key == '\b') {  
            if (indexnumber > 0) {
                indexnumber--;
                str[indexnumber] = '\0'; 
            }
        } else {
            if (indexnumber < 999) {  
                str[indexnumber] = key;
                indexnumber++;
                str[indexnumber] = '\0';  
            } 
			// else {
            //     printf("Name input is too long!\n"); 
            // }
        }
    }
    
    if (key == 'q' || key == 'Q') { 
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
				//printf("%d %d\n",harryNow[0],harryNow[1]);
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
				//printf("%d %d\n",harryNow[0],harryNow[1]);
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
                //printf("%d %d\n",harryNow[0],harryNow[1]);
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
				//printf("%d %d\n",harryNow[0],harryNow[1]);
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
		dem1.lastcount=0;
		dem1.target[0]=harryNow[0];
		dem1.target[1]=harryNow[1];
		dem1.deadtime=0;
		
		dem2.now[0]=1;
		dem2.now[1]=1;
		dem2.lastcount=0;
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
		dem2.deadtime=0;

		dem3.now[0]=9;
		dem3.now[1]=10;
		dem3.lastcount=0;
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
		dem3.deadtime=0;

		basil.now[0]=8;
		basil.now[1]=9;
		basil.lastcount=0;
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
		basil.deadtime=0;
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
			dem1.lastcount=0;
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
				dem1.lastcount=1;
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
				dem1.lastcount=1;
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
				dem1.lastcount=0;
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
			dem1.lastcount=1;
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
				dem1.lastcount=0;
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
				dem1.lastcount=0;
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
				dem1.lastcount=1;
			}
		}
    }
	
	else if(dem1.direction==2){
		if(dem1.target[1]<dem1.now[1] && NoWall(dem1.now,1)){
			dem1.direction=1;
			dem1.now[1]--;
			dem1.x-=mazepixel;	
			dem1.lastcount=1;
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
				dem1.lastcount=0;
			}
            else if(dem1.target[1]<dem1.now[1] && NoWall(dem1.now,1)){
                dem1.direction=1;
				dem1.now[1]--;
                dem1.x-=mazepixel;
				dem1.lastcount=1;
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
				dem1.lastcount=1;
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
				dem1.lastcount=0;
			}
        }
		else if(NoWall(dem1.now,2)){
			if(dem1.target[1]>dem1.now[1] && NoWall(dem1.now,0)){
				dem1.direction=0;
				dem1.now[1]++;
				dem1.x+=mazepixel;
				dem1.lastcount=0;
			}
			else if(dem1.target[1]<dem1.now[1] && NoWall(dem1.now,1)){
                dem1.direction=1;
				dem1.now[1]--;
                dem1.x-=mazepixel;
				dem1.lastcount=1;
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
				dem1.lastcount=1;
            }
			else if(dem1.target[1]>dem1.now[1] && NoWall(dem1.now,0)){
				dem1.direction=0;
				dem1.now[1]++;
				dem1.x+=mazepixel;
				dem1.lastcount=0;
			}
			else if(NoWall(dem1.now,1)){
				dem1.direction=1;
				dem1.now[1]--;
				dem1.x-=mazepixel;
				dem1.lastcount=1;
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
				dem1.lastcount=0;
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
				dem1.lastcount=1;
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
			dem2.lastcount=0;
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
				dem2.lastcount=1;
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
				dem2.lastcount=1;
			}
        }
		else if(NoWall(dem2.now,0)){
				dem2.direction=0;
				dem2.now[1]++;
				dem2.x+=mazepixel;	
				dem2.lastcount=0;
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
			dem2.lastcount=1;
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
				dem2.lastcount=0;
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
				dem2.lastcount=0;
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
				dem2.lastcount=1;
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
				dem2.lastcount=0;
			}
            else if(dem2.target[1]<dem2.now[1] && NoWall(dem2.now,1)){
                dem2.direction=1;
				dem2.now[1]--;
                dem2.x-=mazepixel;
				dem2.lastcount=1;
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
				dem2.lastcount=0;
			}
			else if(NoWall(dem2.now,1)){
				dem2.direction=1;
				dem2.now[1]--;
				dem2.x-=mazepixel;
				dem2.lastcount=1;
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
				dem2.lastcount=0;
			}
            else if(dem2.target[1]<dem2.now[1] && NoWall(dem2.now,1)){
                dem2.direction=1;
				dem2.now[1]--;
                dem2.x-=mazepixel;
				dem2.lastcount=1;
            }
			else if(NoWall(dem2.now,0)){
				dem2.direction=0;
				dem2.now[1]++;
				dem2.x+=mazepixel;
				dem2.lastcount=0;
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
				dem2.lastcount=1;
			}
        }
		else if(NoWall(dem2.now,3)){
			if(dem2.target[1]<dem2.now[1] && NoWall(dem2.now,1)){
                dem2.direction=1;
				dem2.now[1]--;
                dem2.x-=mazepixel;
				dem2.lastcount=1;
            }
			else if(dem2.target[1]>dem2.now[1] && NoWall(dem2.now,0)){
				dem2.direction=0;
				dem2.now[1]++;
				dem2.x+=mazepixel;
				dem2.lastcount=0;
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
			dem3.lastcount=0;
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
				dem3.lastcount=1;
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
				dem3.lastcount=1;
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
				dem3.lastcount=0;
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
			dem3.lastcount=1;
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
				dem3.lastcount=0;
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
				dem3.lastcount=0;
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
				dem3.lastcount=1; 
			//}
		}
    }
	
	else if(dem3.direction==2){
		if(dem3.target[1]<dem3.now[1] && NoWall(dem3.now,1)){
			dem3.direction=1;
			dem3.now[1]--;
			dem3.x-=mazepixel;
			dem3.lastcount=1;	
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
				dem3.lastcount=0;
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
				dem3.lastcount=1;
            }
			else if(NoWall(dem3.now,1)){
				dem3.direction=1;
				dem3.now[1]--;
				dem3.x-=mazepixel;
				dem3.lastcount=1;
			}
			else if(NoWall(dem3.now,0)){
				dem3.direction=0;
				dem3.now[1]++;
				dem3.x+=mazepixel;
				dem3.lastcount=0;
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
				dem3.lastcount=0;
			}
			else if(dem3.target[1]<dem3.now[1] && NoWall(dem3.now,1)){
                dem3.direction=1;
				dem3.now[1]--;
                dem3.x-=mazepixel;
				dem3.lastcount=1;
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
			dem3.lastcount=0;
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
				dem3.lastcount=0;
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
				dem3.lastcount=1;
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
				dem3.lastcount=1;
			}
			else if(NoWall(dem3.now,0)){
				dem3.direction=0;
				dem3.now[1]++;
				dem3.x+=mazepixel;
				dem3.lastcount=0;
			}
        }
		else if(NoWall(dem3.now,3)){
			if(dem3.target[1]>dem3.now[1] && NoWall(dem3.now,0)){
				dem3.direction=0;
				dem3.now[1]++;
				dem3.x+=mazepixel;
				dem3.lastcount=0;
			}
			else if(dem3.target[1]<dem3.now[1] && NoWall(dem3.now,1)){
                dem3.direction=1;
				dem3.now[1]--;
                dem3.x-=mazepixel;
				dem3.lastcount=1;
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
			basil.lastcount=0;
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
				basil.lastcount=1;
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
				basil.lastcount=1;
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
				basil.lastcount=0;
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
			basil.lastcount=1;
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
				basil.lastcount=0;
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
				basil.lastcount=0;
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
				basil.lastcount=1;
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
				basil.lastcount=0;
			}
            else if(basil.target[1]<basil.now[1] && NoWall(basil.now,1)){
                basil.direction=1;
				basil.now[1]--;
                basil.x-=mazepixel;
				basil.lastcount=1;
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
				basil.lastcount=1;
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
				basil.lastcount=0;
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
				basil.lastcount=0;
			}
            else if(basil.target[1]<basil.now[1] && NoWall(basil.now,1)){
                basil.direction=1;
				basil.now[1]--;
                basil.x-=mazepixel;
				basil.lastcount=1;
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
				basil.lastcount=1;
			}
			else if(NoWall(basil.now,0)){
				basil.direction=0;
				basil.now[1]++;
				basil.x+=mazepixel;
				basil.lastcount=0;
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

void targetchange(){
	if(!powerup && !dem1.dead){
		dem1.target[0]=harryNow[0];
		dem1.target[1]=harryNow[1];
	}
	if(!powerup && !dem2.dead){
		dem2.target[0]=harryNow[0];
		dem2.target[1]=harryNow[1];
	}
	if(!powerup && !dem3.dead){
		dem3.target[0]=harryNow[0];
		dem3.target[1]=harryNow[1];
	}
	if(!powerup && !basil.dead){
		basil.target[0]=harryNow[0];
		basil.target[1]=harryNow[1];
	}
	if(powerup && !dem1.dead){
		dem1.target[0]=1;
		dem1.target[1]=8;
	}
	if(powerup && !dem2.dead){
		dem2.target[0]=2;
		dem2.target[1]=17;
	}
	if(powerup && !dem3.dead){
		dem3.target[0]=4;
		dem3.target[1]=1;
	}
	if(powerup && !basil.dead){
		basil.target[0]=16;
		basil.target[1]=14;
	}
	if(dem1.dead){
		dem1.target[0]=dem1initY;
		dem1.target[1]=dem1initX;
	}
	if(dem2.dead){
		dem2.target[0]=dem2initY;
		dem2.target[1]=dem2initX;
	}
	if(dem3.dead){
		dem3.target[0]=dem3initY;
		dem3.target[1]=dem3initX;
	}
	if(basil.dead){
		basil.target[0]=basilinitY;
		basil.target[1]=basilinitX;
	}
}

void movedementor(){
	if(!dem1.dead){
		if(!powerup){
			if(dem1.lastcount==0)
				iShowBMP2(dem1.x, dem1.y, dementorright[0], 255);
			else if(dem1.lastcount==1)
				iShowBMP2(dem1.x, dem1.y, dementorleft[0], 255);
		}
		else{
			iShowBMP2(dem1.x, dem1.y, dementordown[0], 16777215);
		}
	}
	else if(dem1.dead){
		iShowBMP2(dem1.x, dem1.y, deaddementor[0], 0);
	}
	if(!dem2.dead){
		if(!powerup){
			if(dem2.lastcount==0)
				iShowBMP2(dem2.x, dem2.y, dementorright[0], 255);
			else if(dem2.lastcount==1)
				iShowBMP2(dem2.x, dem2.y, dementorleft[0], 255);
		}
		else
			iShowBMP2(dem2.x, dem2.y, dementordown[0], 16777215);
	}
	else if(dem2.dead){
		iShowBMP2(dem2.x, dem2.y, deaddementor[0], 0);
	}
	if(!dem3.dead){
		if(!powerup){
			if(dem3.lastcount==0)
				iShowBMP2(dem3.x, dem3.y, dementorright[0], 255);
			else if(dem3.lastcount==1)
				iShowBMP2(dem3.x, dem3.y, dementorleft[0], 255);
		}
		else
			iShowBMP2(dem3.x, dem3.y, dementordown[0], 16777215);
	}
	else if(dem3.dead){
		iShowBMP2(dem3.x, dem3.y, deaddementor[0], 0);
	}
	if(basil.lastcount==0)
		iShowBMP2(basil.x, basil.y, basiliskright[0], 0);
	else if(basil.lastcount==1)
		iShowBMP2(basil.x, basil.y, basiliskleft[0], 0);
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
			if(!powerup){
				powerup=true;
				timerID = iSetTimer(1000, timerFunction);
			}
		}
		if(maze[mazeLevel][harryNow[0]][harryNow[1]]==5){
			gamewin=true;
			playgame=false;
			if(totalsound){
				if(musicOn){
					musicOn=false;
					PlaySound(0,0,0);
					gamewinsound=true;
					if(gamewinsound){
					PlaySound(TEXT("assets\\sound\\aveda.WAV"), NULL,SND_ASYNC );
					}
				}
			}
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
			if(!powerup){
				powerup=true;
				timerID = iSetTimer(1000, timerFunction);
			}
		}
		if(maze[mazeLevel][harryNow[0]][harryNow[1]]==5){
			gamewin=true;
			playgame=false;
			if(totalsound){
				if(musicOn){
					musicOn=false;
					PlaySound(0,0,0);
					gamewinsound=true;
					if(gamewinsound){
					PlaySound(TEXT("assets\\sound\\aveda.WAV"), NULL,SND_ASYNC );
					}
				}
			}
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
			if(!powerup){
				powerup=true;
				timerID = iSetTimer(1000, timerFunction);
			}
		}
		if(maze[mazeLevel][harryNow[0]][harryNow[1]]==5){
			gamewin=true;
			playgame=false;
			if(totalsound){
				if(musicOn){
					musicOn=false;
					PlaySound(0,0,0);
					gamewinsound=true;
					if(gamewinsound){
					PlaySound(TEXT("assets\\sound\\aveda.WAV"), NULL,SND_ASYNC );
					}
				}
			}
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
			if(!powerup){
				powerup=true;
				timerID = iSetTimer(1000, timerFunction);
			}
		}
		if(maze[mazeLevel][harryNow[0]][harryNow[1]]==5){
			gamewin=true;
			playgame=false;
			if(totalsound){
				if(musicOn){
					musicOn=false;
					PlaySound(0,0,0);
					gamewinsound=true;
					if(gamewinsound){
					PlaySound(TEXT("assets\\sound\\aveda.WAV"), NULL,SND_ASYNC );
					}
				}
			}
		}
		harry.downInd++;
        if(harry.downInd>1) harry.downInd=0;
        harry.downCount=false;
	}
}

void  Harrydeadcheck(){
	if(harryNow[0]==dem1.now[0] && harryNow[1]==dem1.now[1] && harrydead==false && powerup==false && dem1.dead==false){
		harrydead=true;
	}
	else if(harryNow[0]==dem2.now[0] && harryNow[1]==dem2.now[1] && harrydead==false && powerup==false && dem2.dead==false){
		harrydead=true;
	}
	else if(harryNow[0]==dem3.now[0] && harryNow[1]==dem3.now[1] && harrydead==false && powerup==false && dem3.dead==false){
		harrydead=true;
	}
	else if(harryNow[0]==basil.now[0] && harryNow[1]==basil.now[1] && harrydead==false ){
		harrydead=true;
	}
	if(harryNow[0]==dem1.now[0] && harryNow[1]==dem1.now[1] && harrydead==false && powerup==true && dem1.dead==false){
		// dem1.now[0]=dem1initY;
		// dem1.now[1]=dem1initX;
		// dem1.x = mazeX + dem1.now[1]*mazepixel;
		// dem1.y = mazeY + (20-dem1initY)*mazepixel;
		dem1.dead=true;
		dem1.timerid=iSetTimer(1000,dem1deadtolife);
		iPauseTimer(timerID); 
		timerCount=0;
		powerup=false;
	}
	else if(harryNow[0]==dem2.now[0] && harryNow[1]==dem2.now[1] && harrydead==false && dem2.dead==false){
		// dem2.now[0]=dem2initY;
		// dem2.now[1]=dem1initX;
		// dem2.x = mazeX + dem2.now[1]*mazepixel;
		// dem2.y = mazeY + (20-dem2initY)*mazepixel;
		dem2.dead=true;
		dem2.timerid=iSetTimer(1000,dem2deadtolife);
		// iPauseTimer(timerID); 
		// timerCount=0;
		// powerup=false;
	}
	else if(harryNow[0]==dem3.now[0] && harryNow[1]==dem3.now[1] && harrydead==false && dem3.dead==false){
		// dem3.now[0]=dem3initY;
		// dem3.now[1]=dem1initX;
		// dem3.x = mazeX + dem3.now[1]*mazepixel;
		// dem3.y = mazeY + (20-dem3initY)*mazepixel;
		dem3.dead=true;
		dem3.timerid=iSetTimer(1000,dem3deadtolife);
		iPauseTimer(timerID); 
		timerCount=0;
		powerup=false;
	}
}

void timeID(){
	
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
			appendScoreToFile(str, point);
			//printf("%s\n",str);
			str[0]='\0';
			if(totalsound){
				if(musicOn){
					musicOn=false;
					PlaySound(0,0,0);
					deaddialouge=true;
					if(deaddialouge){
					PlaySound(TEXT("assets\\sound\\youknowwho.WAV"), NULL,SND_ASYNC );
					}
				}
			}
		}
	}
}

void dem1deadtolife (){
    dem1.deadtime++;
    //printf("deadtime Count: %d\n", dem1.deadtime);

    if (dem1.deadtime >= deathtime) {
        iPauseTimer(dem1.timerid); 
		dem1.deadtime=0;
		dem1.dead=false;
    }
}

void dem2deadtolife (){
    dem2.deadtime++;
    //printf("deadtime Count: %d\n", dem2.deadtime);

    if (dem2.deadtime >= deathtime) {
        iPauseTimer(dem2.timerid); 
		dem2.deadtime=0;
		dem2.dead=false;
    }
}

void dem3deadtolife (){
    dem3.deadtime++;
    //printf("deadtime Count: %d\n", dem3.deadtime);

    if (dem3.deadtime >= deathtime) {
        iPauseTimer(dem3.timerid); 
		dem3.deadtime=0;
		dem3.dead=false;
    }
}

void soundMoldy(){
	if(musicOn){
		PlaySound(TEXT("assets\\sound\\gamesound.WAV"), NULL,SND_LOOP | SND_ASYNC );
	}
	if(deaddialouge){
		PlaySound(TEXT("assets\\sound\\youknowwho.WAV"), NULL,SND_ASYNC );
	}
}

void newgame(){
	harryinitial();
	dementorinitial();
	indexnumber=0;
	life=3;
	mazeLevel=0;
	point=0;
	snitchCollected=0;
	timerCount=0;
	for(int eee=0;eee<3;eee++){
		for(int cdi=0;cdi<21;cdi++){
			for(int cse=0;cse<19;cse++){
				maze[eee][cdi][cse]=original[eee][cdi][cse];
			}
		}
	}
}



void appendScoreToFile(const char* name, int score) {
    FILE *fp = fopen("assets//High_Score.txt", "a");
    if (fp) {
        fprintf(fp, "%s: %d\n", name, score);
        fclose(fp);
		//printf("Score appended successfully for %s.\n", name);

    } else {
        //printf("Error: Could not open High_Score.txt for appending.\n");
    }
}

int compareScores(const void *a, const void *b) {
    Entry *entryA = (Entry *)a;
    Entry *entryB = (Entry *)b;
    return entryB->score - entryA->score;
}

void sortScoresInFile() {
    FILE *fp = fopen("assets//High_Score.txt", "r");
    Entry entries[MAX_ENTRIES];
    int count = 0;
    while (fgets(entries[count].name, MAX_LINE_LENGTH, fp) && count < MAX_ENTRIES) {
        char *colon = strchr(entries[count].name, ':');
        if (colon) {
            *colon = '\0';
            entries[count].score = atoi(colon + 1);
            count++;
        }
    }
    fclose(fp);
    qsort(entries, count, sizeof(Entry), compareScores);
    fp = fopen("assets//High_Score.txt", "w");
    for (int i = 0; i < count; i++) {
        fprintf(fp, "%s: %d\n", entries[i].name, entries[i].score);
    }
    fclose(fp);
}

void showHighScore() {
    FILE *fp = fopen("assets//High_Score.txt", "r");
	int yPosition = 570;
    char name[100];
    int score;
    int displayed = 0;
	while (fscanf(fp, " %99[^:]: %d\n", name, &score) == 2 && displayed < MAX_DISPLAYED_SCORES) {
        char displayText[150];
        sprintf(displayText, "%d. %s: %d", displayed + 1, name, score);
        iSetColor(0, 0, 0);
        iText(150, yPosition, displayText, GLUT_BITMAP_TIMES_ROMAN_24);
        yPosition -= 50;
        displayed++;
    }
	fclose(fp);
}

void timerFunction() {
    timerCount++;
    printf("Timer Count: %d\n", timerCount);
	if (timerCount >= poweruptime) {
        iPauseTimer(timerID); 
		timerCount=0;
		powerup=false;
    }
}
void update(){
	movedem1();
	movedem2();
	movedem3();
	movebasil();
	targetchange();
}

int main() {
	harryinitial();
	dementorinitial();
	iSetTimer(dementortime,update);
	if(totalsound)
		soundMoldy();
	// iSetTimer(10, Harrydeadcheck);
	// iSetTimer(10,lifecheck);
	//iSetTimer(harrytime,Harrymove);
	//place your own initialization codes here.
	iInitialize(screenwidth, screenheight, "Dotly Hallows");
	return 0;
}
