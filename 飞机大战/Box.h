#ifndef __BOX__
#define __BOX__

class BlackBoard; 

class Box
{
public:
	const static int BOX_SIZE = 20; 
	
	Box(int left, int top, int r, int c); 

	int getCOL(){return _col;}
    void Reset(int r, int c)
	{
		_row = r;
		_col = c;
	}

	virtual void OnDraw(BlackBoard &board)=0;
	virtual bool HitBullet_or_Plane()=0;
	virtual bool CanMove(int dx, int dy)=0;
	virtual void Move(int dx, int dy)=0;
	virtual bool Is_in(int r,int c)=0;
	virtual int getID()=0;
	virtual void clear()=0;

	virtual bool LeftTo(int x)
	{
		return _left + _col * BOX_SIZE < x;
	}

	virtual bool RightTo(int x)
	{
		return _left + (_col + 1) * BOX_SIZE - 1 > x;
	}

	virtual bool LowerTo(int y)
	{
		return _top + (-_row - 1) * BOX_SIZE + 1 < y; 
	}

	virtual bool Higherto(int y)
	{
		return _top - _row * BOX_SIZE > y;
	}

protected:
	int _left, _top; //游戏窗口的左上角
	int _row, _col; 
	int flag;
	
}; 


#endif // #ifndef __BOX__