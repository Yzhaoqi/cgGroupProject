#include "CubeColor.h"

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
private:
    position pos;
    CubeColor cubeColor;
};