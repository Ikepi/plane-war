#ifndef __UICONTROLLER__
#define __UICONTROLLER__

#include <list>

class Box;
class BlackBoard; 
class MyPlane;

class UIController
{
public:
	// 整个区域容纳的方块数量
	const static int ROWS = 30; 
	const static int COLS = 15;
	int _boxes[ROWS][COLS]; //创建一个相应的数组,约定1：子弹；2：我机；3：敌机
	// 初始掉落位置
	const static int INITIAL_COL = COLS / 2; 
	
	std::list<Box*> figure;//存放子弹和飞机

public:
	// UIController采用单子模式，整个软件中唯一
	static UIController &handle()
	{
		static UIController instance; 
		return instance; 
	}

	// 掉落速度，单位毫秒，即每X毫秒移动一格
	int PlaneGameSpeed() { return 500;}
	int BulletGameSpeed() {return 30;}

	// 定时器处理逻辑，此处主要用于驱动方块自动掉落
	void PlaneOnTimer(int code);
	void BulletOnTimer(int code);

	// 绘图逻辑，包括边框绘制，方块绘制
	void OnDraw(BlackBoard &board); 

	// 按键逻辑，主要处理用户左、右、下三个方向的操作
	void OnKey(unsigned char key, int x, int y); 

	// 判断方块是否触碰左边界、右边界、下边界、及已有固定方块
	bool HitLeft(Box &box);
	bool HitRight(Box &box);
	bool HitBottom(Box &box);
	bool HitTop(Box &box);
	bool HitBulletPlane(Box &box); 

	~UIController(); 

private:
	UIController(); //单子模式，外界无法使用构造函数
	
	// 删除已满的行
	void EraseFullRows();

	// 删除已满行后，上方方块下落
	void PushRows(int row);

	// 活动方块控制逻辑
	void MoveBoxLeft(); 
	void MoveBoxRight(); 
	void MoveBoxDown(); 
	void MoveBoxUp();
	void shoot_Bullet();
		
private:
	int _left,  _bottom; //用于构造游戏框的大小，不是命令窗口
	int _right, _top; 

	
	MyPlane *bigplane;
}; 


#endif // #ifndef __UICONTROLLER__