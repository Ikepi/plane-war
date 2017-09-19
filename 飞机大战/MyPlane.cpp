#include "MyPlane.h"
#include "bullet.h"
#include "BlackBoard.h"
#include "UIController.h"
#include <iostream>
using namespace std;

MyPlane::MyPlane(int left, int top, int r, int c):Box(left,top,r,c)
{
	flag = 2;
	UIController::handle()._boxes[_row][_col] = 2;
	UIController::handle()._boxes[_row][_col+1] = 2;
	UIController::handle()._boxes[_row][_col+2] = 2;
	UIController::handle()._boxes[_row][_col+3] = 2;
	UIController::handle()._boxes[_row-1][_col+1] = 2;
	UIController::handle()._boxes[_row-1][_col+2] = 2;
}

MyPlane::~MyPlane()
{
}

void MyPlane::OnDraw(BlackBoard &board)
{
	board.SetColor(0, 1, 0); //»­³öÎÒ»ú
	int x1 = _left + _col * BOX_SIZE, x2 = x1 + BOX_SIZE - 1, x3 = x2 + BOX_SIZE - 1, x4 = x3 + BOX_SIZE - 1, x5 = x4 + BOX_SIZE - 1;
	int y1 = _top -_row * BOX_SIZE, y2 = y1 + BOX_SIZE - 1, y3 = y1 - BOX_SIZE + 1;
	board.DrawLine(x1,y1,x5,y1);
	board.DrawLine(x1,y3,x5,y3);
	board.DrawLine(x2,y2,x4,y2);
	board.DrawLine(x1,y1,x1,y3);
	board.DrawLine(x2,y2,x2,y3);
	board.DrawLine(x3,y2,x3,y3);
	board.DrawLine(x4,y2,x4,y3);
	board.DrawLine(x5,y1,x5,y3);
}

bool MyPlane::HitBullet_or_Plane()
{
	if (UIController::handle()._boxes[_row][_col]==3)
	{
		return true;
	}
	if (UIController::handle()._boxes[_row][_col+1]==3)
	{
		return true;
	}
	if (UIController::handle()._boxes[_row][_col+2]==3)
	{
		return true;
	}
	if (UIController::handle()._boxes[_row][_col+3]==3)
	{
		return true;
	}
	if (UIController::handle()._boxes[_row-1][_col+1]==3)
	{
		return true;
	}
	if (UIController::handle()._boxes[_row-1][_col+2]==3)
	{
		return true;
	}
	return false;
}

void MyPlane::Move(int dx, int dy)
{
	_row += dx;
	_col += dy;
}

bool MyPlane::CanMove(int dx, int dy)
{
	MyPlane temp = *this;
	temp.Move(dx,dy);

	if (UIController::handle().HitLeft(temp))
	{
		return false; 
	}

	if (UIController::handle().HitRight(temp))
	{
		return false; 
	}

	if (UIController::handle().HitBottom(temp))
	{
		return false; 
	}

	if (UIController::handle().HitTop(temp))
	{
		return false;
	}

	if (UIController::handle().HitBulletPlane(temp))
	{
		cout << "myplane hit enemy plane,game over!!" << endl;
		exit(1);
	}
	UIController::handle()._boxes[_row][_col] = 0;
	UIController::handle()._boxes[_row][_col+1] = 0;
	UIController::handle()._boxes[_row][_col+2] = 0;
	UIController::handle()._boxes[_row][_col+3] = 0;
	UIController::handle()._boxes[_row-1][_col+1] = 0;
	UIController::handle()._boxes[_row-1][_col+2] = 0;

	UIController::handle()._boxes[_row+dx][_col+dy] = 2;
	UIController::handle()._boxes[_row+dx][_col+1+dy] = 2;
	UIController::handle()._boxes[_row+dx][_col+2+dy] = 2;
	UIController::handle()._boxes[_row+dx][_col+3+dy] = 2;
	UIController::handle()._boxes[_row-1+dx][_col+1+dy] = 2;
	UIController::handle()._boxes[_row-1+dx][_col+2+dy] = 2;
	return true;
}

bool MyPlane::Is_in(int r,int c)
{
	return (r==_row&&c==_col)||(r==_row&&c==_col+1)||(r==_row&&c==_col+2)||(r==_row&&c==_col+3)||(r==_row-1&&c==_col+1)||(r==_row-1&&c==_col+2);
}

void MyPlane::shoot()
{
	UIController::handle().figure.push_back(new Bullet(_left,_top,_row-1,_col));
	UIController::handle().figure.push_back(new Bullet(_left,_top,_row-1,_col+3));
}

void MyPlane::clear()
{
	flag = 0;
	UIController::handle()._boxes[_row][_col] = 0;
	UIController::handle()._boxes[_row][_col+1] = 0;
	UIController::handle()._boxes[_row][_col+2] = 0;
	UIController::handle()._boxes[_row][_col+3] = 0;
	UIController::handle()._boxes[_row-1][_col+1] = 0;
	UIController::handle()._boxes[_row-1][_col+2] = 0;
}