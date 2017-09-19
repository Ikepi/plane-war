#include "bullet.h"
#include "EnemyPlane.h"
#include "BlackBoard.h"
#include "UIController.h"
#include <iostream>
using namespace std;

Bullet::Bullet(int left, int top, int r, int c):Box(left,top,r,c)
{
	flag = 1;
	UIController::handle()._boxes[_row][_col] = 1;
}

Bullet::~Bullet()
{
}

void Bullet::OnDraw(BlackBoard &board)
{
	board.SetColor(1, 0, 0);
	int x1 = _left + _col * BOX_SIZE, x2 = x1 + BOX_SIZE - 1; 
	int y1 = _top  - _row * BOX_SIZE, y2 = y1 - BOX_SIZE + 1; 

	board.DrawLine(x1, y1, x1, y2); 
	board.DrawLine(x1, y1, x2, y1); 
	board.DrawLine(x1, y2, x2, y2); 
	board.DrawLine(x2, y1, x2, y2); 
}

void Bullet::Move(int dx, int dy)
{
	_row += dx;
	_col += dy;
}

bool Bullet::CanMove(int dx, int dy) 
{
	Bullet temp = *this;
	temp.Move(dx,dy);

	if (UIController::handle().HitTop(temp))//子弹飞出游戏框后消失
	{
		clear();
		return false;
	}

	if (UIController::handle().HitBottom(temp))//子弹飞出游戏框后消失
	{
		clear();
		return false;
	}

	if (UIController::handle().HitBulletPlane(temp))
	{//子弹打到飞机后子弹就消失，飞机也消失
		for(auto p : UIController::handle().figure)//先判断子弹打到的是哪架飞机
		{
			if(p->Is_in(_row+dx,_col+dy))
			{
				if (p->getID()==2)
				{
					cout << "bullet hit myplane,game over!!" << endl;
					exit(1);
				}
				p->clear();
			}
		}
		clear();
		return false;
	}
	UIController::handle()._boxes[_row][_col] = 0;
	UIController::handle()._boxes[_row+dx][_col+dy] = 1;
	return true; 
}

bool Bullet::HitBullet_or_Plane()
{
	return UIController::handle()._boxes[_row][_col]==2||UIController::handle()._boxes[_row][_col]==3;
}

void Bullet::clear()
{
	flag = 0;
	UIController::handle()._boxes[_row][_col] = 0;
}