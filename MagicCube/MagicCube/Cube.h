#include "CubeColor.h"
#include <GL\freeglut.h>
#include "glm\glm.hpp"
#include "glm\gtc\type_ptr.hpp"
#include "glm\gtx\rotate_vector.hpp"

#define _USE_MATH_DEFINES
#include <math.h>

/*��ת��*/
#define XAXIS 1000
#define YAXIS 1001
#define ZAXIS 1002
/*��ת����*/
#define CLOCKWISE 1004  // ˳ʱ��
#define EASTERN 1005    // ��ʱ��

/*
    position�ṹ�壺��¼ÿһ�������������λ��
    ����x, y, z���������λ�ã���ΧΪ0~n-1������n��ħ����
*/
struct position {
    int x, y, z;
};

class Cube {
public:
    /*
    ����λ�ù���һ�������塣
    _pos: �������λ��
    _cubeColor: ���������ɫ
    */
    Cube(position _pos, CubeColor _cubeColor);

    /*
    �����������λ��
    _pos: �������λ��
    */
    void setLocation(position _pos);

    /*
    �õ�����������λ��
    return: �������������ڵ�λ��
    */
    position getLocation();

    /*
    ����ʾ������ǰ������ɫ
    _cubeColor: ���������ɫ
    */
    void setColor(CubeColor _cubeColor);

    /*
    ��ʾ/����������
    */
    void display();

    /*
    ��ת������: ������ת���Լ���ת��������ת�����壬ÿ����ת�ĽǶȾ�Ϊ90�ȣ���ת����Ҫ�����������λ�á�
    axis: ��ʾҪ���ŵ���ת�ᣨx�ᣬy�ᣬz�ᣩ
    direction: ��ʾ��ת����˳ʱ�������ʱ�룩
    */
    void rotateCube(const int axis, const int direction);

	//���Ҫ���������꣨ħ��������ת����ת�����������꣬����Ҫ֪��ħ���Ľף�Ĭ��3��
	/*
	����λ�ù���һ�������塣
	_pos: �������λ��
	_cubeColor: ���������ɫ
	_order��ħ���Ľ�
	*/
	Cube(position _pos, CubeColor _cubeColor, int _order);
	Cube(position _pos);
	/*
	����(x, y, z)��תangle�ȡ�
	angle: ��ת�Ƕȣ���λ���ȣ�
	(x, y, z)����ת��
	*/
	void rotate(float angle, float x, float y, float z);
	/*
	ƽ������(x, y, z)��
	*/
	void translate(float x, float y, float z);
private:
    position pos;
    CubeColor cubeColor;

	//Ϊdisplay�������ӵ�
	// Vertex indexs for the 6 faces of a cube.
	const int faces[6][4]{
		{ 0, 1, 2, 3 },//left
		{ 3, 2, 6, 7 },//bottom
		{ 7, 6, 5, 4 },//right
		{ 4, 5, 1, 0 },//top
		{ 5, 6, 2, 1 },//front
		{ 7, 4, 0, 3 } //back
	};

	//Ϊdisplay�������ӵ�
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
	��������ת������������
	*/
	void posLocalToWorld(position p, float &x, float &y, float &z);
};