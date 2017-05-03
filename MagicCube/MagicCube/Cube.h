#include "CubeColor.h"
#include <GL\freeglut.h>
#include "glm\glm.hpp"
#include "glm\gtc\type_ptr.hpp"
#include "glm\gtx\rotate_vector.hpp"

#define _USE_MATH_DEFINES
#include <math.h>

/*旋转轴*/
#define XAXIS 1000
#define YAXIS 1001
#define ZAXIS 1002
/*旋转方向*/
#define CLOCKWISE 1004  // 顺时针
#define EASTERN 1005    // 逆时针

/*
    position结构体：记录每一个立方体的中心位置
    变量x, y, z：立方体的位置，范围为0~n-1（对于n阶魔方）
*/
struct position {
    int x, y, z;
};

class Cube {
public:
    /*
    给定位置构造一个立方体。
    _pos: 立方体的位置
    _cubeColor: 立方体的颜色
    */
    Cube(position _pos, CubeColor _cubeColor);

    /*
    设置立方体的位置
    _pos: 立方体的位置
    */
    void setLocation(position _pos);

    /*
    得到立方体所在位置
    return: 返回立方体所在的位置
    */
    position getLocation();

    /*
    在显示立方体前设置颜色
    _cubeColor: 立方体的颜色
    */
    void setColor(CubeColor _cubeColor);

    /*
    显示/绘制立方体
    */
    void display();

    /*
    旋转立方体: 根据旋转轴以及旋转方向来旋转立方体，每次旋转的角度均为90度，旋转后需要更新立方体的位置。
    axis: 表示要绕着的旋转轴（x轴，y轴，z轴）
    direction: 表示旋转方向（顺时针或者逆时针）
    */
    void rotateCube(const int axis, const int direction);

	//如果要将本地坐标（魔方内坐标转换）转换到世界坐标，我需要知道魔方的阶，默认3阶
	/*
	给定位置构造一个立方体。
	_pos: 立方体的位置
	_cubeColor: 立方体的颜色
	_order：魔方的阶
	*/
	Cube(position _pos, CubeColor _cubeColor, int _order);
	Cube(position _pos);
	/*
	绕轴(x, y, z)旋转angle度。
	angle: 旋转角度（单位：度）
	(x, y, z)：旋转轴
	*/
	void rotate(float angle, float x, float y, float z);
	/*
	平移向量(x, y, z)。
	*/
	void translate(float x, float y, float z);
private:
    position pos;
    CubeColor cubeColor;

	//为display方便而添加的
	// Vertex indexs for the 6 faces of a cube.
	const int faces[6][4]{
		{ 0, 1, 2, 3 },//left
		{ 3, 2, 6, 7 },//bottom
		{ 7, 6, 5, 4 },//right
		{ 4, 5, 1, 0 },//top
		{ 5, 6, 2, 1 },//front
		{ 7, 4, 0, 3 } //back
	};

	//为display方便而添加的
	float colors[6][3]{
		{ 1, 0, 0 },// -- left
		{ 1, 1, 1 },// -- bottom
		{ 1, 0.5, 0 },// -- right
		{ 1, 1, 0 },// -- top
		{ 0, 1, 0 },// -- front
		{ 0, 0, 1 } // -- back
	};

	glm::vec3 vertex[8];//vertex coordinates

	float center[3]; //Cube cneter
	float lenght; //Cube Lenght

	int order; //Cube Order

	/*
	本地坐标转换到世界坐标
	*/
	void posLocalToWorld(position p, float &x, float &y, float &z);
};