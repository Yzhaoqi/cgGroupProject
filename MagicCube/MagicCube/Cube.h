#include "CubeColor.h"

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
private:
    position pos;
    CubeColor cubeColor;
};