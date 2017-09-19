#include "Box.h"

class EnemyPlane:public Box
{
public:
	EnemyPlane(int left, int top, int r, int c);
	~EnemyPlane();

	virtual void OnDraw(BlackBoard &board); 
	virtual bool HitBullet_or_Plane();
	virtual bool CanMove(int dx, int dy); 
	virtual void Move(int dx, int dy);
	virtual bool Is_in(int r,int c);

	virtual bool LeftTo(int x)
	{
		return _left + _col * BOX_SIZE < x;
	}

	virtual bool RightTo(int x)
	{
		return _left + (_col + 3) * BOX_SIZE - 1 > x; 
	}

	virtual bool LowerTo(int y)
	{
		return _top + (-_row - 2) * BOX_SIZE + 1 < y; 
	}

	virtual bool Higherto(int y)
	{
		return _top - _row * BOX_SIZE > y;
	}
	virtual void clear();
	virtual int getID(){return flag;}

private:

};
