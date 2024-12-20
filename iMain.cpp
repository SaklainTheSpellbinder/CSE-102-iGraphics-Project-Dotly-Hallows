#include "iGraphics.h"
#include<time.h>
#include<stdlib.h>
#include<stdbool.h>
#include<Windows.h>
#define screenheight 850
#define screenwidth 800
#define mazepixel 40// all of the sprites...harry demnetors....snitches eveerything is 40*40

void setMazeAra();

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
int harrytime=10;
int harryspeed=5;
int harryNow[2]={19,9};

typedef struct {
    int upInd, downInd, leftInd, rightInd;
    int x;
    int y;
    bool upCount, downCount, leftCount, rightCount;
    bool trigRight, trigLeft, trigUp, trigDown;
    int right, left, up, down;
} move;

move harry;


int maze[2][21][19] =
{
	{
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1,
		1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1,
		1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1,
		0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0,
		1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1,
		1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1,
		1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1,
		0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0,
		1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1,
		1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1,
		1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1,
		1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1,
		1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	},
	{
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1,
		1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1,
		1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1,
		1, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 1,
		1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1,
		1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1,
		1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
		1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1,
		1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1,
		1, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1,
		1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
		1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1,
		1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1,
		1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1,
		1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1,
		1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1,
		1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1,
		1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1,
		1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
	}
};

char BGImg[4][30] = {"assets\\BG2.bmp"};
char mazeWall[2][30]={"assets\\tree.bmp"};
char snitch[2][39]={"assets\\snitch4.bmp","assets\\Sortinghat2.bmp"};
char harrydown[9][100]={"assets\\harry\\tile001.bmp","assets\\harry\\tile002.bmp","assets\\harry\\tile003.bmp","assets\\harry\\tile004.bmp","assets\\harry\\tile005.bmp","assets\\harry\\tile006.bmp","assets\\harry\\tile007.bmp","assets\\harry\\tile008.bmp"};
char harryup[9][100]={"assets\\harry\\tile009.bmp","assets\\harry\\tile010.bmp","assets\\harry\\tile011.bmp","assets\\harry\\tile012.bmp","assets\\harry\\tile013.bmp","assets\\harry\\tile014.bmp","assets\\harry\\tile009.bmp","assets\\harry\\tile010.bmp"};
char harryright[9][100]={"assets\\harry\\tile027.bmp","assets\\harry\\tile028.bmp","assets\\harry\\tile029.bmp","assets\\harry\\tile030.bmp","assets\\harry\\tile031.bmp","assets\\harry\\tile033.bmp","assets\\harry\\tile034.bmp","assets\\harry\\tile035.bmp"};
char harryleft[9][100]={"assets\\harry\\tile018.bmp","assets\\harry\\tile019.bmp","assets\\harry\\tile020.bmp","assets\\harry\\tile021.bmp","assets\\harry\\tile022.bmp","assets\\harry\\tile023.bmp","assets\\harry\\tile024.bmp","assets\\harry\\tile025.bmp"};
int x=500, y = 300, r = 20;
/*
	function iDraw() is called again and again by the system.

	*/

void iDraw() {
	//place your drawing codes here
	iClear();
	iShowBMP(0,0,BGImg[0]);
	for (int i = 0; i <= brickNum; i++)
		{
			iShowBMP(mazeX + mazeXcor[i], mazeY + mazeYcor[i], mazeWall[0]);
		}
	iSetColor(255,255,255);
	for (int i = 0; i <= snitchesNum; i++)
		{
			if (snitchXcor[i][1] != -1)
			{
				if ((i == 41 || i == 55 || i == 179 || i == 184) && mazeLevel == 0)
				{
					iShowBMP2(mazeX + snitchXcor[i][0], mazeY + snitchYcor[i],snitch[1],0 );
				}
				else if ((i == 41 || i == 55 || i == 165 || i == 156) && mazeLevel == 1)
				{
					iShowBMP2(mazeX + snitchXcor[i][0], mazeY + snitchYcor[i],snitch[1],0 );
				}
				else
					iShowBMP2(mazeX + snitchXcor[i][0], mazeY + snitchYcor[i],snitch[0],0 );
			}
		}
	if (harry.rightCount)
				iShowBMP2(harry.x, harry.y, harryright[harry.rightInd], 9283431);
			else if (harry.leftCount)
				iShowBMP2(harry.x, harry.y, harryleft[harry.leftInd], 9283431);
			else if (harry.upCount)
				iShowBMP2(harry.x, harry.y, harryup[harry.upInd], 9283431);
			else if (harry.downCount)
				iShowBMP2(harry.x, harry.y, harrydown[harry.downInd], 9283431);
			else
				iShowBMP2(harry.x, harry.y, harryright[harry.rightInd], 9283431);
		
    // iLine(x,y,r+3,r+5);
    // iEllipse(30,56,32,13);
    // iFilledEllipse(23,4,2,23);
	// iSetColor(20, 200, 200);
	// iFilledCircle(x, y, r);
	// iFilledRectangle(10, 30, 20, 20);
	// iSetColor(20, 200, 0);
	// iText(40, 40, "Hi, I am Saklain");
}
void setMazeAra() {
	int c=0, p, t = 0, z;
	brickNum = 0;
	//foodNum = 0;
    for (int i = 0; i <= 20; i++) {
        for (int j = 0; j < 19; j++) {
            if (maze[mazeLevel][i][j]==1) {
                brickNum = c++;
                mazeXcor[brickNum] = mazepixel * j;
                mazeYcor[brickNum] = mazepixel * i;
			}
			else
				{
					snitchesNum = t++;
					snitchXcor[snitchesNum][0] = mazepixel*j;
					snitchYcor[snitchesNum] = mazepixel*i;
					snitchXcor[snitchesNum][1] = 0;
				}
			}
	}
		
		for (int i = 0; i < 201; i++)
		{
			hocrux[i] = 0;
		}
	cellX = 9;
	cellY = 19;
	harry.x = mazeX + cellX*mazepixel;
	harry.y = mazeY + (20-cellY)*mazepixel;
	harry.downCount=false;
	harry.rightCount=false;
	harry.upCount=false;
	harry.leftCount=false;
        
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
		if (!(harry.x % mazepixel) && !(harry.y % mazepixel))
			{
				harry.downCount = false;
				harry.upCount = false;
				harry.leftCount = false;
				harry.rightCount = true;
			}
			else
			{
				harry.trigRight = true;
				harry.trigLeft = false;
				harry.trigDown = false;
				harry.trigUp = false;
			}
	}
	if(key==GLUT_KEY_LEFT){
		if (!(harry.x % mazepixel) && !(harry.y % mazepixel))
			{
				harry.downCount = false;
				harry.rightCount = false;
				harry.upCount = false;
				harry.leftCount = true;
			}
			else
			{
				harry.trigRight = false;
				harry.trigLeft = true;
				harry.trigDown = false;
				harry.trigUp = false;
			}
	}

	if(key==GLUT_KEY_UP){
		if (!(harry.y % mazepixel) && !(harry.x % mazepixel))
			{
				harry.downCount = false;
				harry.rightCount = false;
				harry.leftCount = false;
				harry.upCount = true;
			}
			else
			{
				harry.trigRight = false;
				harry.trigLeft = false;
				harry.trigDown = false;
				harry.trigUp = true;
			}
	}

	if(key==GLUT_KEY_DOWN){
		if (!(harry.y % mazepixel) && !(harry.x % mazepixel))
			{
				harry.rightCount = false;
				harry.leftCount = false;
				harry.upCount = false;
				harry.downCount = true;
			}
			else
			{
				harry.trigRight = false;
				harry.trigLeft = false;
				harry.trigDown = true;
				harry.trigUp = false;
			}
	}
	else
		{
			harry.rightCount=false;
			harry.leftCount=false;
			harry.downCount=false;
			harry.upCount=false;
		}

	if (key == GLUT_KEY_END) {
		exit(0);
	}
	//place your codes for other keys here
}

void harrymove()
{
	if (harry.rightCount)
	{
		harry.right++;
		if (!maze[mazeLevel][cellY][cellX + 1])
		{
			harry.x += harryspeed;
			if (!(harry.right % 2))
				harry.rightInd++;

			if (!(harry.x % mazepixel))
				cellX++;

		}
		if (harry.rightInd > 7) harry.rightInd = 0;

	}
	else if (harry.leftCount)
	{
		harry.left++;
		if (!maze[mazeLevel][cellY][cellX - 1])
		{
			harry.x -= harryspeed;
			if (!(harry.left % 2))
				harry.leftInd++;

			if (!(harry.x % mazepixel))
				cellX--;

		}

		if (harry.leftInd > 1) harry.leftInd = 0;
	}
	else if (harry.upCount)
	{
		harry.up++;
		if (!maze[mazeLevel][cellY - 1][cellX])
		{
			harry.y += harryspeed;
			if (!(harry.up % 2))
				harry.upInd++;

			if (!(harry.y % mazepixel))
				cellY--;
		}
		if (harry.upInd > 5) harry.upInd = 0;
	}
	else if (harry.downCount)
	{
		harry.down++;
		if (!maze[mazeLevel][cellY + 1][cellX])
		{
			harry.y -= harryspeed;
			if (!(harry.down % 2))
				harry.downInd++;

			if (!(harry.y % mazepixel))
				cellY++;
		}
		if (harry.downInd > 5) harry.downInd = 0;
	}
}

// void Harrymove(){
// 	if(harry.rightCount){
// 		//harry.x+=harryspeed;
// 		harry.rightInd++;
// 	}
// 	else if(harry.leftCount){
// 		//harry.x-=harryspeed;
// 		harry.leftInd++;
// 	}
// 	else if(harry.upCount){
// 		//harry.y+=harryspeed;
// 		harry.upInd++;
// 	}
// 	else if(harry.downCount){
// 		//harry.y-=harryspeed;
// 		harry.downInd++;
// 	}
// 	else{
// 		//harry.rightCount=true;
// 		harry.rightInd=0;
// 	}
// }

void checkTrigger(){
	if (harry.trigRight && !(harry.x % mazepixel) && !(harry.y % mazepixel) && !maze[mazeLevel][cellY][cellX + 1])
	{
		harry.downCount = false;
		harry.upCount = false;
		harry.leftCount = false;
		harry.rightCount = true;
		harry.trigRight = false;
	}
	else if (harry.trigLeft && !(harry.x % mazepixel) && !(harry.y % mazepixel) && !maze[mazeLevel][cellY][cellX - 1])
	{
		harry.downCount = false;
		harry.rightCount = false;
		harry.upCount = false;
		harry.leftCount = true;
		harry.trigLeft = false;
	}
	else if (harry.trigUp && !(harry.x % mazepixel) && !(harry.y % mazepixel) && !maze[mazeLevel][cellY - 1][cellX])
	{
		harry.downCount = false;
		harry.rightCount = false;
		harry.leftCount = false;
		harry.upCount = true;
		harry.trigUp = false;
	}
	else if (harry.trigDown && !(harry.x % mazepixel) && !(harry.y % mazepixel) && !maze[mazeLevel][cellY + 1][cellX])
	{
		harry.rightCount = false;
		harry.leftCount = false;
		harry.upCount = false;
		harry.downCount = true;
		harry.trigDown = false;
	}

}

int main() {
	setMazeAra();
	iSetTimer(10, checkTrigger);
	iSetTimer(harrytime,harrymove);
	//place your own initialization codes here.
	iInitialize(screenwidth, screenheight, "Dotly Hallows");
	return 0;
}
