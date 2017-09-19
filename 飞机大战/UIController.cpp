#include "stdafx.h"

#include <iostream>

#include "UIController.h"
#include "BlackBoard.h"
#include "Box.h"
#include "bullet.h"
#include "MyPlane.h"
#include "EnemyPlane.h"

using namespace std;
extern BlackBoard board; //声明一个全局变量


UIController::UIController() : _left(-(COLS * Box::BOX_SIZE / 2)), _bottom(-ROWS * Box::BOX_SIZE / 2), _right(COLS * Box::BOX_SIZE / 2), _top(ROWS * Box::BOX_SIZE / 2)
{	
	bigplane = new MyPlane(_left,_top,ROWS-1,6);
	figure.push_back(bigplane);
	figure.push_back(new EnemyPlane(_left,_top,0,0));
	figure.push_back(new EnemyPlane(_left,_top,0,4));
	figure.push_back(new EnemyPlane(_left,_top,0,8));
	figure.push_back(new EnemyPlane(_left,_top,0,12));
}

UIController::~UIController()//析构函数
{
	for(auto p : figure)
	{
		delete p;
		p = NULL;
	}
}

void UIController::OnDraw(BlackBoard &board) 
{
	for (int i = 0; i < COLS; i++)
	{
		if (_boxes[ROWS-1][i]==3)
		{
			cout << "you let one enemyplane run away,game over!!" << endl;
			exit(1);
		}
	}
	//画出游戏的框框，可以灵活设置
	board.SetColor(1, 0, 1); 
	board.DrawLine(_left,  _top,   _left,  _bottom);
	board.DrawLine(_left,  _top,   _right, _top);
	board.DrawLine(_left,  _bottom,_right, _bottom);
	board.DrawLine(_right, _top,   _right, _bottom);

	//画出我机
	bigplane->OnDraw(board);

	//画出子弹、敌机
	for(auto p : figure)
		if (p->getID()!=0&&p->getID()!=2)
		{
			p->OnDraw(board);
		}
}

void UIController::PlaneOnTimer(int code)
{
	for(auto p : figure)
	{
		if(p->getID()==3)
		{
			if(p->CanMove(1,0))
				p->Move(1,0);
		}
	}
	board.Update();
}

void UIController::BulletOnTimer(int code)
{
	for(auto p : figure)
	{
		if(p->getID()==1)
		{
			if(p->CanMove(-1,0))
				p->Move(-1,0);
		}
	}
	board.Update();
}

void UIController::OnKey(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'q':
		std::cout<<"see you"<<std::endl;
		exit(0);//按q退出
		break;
	case 's':
		MoveBoxDown(); //向下移动飞机
		break;
	case 'a':
		MoveBoxLeft(); //向左移动飞机
		break;
	case 'd':
		MoveBoxRight(); //向右移动飞机
		break;
	case 'w':
		MoveBoxUp();//向上移动飞机
		break;
	case ' ':
		shoot_Bullet();//发射子弹
		break;
	}
}

bool UIController::HitLeft(Box &box)
{
	return box.LeftTo(_left); 
}

bool UIController::HitRight(Box &box)
{
	return box.RightTo(_right); 
}

bool UIController::HitBottom(Box &box)
{
	return box.LowerTo(_bottom); 
}

bool UIController::HitTop(Box &box)
{
	return box.Higherto(_top);
}

bool UIController::HitBulletPlane(Box &box)
{
	return box.HitBullet_or_Plane();
}

void UIController::MoveBoxLeft()
{
	if (bigplane->CanMove(0, -1))
	{
		bigplane->Move(0, -1); 
		board.Update(); 
	}
}

void UIController::MoveBoxRight()
{
	if (bigplane->CanMove(0, 1))
	{
		bigplane->Move(0, 1); 
		board.Update(); 
	}
}

void UIController::MoveBoxDown()
{
	if (bigplane->CanMove(1, 0))
	{
		bigplane->Move(1, 0); 
		board.Update(); 
	}
}

void UIController::MoveBoxUp()
{
	if (bigplane->CanMove(-1, 0))
	{
		bigplane->Move(-1, 0); 
		board.Update(); 
	}	
}

void UIController::shoot_Bullet()
{
	bigplane->shoot();
	board.Update();
}