/*
    管理立方体六个面的颜色
*/
struct CubeColor {
    int up[3] = { 255, 255, 0 };
    int down[3] = { 255, 255, 255 };
    int left[3] = { 255, 0, 0 };
    int right[3] = { 255, 97, 0 };
    int front[3] = { 0, 255, 0 };
    int back[3] = { 0, 0, 255 };
};