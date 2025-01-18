#pragma once
#include <windows.h>

class Mouse {
public:
    Mouse();
    ~Mouse();

    void OnMouseMove(int x, int y);
    void OnMouseDown(WPARAM buttonState);
    void OnMouseUp(WPARAM buttonState);
    void OnMouseWheel(short delta);

    // 获取鼠标当前的状态
    int GetMouseX() const;
    int GetMouseY() const;
    bool IsLeftButtonDown() const;

private:
    int m_x; // 鼠标X坐标
    int m_y; // 鼠标Y坐标
    bool m_leftButtonDown; // 左键是否按下
    bool m_rightButtonDown; // 右键是否按下
};
#pragma once
