#include "EnemyPlane.h"
#include "BlackBoard.h"
#include "UIController.h"
#include <iostream>

using namespace std;

EnemyPlane::EnemyPlane(int left, int top, int r, int c):Box(left,top,r,c)
{
	flag = 3;
	UIController::handle()._boxes[_row][_col]=3;
	UIController::handle()._boxes[_row][_col+1]=3;
	UIController::handle()._boxes[_row][_col+2]=3;
	UIController::handle()._boxes[_row+1][_col+1]=3;
}

EnemyPlane::~EnemyPlane()
{
}

void EnemyPlane::OnDraw(BlackBoard &board)
{
	board.SetColor(0, 0, 1); //»­³öµÐ»ú
	int x1 = _left + _col * BOX_SIZE, x2 = x1 + BOX_SIZE - 1, x3 = x2 + BOX_SIZE - 1, x4 = x3 + BOX_SIZE - 1;
	int y1 = _top -_row * BOX_SIZE, y2 = y1 - BOX_SIZE + 1, y3 = y2 - BOX_SIZE + 1;
	board.DrawLine(x1,y1,x4,y1);
	board.DrawLine(x1,y2,x4,y2);
	board.DrawLine(x2,y3,x3,y3);
	board.DrawLine(x1,y1,x1,y2);
	board.DrawLine(x2,y1,x2,y3);
	board.DrawLine(x3,y1,x3,y3);
	board.DrawLine(x4,y1,x4,y2);
}

bool EnemyPlane::HitBullet_or_Plane()
{
	if (UIController::handle()._boxes[_row][_col]==1||UIController::handle()._boxes[_row][_col]==2)
	{
		return true;
	}
	if (UIController::handle()._boxes[_row][_col+2]==1||UIController::handle()._boxes[_row][_col+2]==2)
	{
		return true;
	}
	if (UIController::handle()._boxes[_row+1][_col+1]==1||UIController::handle()._boxes[_row+1][_col+1]==2)
	{
		return true;
	}
	return false;
}

void EnemyPlane::Move(int dx, int dy)
{
	_row += dx;
	_col += dy;
}

bool EnemyPlane::CanMove(int dx, int dy)
{
	EnemyPlane temp = *this;
	temp.Move(dx,dy);

	if (UIController::handle().HitBottom(temp))
	{
		clear();
		return false;
	}
	if (UIController::handle().HitBulletPlane(temp))
	{
		for(auto p : UIController::handle().figure)
		{
			if(p->Is_in(_row+dx,_col+dy)||p->Is_in(_row+dx,_col+2+dy)||p->Is_in(_row+1+dx,_col+1+dy))
			{
				if (p->getID()==2)
				{
					cout << "enemyplane hit myplane,game over!!" << endl;
					exit(1);
				}
				p->clear();
			}
		}
		clear();
		return false;
	}
	UIController::handle()._boxes[_row][_col]=0;
	UIController::handle()._boxes[_row][_col+1]=0;
	UIController::handle()._boxes[_row][_col+2]=0;
	UIController::handle()._boxes[_row+1][_col+1]=0;

	UIController::handle()._boxes[_row+dx][_col+dy]=3;
	UIController::handle()._boxes[_row+dx][_col+1+dy]=3;
	UIController::handle()._boxes[_row+dx][_col+2+dy]=3;
	UIController::handle()._boxes[_row+1+dx][_col+1+dy]=3;
	return true;
}

bool EnemyPlane::Is_in(int r,int c)
{
	return (r==_row&&c==_col)||(r==_row&&c==_col+2)||(r==_row+1&&c==_col+1);
}

void EnemyPlane::clear()
{
	UIController::handle()._boxes[_row][_col]=0;
	UIController::handle()._boxes[_row][_col+1]=0;
	UIController::handle()._boxes[_row][_col+2]=0;
	UIController::handle()._boxes[_row+1][_col+1]=0;
	_row = 0;
	UIController::handle()._boxes[_row][_col]=3;
	UIController::handle()._boxes[_row][_col+1]=3;
	UIController::handle()._boxes[_row][_col+2]=3;
	UIController::handle()._boxes[_row+1][_col+1]=3;
}