#ifndef _BLACK_BOARD_H_
#define _BLACK_BOARD_H_

#include "GL/glut.h"

typedef void (*CallbackFunction)(); 
typedef void (*KeyboardFunction)(unsigned char key, int x, int y);
typedef void (*ReshapeFunction)(int width, int height); 
typedef void (*MouseButtonFunction)(int button, int state, int x, int y); 
typedef void (*MouseMotionFunction)(int x, int y); 
typedef void (*IdleFunction)(void); 
typedef void (*TimerFunction)(int value); 


class BlackBoard
{
public:

public:
	void InitCommandLine(int *argc, char **argv); 
	void InitWindowSize(int width, int height); 
	void UpdateWindowSize(int width, int height); 

	// 设置窗口绘制回调函数
	void InitDisplayCallback(CallbackFunction callback); 
	
	// 设置键盘事件回调函数
	void InitKeyboardCallback(KeyboardFunction callback);
	
	// 设置窗口缩放事件回调函数
	void InitReshapeCallback(ReshapeFunction callback);
	
	// 设置鼠标点击事件回调函数
	void InitMouseButtonCallback(MouseButtonFunction callback);
	
	// 设置鼠标移动事件回调函数
	void InitMouseMotionCallback(MouseMotionFunction callback);
	
	// 设置空闲状态回调函数
	void InitIdleCallback(IdleFunction callback);

	// 启动一个定时器，注意，只会触发一次，不会周期触发
	// 需要周期触发可在回调函数中，再次启动一个同样的定时器
	void InstallTimerCallback(unsigned int millis, TimerFunction callback, int value);



	// 创建并显示窗口，仅调用一次，之后，将进入事件循环
	void Show(); 



	// 标志窗口需要更新，通常是数据发生变化后，用于主动要求窗口重绘
	void Update(); 


	// 以下函数只用于绘制回调函数中，通常时，程序调用Update或系统发起Update-> 窗口重绘（事件循环调用绘制回调函数） -> 用以下函数绘制图形

	// 设置颜色，r/g/b为三色分量，0-1之间，
	// 如纯红为1,0,0;
	// 纯白为1,1,1
	void SetColor(double r, double g, double b); 
	// 清屏
	void Clear(); 
	// 讲绘制图像显示出来
	void Flush(); 

	// 画线，参数为两个端点的x、y坐标
	void DrawLine(int x1, int y1, int x2, int y2);

	// 画圆，参数为圆圆心x、y，半径
	void DrawCircle(int x, int y, int r);


private:
	int _width, _height; 
}; 









#endif // ifndef _BLACK_BOARD_H_
