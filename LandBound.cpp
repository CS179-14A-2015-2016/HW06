// LandBound.cpp : Gunbound game using c++ and openGL *omega sigh*.

#include "stdafx.h"

#include <string>
#include <windows.h>
#include <iostream>
#include <conio.h>
#include <sstream>
#include <math.h>
#include <random>
#include <gl\GL.h>
#include <gl\GLU.h>
#include "GL/freeglut.h"
#pragma comment(lib, "OpenGL32.lib") //specify linker options

using namespace std;

random_device ran;
mt19937 dev(ran());
mt19937 gen(ran());

//key define
#define VK_W 0x57
#define VK_S 0x53
#define VK_A 0x41
#define VK_D 0x44
#define VK_F 0x46
#define VK_L 0x4C
#define VK_SPACE 0x20

//window size and refresh rate
int width = 1000;
int height = 500;
int refresh = 1000 / 60;

//land specs
float land_width = 100;
float land_height = 50;

//tank specs
float tank_width = 20;
float tank_height = 10;

//tank position
float tank1_posx = land_width / 2;
float tank1_posy = land_height;
float tank2_posx = width - (land_width / 2) - 8 - tank_width;
float tank2_posy = land_height;

//powergauge
float p1gauge_posx = tank1_posx;
float p2gauge_posx = tank2_posx;

float gauge_posy = land_height * 3;

float gauge1_height = 1;
float gauge2_height = 1;

float gauge_width = 10;
float gauge_maxheight = gauge_posy + 30;
float gauge_fill = 2;

//scoring
int p1life = 5;
int p2life = 5;

//bullet
float velocityX1;
float velocityY1;
float velocityX2;
float velocityY2;
float theta1;
float theta2;
float bulletX1 = 0.0;
float bulletY1 = 0.0;
float bulletX2 = 0.0;
float bulletY2 = 0.0;
float bulletSize = 5; //radius
int bullet_segments = 8;
float windVelocity = 0;
float storewind1 = 0;
float storewind2 = 0;
float ts = 0;

//bools
bool player2 = false;
bool gameStart = false;
bool p1fire = false;
bool p2fire = false;

static float rotAngle1 = 0.0;
static float rotAngle2 = 360.0;

/*
//ball shenanigans
//ball1
float bulletX = width / 2 + 10;
float bulletY = height / 2;
float ball_dirx = -1.0;
float ball_diry = 1.0;

//ball2
float ball2_posx = width / 2 - 10;
float ball2_posy = height / 2;
float ball2_dirx = 1.0;
float ball2_diry = -1.0;

float ball_speedx1 = 4;
float ball_speedy1 = 0;
float ball_speedx2 = -4;
float ball_speedy2 = 0;
float ball_radius = 5;
int ball_segments = 8;
*/

//function functions

int steprand()
{
	int wind = 5;
	uniform_int_distribution<> dis(-wind, wind);
	int a = dis(dev);
	return a;
}

//int to string function
string inttostr(int x) {
	//converts an int to a string using sstream lib
	stringstream convs;
	convs << x;
	return convs.str();
}

/*
//clamp function
float clamp(float n, float lower, float upper) {
n = (n > lower) * n + !(n > lower) * lower;
return (n < upper) * n + !(n < upper) * upper;
}
*/

//void functions

//keyboard controls
void keyboard() {
	//gauge power
	if (GetAsyncKeyState(VK_W))
	{
		if (gauge1_height <= gauge_maxheight)
		{
			gauge1_height += gauge_fill;
		}
	}

	if (GetAsyncKeyState(VK_S))
	{
		if (gauge1_height > 1)
		{
			gauge1_height -= gauge_fill;
		}
	}


	if (GetAsyncKeyState(VK_UP))
	{
		if (gauge2_height <= gauge_maxheight)
		{
			gauge2_height += gauge_fill;
		}
	}

		if (GetAsyncKeyState(VK_DOWN))
	{
		if (gauge2_height >= 1)
		{
			gauge2_height -= gauge_fill;
		}
	}

	if (GetAsyncKeyState(VK_A))
	{
		if (rotAngle1 <= 180.0)
		{
			rotAngle1 += 1.0;
		}
	}

	if (GetAsyncKeyState(VK_D))
	{
		if (rotAngle1 >= 2)
		{
			rotAngle1 -= 1.0;
		}
	}

	if (GetAsyncKeyState(VK_RIGHT))
	{
		if (rotAngle2 >= 180.0)
		{
			rotAngle2 -= 1.0;
		}
	}

	if (GetAsyncKeyState(VK_LEFT))
	{
		if (rotAngle2 <= 360.0)
		{
			rotAngle2 += 1.0;
		}
	}

	if (GetAsyncKeyState(VK_F))
	{
		bulletX2 = 0;
		bulletY2 = 0;
		velocityX2 = 0;
		velocityY2 = 0;
		storewind2 = 0;
		storewind1 = windVelocity;
		bulletX1 = tank1_posx + (tank_width / 2);
		bulletY1 = tank1_posy + (tank_width / 2);
		velocityX1 = gauge1_height / 5;
		velocityY1 = gauge1_height / 5;
		theta1 = (3.1415926 / 180) * rotAngle1;

	}

	if (GetAsyncKeyState(VK_L))
	{
		bulletX1 = 0;
		bulletY1 = 0;
		velocityX1 = 0;
		velocityY1 = 0;
		storewind1 = 0;
		storewind2 = windVelocity;
		bulletX2 = tank2_posx + (tank_width / 2);
		bulletY2 = tank2_posy + (tank_width / 2);
		velocityX2 = gauge2_height / 5;
		velocityY2 = gauge2_height / 5;
		theta2 = (3.1415926 / 180) * (rotAngle2 - 180);

	}
	
	if (GetAsyncKeyState(VK_SPACE))
	{
		gameStart = true;
	}
}

//makes gl recognized 2d usage
void use2D(int width, int height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0f, width, 0.0f, height, 0.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

//prints text on screen
void textDraw(float x, float y, string text) {
	glRasterPos2f(x, y);
	glutBitmapString(GLUT_BITMAP_8_BY_13, (const unsigned char*)text.c_str());
}

//draw paddles
void boxDraw(float x, float y, float width, float height) {
	glBegin(GL_QUADS);
	glVertex2f(x, y);
	glVertex2f(x + width, y);
	glVertex2f(x + width, y + height);
	glVertex2f(x, y + height);
	glEnd();
}

//line draw
void lineDraw(float x1, float y1, float x2, float y2) {
	glPushMatrix();
	glTranslatef(x1, y1, 0.0f);
	glRotatef(rotAngle1, 0.0f, 0.0f, 1.0f);
	glTranslatef(-x1, -y1, 0.0f);
	glBegin(GL_LINES);
	glVertex3f(x1, y1, 0.0f);
	glVertex3f(x2, y2, 0.0f);
	glEnd();
	glPopMatrix();
}

void line2Draw(float x1, float y1, float x2, float y2) {
	glPushMatrix();
	glTranslatef(x1, y1, 0.0f);
	glRotatef(rotAngle2, 0.0f, 0.0f, 1.0f);
	glTranslatef(-x1, -y1, 0.0f);
	glBegin(GL_LINES);
	glVertex3f(x1, y1, 0.0f);
	glVertex3f(x2, y2, 0.0f);
	glEnd();
	glPopMatrix();
}

//draw the ball
void ballDraw(float cx, float cy, float r, int segments) {
	float theta = 2 * 3.1415926 / float(segments);
	//sin and cos calculation
	float cos = cosf(theta);
	float sin = sinf(theta);
	float t;

	float varx = r; //start at angle 0
	float vary = 0;

	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < segments; i++) {
		glVertex2f(varx + cx, vary + cy); //outputs vertex

										  //apply rotation matrix
		t = varx;
		varx = cos * varx - sin * vary;
		vary = sin * t + cos * vary;
	}
	glEnd();
}

void boom()
{
	if (player2 == false)
	{
		bulletX1 = tank1_posx + (tank_width / 2);
		bulletY1 = tank1_posy + (tank_height / 2);
		windVelocity = steprand();
		player2 = true;
		ts = 0;
	}
	else if (player2 == true)
	{
		bulletX2 = tank2_posx + (tank_width / 2);
		bulletY2 = tank2_posy + (tank_height / 2);
		windVelocity = steprand();
		player2 = false;
		ts = 0;
	}
}

void collisionChecker() {
	//left wall collision
	if ((bulletX1 < 0) || (bulletX2 < 0)) {
		boom();
	}

	//right wall collision
	if ((bulletX1 > width) || (bulletX2 > width)) {
		boom();
	}

	//top /bot wall collision
	if ((bulletY1 > height - 20 || bulletY1 < 10) || (bulletY2 > height - 20 || bulletY2 < 10))
	{
		boom();
	}

	//tank collision
	if ((bulletX2 >= tank1_posx) &&
		(bulletX2 <= tank1_posx + tank_width) &&
		(bulletY2 <= tank1_posy + tank_height) &&
		(bulletY2 >= tank1_posy))
	{
		if (player2 == true)
		{
			p1life -= 1;
		}
		boom();
	}
	if ((bulletX1 >= tank2_posx) &&
		(bulletX1 <= tank2_posx + tank_width) &&
		(bulletY1 <= tank2_posy + tank_height) &&
		(bulletY1 >= tank2_posy))
	{
		if (player2 == false)
		{
			p2life -= 1;
		}
		boom();
	}
}

void bulletMove()
{
	if (gameStart == true)
	{
		if (player2 == false)
		{
			bulletX1 += velocityX1*cos(theta1)*ts + storewind2;
			bulletY1 += velocityY1*sin(theta1)*ts - ((ts*ts*9.8)/2);
			collisionChecker();
		}

		else if (player2 == true)
		{
			bulletX2 += velocityX2*cos(theta2)*ts + storewind2;
			bulletY2 += velocityY2*sin(theta2)*ts - ((ts*ts*9.8)/2);
			collisionChecker();
		}		

		/*
		
		if (player2 == false)
		{
			bulletX += ((velocityOriginal + windVelocity)*ts)*cos(rotAngle1);
			bulletY += (velocityOriginal*ts)*sin(rotAngle1) - ((9.8*(ts*ts)) / 2);
		}
		
		else if (player2 == true)
		{
			bulletX -= ((velocityOriginal + windVelocity)*ts)*cos(launchAngle);
			bulletY += (velocityOriginal*ts)*sin(launchAngle) - ((9.8*(ts*ts)) / 2);
		}
		*/

	}


}



//draw on screen
void draw() {
	//clearing the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	//put draw codes below

	//ball display
	ballDraw(bulletX1, bulletY1, bulletSize, bullet_segments);
	ballDraw(bulletX2, bulletY2, bulletSize, bullet_segments);

	//ballDraw(ball2_posx, ball2_posy, ball_radius, ball_segments);

	//land display
	boxDraw(0, 0, land_width, land_height);
	boxDraw(width - land_width - 8, 0, land_width, land_height);

	//tank draw
	boxDraw(tank1_posx, tank1_posy, tank_width, tank_height);
	boxDraw(tank2_posx, tank2_posy, tank_width, tank_height);

	//gauge draw
	boxDraw(p1gauge_posx, gauge_posy, gauge_width, gauge1_height);
	boxDraw(p2gauge_posx, gauge_posy, gauge_width, gauge2_height);

	//line
	lineDraw((tank1_posx + (tank_width/2)), (tank1_posy + (tank_height/2)), (tank1_posx + 50), (tank1_posy + (tank_height / 2)));
	line2Draw((tank2_posx + (tank_width/2)), (tank2_posy + (tank_height / 2)), (tank2_posx - 30), (tank2_posy + (tank_height / 2)));


	//score display
	textDraw(width / 2 - 30, height - 30, inttostr(rotAngle1) + " " + inttostr(p1life) + " : " + inttostr(p2life) + " " + inttostr(abs(rotAngle2 - 360)));
	textDraw(width / 2, height - 50, inttostr(windVelocity));
	//swapping buffers
	glutSwapBuffers();
}

//screen update handler
void update(int upvalue) {
	//input
	keyboard();

	bulletMove();
	ts += 1/600;

	//calls update in millisecs
	glutTimerFunc(refresh, update, 0);

	//Redisplay Frame
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	//initiliaze opengl using glut
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutCreateWindow("Le GunBound");

	//uses the void functions
	glutDisplayFunc(draw);
	glutTimerFunc(refresh, update, 0);

	//setup the 2d and set draw color to black
	use2D(width, height);
	glColor3f(1.0f, 1.0f, 1.0f);

	//program loop
	glutMainLoop();

	return 0;
}

//wake me up
//wake me up inside
//cant wake up
//wake me up inside
//save meeee
