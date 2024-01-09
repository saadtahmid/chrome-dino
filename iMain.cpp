#include <iostream>
#include "iGraphics.h"
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")
#include <string>
using namespace std;
int windowWidth = 700, windowHeight = 500;
int highestscore = 0, userscore = 0;
bool isInitDisplay = true, isInfoDisplay = false, isGameOver = false, musicOn = true,
	 jumping = false, jumpingUp = false, jumpingDown = false, isducking = false;
int birdy = 200;
float birdx = 555 + 2 * 720;
int BaseHeight = 150;
int groundWidth = 90;
float initialGroundPoint = 90;
float initialDinoPoint = 91;
float dinoBaseHeight = 155;
float speedincrease = .4;
char duck_img[2][50] = {
	"bitmaps\\dino\\duckleft.bmp",
	"bitmaps\\dino\\duckright.bmp",
};
char dino_img[2][50] = {
	"bitmaps\\dino\\left.bmp",
	"bitmaps\\dino\\right.bmp",
};
char bird_img[2][50] = {
	"bitmaps\\pterodactyl\\pdn.bmp",
	"bitmaps\\pterodactyl\\pup.bmp",
};
char cactus_img[8][50] = {
	"bitmaps\\ground\\cactus_0.bmp",
	"bitmaps\\ground\\ground_0.bmp",
	"bitmaps\\ground\\cactus_2.bmp",
	"bitmaps\\ground\\ground_1.bmp",
	"bitmaps\\ground\\cactus_3.bmp",
	"bitmaps\\ground\\ground_0.bmp",
	"bitmaps\\ground\\cactus_1.bmp",
	"bitmaps\\ground\\ground_1.bmp",
};
char ground_img[8][50] = {
	"bitmaps\\ground\\ground_0.bmp",
	"bitmaps\\ground\\ground_1.bmp",
	"bitmaps\\ground\\ground_0.bmp",
	"bitmaps\\ground\\ground_1.bmp",
	"bitmaps\\ground\\ground_0.bmp",
	"bitmaps\\ground\\ground_1.bmp",
	"bitmaps\\ground\\ground_0.bmp",
	"bitmaps\\ground\\ground_1.bmp",
};
int duck_index = 0;
void duck()
{
	if (isducking)
		iShowBMP2(initialDinoPoint, dinoBaseHeight, duck_img[duck_index], 0);
}
int birdIndex = 0;
void plotBird()
{
	iShowBMP2(birdx, birdy, bird_img[birdIndex], 0);
}
int f[8] = {0, 1, 1, 0, 0, 1, 1, 2}, s[8] = {0, 1, 1, 0, 0, 1, 1, 2};
int fcopy[8] = {0, 1, 1, 0, 0, 0, 1, 0};
//swap first lands with second ones
void swapg()
{
	for (int i = 0; i < 8; i++)
	{
		f[i] = s[i];
		if (i != 5)
			s[i] = rand() % 8;
	}
}
void plotLandImg()
{
	for (int i = 0; i < 15; i++)
	{
		if (i % 2 == 0)
		{

			if (i < 8)
				iShowBMP(initialGroundPoint + groundWidth * i, BaseHeight, ground_img[f[i]]);
			else
				iShowBMP(initialGroundPoint + groundWidth * i, BaseHeight, ground_img[s[i - 8]]);
		}
		else
		{
			if (i < 8)
			{
				iShowBMP(initialGroundPoint + groundWidth * i, BaseHeight, cactus_img[f[i]]);
			}
			else
			{
				iShowBMP(initialGroundPoint + groundWidth * i, BaseHeight, cactus_img[s[i - 8]]);
			}
		}
	}
};
int dino_index = 0;
void jumpDino()
{
	if (!jumping)
		return; // Check if it's in Jumping Stage
	else if (!jumpingUp && !jumpingDown)
	{ // Initially in JumpingUp stage
		jumpingUp = true;
		PlaySound(TEXT("musics\\jump.wav"),NULL,SND_ASYNC);
		jumpingDown = false;
	}

	if (jumpingUp)
	{ // For Jumping Up Stage increase Height
		if (dinoBaseHeight < 250)
			dinoBaseHeight += 0.55;
		if (dinoBaseHeight >= 250)
		{
			jumpingUp = false;
			jumpingDown = true;
		}
	}
	else if (jumpingDown)
	{ // For Jumping Down stage decrease Height
		if (dinoBaseHeight > 155)
		{
			dinoBaseHeight -= 0.55;
		}
		if (dinoBaseHeight <= 155)
		{
			dinoBaseHeight = 155;
			jumpingDown = false;
			jumping = false;
		}
	}
};
void plotDinoImg() { iShowBMP2(initialDinoPoint, dinoBaseHeight, dino_img[dino_index], 0); };
void checkcactus()
{
	int cactus[4] = {0, -180, -360, -540};
	for (int i = 1; i <= 7; i += 2)
	{
		for (int j = 0; j <= 6; j += 2)
		{
			if (f[i] == j)
			{
				if (j == 0)
				{
					if (initialGroundPoint >= cactus[(i - 1) / 2] - 10 && initialGroundPoint <= cactus[(i - 1) / 2] + 15 && dinoBaseHeight <= 175)
					{
						isGameOver = true;
					}
				}
				if (j == 2)
				{
					if (initialGroundPoint >= cactus[(i - 1) / 2] - 25 && initialGroundPoint <= cactus[(i - 1) / 2] + 15 && dinoBaseHeight <= 175)
					{
						isGameOver = true;
					}
				}
				if (j == 4)
				{
					if (initialGroundPoint >= cactus[(i - 1) / 2] - 35 && initialGroundPoint <= cactus[(i - 1) / 2] + 15 && dinoBaseHeight <= 175)
					{
						isGameOver = true;
					}
				}
				if (j == 6)
				{
					if (initialGroundPoint >= cactus[(i - 1) / 2] - 51 && initialGroundPoint <= cactus[(i - 1) / 2] + 5 && dinoBaseHeight <= 175)
					{
						isGameOver = true;
					}
				}
			}
		}
	}
}
void checkGameOver()
{
	if (isducking)
	{
		if (birdx >= initialDinoPoint - 5 && birdx <= initialDinoPoint + 35 && birdy + 23 >= dinoBaseHeight && birdy <= dinoBaseHeight + 15)
		{
			isGameOver = true;
		}
		checkcactus();
	}
	else
	{
		if (birdx >= initialDinoPoint - 5 && birdx <= initialDinoPoint + 15 && birdy + 23 >= dinoBaseHeight && birdy <= dinoBaseHeight + 27)
		{
			isGameOver = true;
		}
		checkcactus();
	}
};
void restartGame()
{
	if (userscore > highestscore)
	{
		highestscore = userscore;
	}
	userscore = 0;
	isGameOver = false;
	jumping = false;
	jumpingUp = false;
	jumpingDown = false;
	isducking = false;
	birdy = 200;
	birdx = 555 + 2 * 720;
	initialGroundPoint = 90;
	speedincrease = .4;
	for (int i = 0; i < 8; i++)
	{
		f[i] = fcopy[i];
	}
	dinoBaseHeight = 155;
};
void infoDisplay()
{
	iSetColor(0, 102, 204);
	iFilledRectangle(0, 0, 700, 500);
	iSetColor(255, 0, 0);
	iText(222, 330, "Control: Press SPACE to JUMP", GLUT_BITMAP_HELVETICA_18);
	iText(288, 300, " Press DOWN to DUCK", GLUT_BITMAP_HELVETICA_18);
	iSetColor(255, 255, 0);
	iText(250, 260, "Created By: Saad Tahmid", GLUT_BITMAP_HELVETICA_18);
	iSetColor(0, 0, 0);
	iText(240, 200, "Press any key or click to Exit", GLUT_BITMAP_HELVETICA_18);
};
void gameOver()
{
	iSetColor(0, 0, 0);
	if (userscore > highestscore)
	{
		iText(265, 390, "NEW HIGHSCORE!", GLUT_BITMAP_TIMES_ROMAN_24);
	}
	iSetColor(255, 0, 0);
	iText(290, 300, "GAME OVER!", GLUT_BITMAP_TIMES_ROMAN_24);
	iSetColor(0, 0, 0);
	iText(260, 260, "Press SPACE to Play Again or Q to exit!", GLUT_BITMAP_HELVETICA_12);
	plotLandImg();
	iShowBMP2(birdx, birdy, bird_img[0], 0);
	iShowBMP2(initialDinoPoint, dinoBaseHeight, "bitmaps\\dino\\over.bmp", 0);

	iFilledRectangle(0, 0, 90, windowHeight);
	iSetColor(255, 255, 255);
	iText(10, 460, "SCORE", GLUT_BITMAP_HELVETICA_18);
	string zero = "0000";
	int init = 1;
	for (int i = 1; i <= 4; i++)
	{
		if (userscore >= 10 * init)
			zero.pop_back();
		init *= 10;
	}
	string Score = to_string(userscore);
	Score = zero + Score;
	char ScoreArr[Score.length() + 1];
	strcpy(ScoreArr, Score.c_str());
	iText(40, 430, ScoreArr, GLUT_BITMAP_HELVETICA_12);
	string hScore = to_string(highestscore);
	char hScoreArr[hScore.length() + 1];
	strcpy(hScoreArr, hScore.c_str());
	iText(10, 45, "HIGHSCORE", GLUT_BITMAP_HELVETICA_12);
	iText(35, 24, hScoreArr, GLUT_BITMAP_HELVETICA_12);
	if (userscore > highestscore)
	{
		iSetColor(0, 0, 0);
		iText(340, 350, ScoreArr, GLUT_BITMAP_HELVETICA_18);
	}
};
void initDisplay()
{
	iShowBMP(0, 0, "bitmaps\\others\\home.bmp");
	iShowBMP2(245, 355, "bitmaps\\others\\name.bmp", 0);
	iSetColor(255, 0, 0);
	iShowBMP2(305, 250, "bitmaps\\others\\ply.bmp", 0);
	iSetColor(255, 255, 255);
	iText(330, 290, "PLAY", GLUT_BITMAP_HELVETICA_12);
	iShowBMP2(245, 200, "bitmaps\\others\\click.bmp", 0);
	iSetColor(255, 255, 0);
	string hScore = to_string(highestscore);
	char hScoreArr[hScore.length() + 1];
	strcpy(hScoreArr, hScore.c_str());
	iText(25, 35, "HIGHSCORE: ", GLUT_BITMAP_9_BY_15);
	iText(115, 35, hScoreArr, GLUT_BITMAP_9_BY_15);
	iShowBMP2(630, 40, "bitmaps\\others\\inf.bmp", 0);
	iText(632, 28, "Info", GLUT_BITMAP_8_BY_13);
}

void playGame()
{   
	initialGroundPoint -= speedincrease;
	birdx -= speedincrease; // Speed of the Background Motion.
	if (birdx <= -810)
	{
		birdx = 630;
		birdy = 155 + rand() % 100;
	}
	if (initialGroundPoint <= -630.0)
	{
		initialGroundPoint = 90;
		swapg();
	} // Loop back of Background Screen
	plotLandImg();
	plotBird();
	jumpDino();
	duck();
	if (!isducking)
		plotDinoImg();
	checkGameOver();
	iSetColor(0, 0, 0);
	iFilledRectangle(0, 0, 90, windowHeight);
	iSetColor(255, 255, 255);
	iText(10, 460, "SCORE", GLUT_BITMAP_HELVETICA_18);
	string zero = "0000";
	int init = 1;
	for (int i = 1; i <= 4; i++)
	{
		if (userscore >= 10 * init)
			zero.pop_back();
		init *= 10;
	}
	string Score = to_string(userscore);
	Score = zero + Score;
	char ScoreArr[Score.length() + 1];
	strcpy(ScoreArr, Score.c_str());
	iText(40, 430, ScoreArr, GLUT_BITMAP_HELVETICA_12);
	string hScore = to_string(highestscore);
	char hScoreArr[hScore.length() + 1];
	strcpy(hScoreArr, hScore.c_str());
	iText(10, 45, "HIGHSCORE", GLUT_BITMAP_HELVETICA_12);
	iText(35, 24, hScoreArr, GLUT_BITMAP_HELVETICA_12);
}
/*
	function iDraw() is called again and again by the system.

	*/
void scoreup()
{
	if (!isGameOver && !isInfoDisplay && !isInitDisplay)
	{
		userscore++;
		if (userscore % 150 == 0)
		{
			speedincrease += .035;
		}
	}
}
float cntr = 0;
void iDraw()
{
	// place your drawing codes here
	iClear();
	iSetColor(255, 255, 255);
	iFilledRectangle(0, 0, windowWidth, windowHeight);
	if (isGameOver)
	{
		gameOver();
	}
	else if (isInfoDisplay)
	{
		infoDisplay();
	}
	else if (isInitDisplay)
	{
		initDisplay();
	}
	else
	{
		playGame();
		if (userscore >= cntr + 3.001)
			isducking = 0;
	}
}

/*
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
	*/
void iMouseMove(int mx, int my)
{
	printf("x = %d, y= %d\n", mx, my);
	// place your codes here
}

/*
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
	*/
void iMouse(int button, int state, int mx, int my)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (mx >= 317 && mx <= 370 && my >= 261 && my <= 323 && isInitDisplay)
		{
			isInitDisplay = false;
			musicOn=0;
			PlaySound(0,0,0);
		}
		else if (mx >= 636 && mx <= 660 && my >= 45 && my <= 70 && isInitDisplay)
		{
			isInfoDisplay = true;
		}
		else if (isInfoDisplay)
		{
			isInfoDisplay = false;
		}
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		// place your codes here
	}
}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
	*/
void iKeyboard(unsigned char key)
{   
	if(key=='m'&&(isInfoDisplay||isInitDisplay)){
		if(musicOn){
			musicOn=0;
			PlaySound(0, 0, 0);
		}else{
			musicOn=1;
			PlaySound(TEXT("musics\\music.wav"),NULL,SND_ASYNC);
		}
	}
	if (key == ' ')
	{
		if (isGameOver)
		{
			restartGame();
		}
		else if (isInfoDisplay)
		{
			isInfoDisplay = false;
		}
		else
		{
			if (!isInitDisplay)
				jumping = true;
		};
	}
	else if (isInfoDisplay)
	{
		isInfoDisplay = false;
	}
	else if (key == 'q' || key == 'Q')
	{
		if (isGameOver)
		{
			isGameOver = false;
			isInitDisplay = true;
			restartGame();
		}
	}
	// place your codes for other keys here
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

void iSpecialKeyboard(unsigned char key)
{
	if (key == GLUT_KEY_DOWN)
	{
		if (!jumping && !jumpingUp && !jumpingDown)
		{
			isducking = true;
			cntr = userscore;
		}
	}
	// place your codes for other keys here
}
void changed()
{
	dino_index++;
	if (dino_index > 1)
		dino_index = 0;
	duck_index++;
	if (duck_index > 1)
		duck_index = 0;
	birdIndex++;
	if (birdIndex > 1)
		birdIndex = 0;
}

int main()
{
	// place your own initialization codes here.
	iSetTimer(120, changed);
	iSetTimer(200, scoreup);
	if(musicOn)PlaySound(TEXT("musics\\music.wav"),NULL,SND_ASYNC);
	iInitialize(windowWidth, windowHeight, "Chrome Dino");
	
	return 0;
} 	