#pragma once
#include <string>
#include <windows.h>
#include <unordered_map>
#include <sstream>
#include <DirectXMath.h>  

using namespace DirectX; 
// 初始化调试窗口函数
void InitDebugWindow(HINSTANCE hInstance, int nCmdShow);
LRESULT CALLBACK DebugWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void UpdateDebugValue(const std::string& varName, const std::string& value);

// 更新関数的模板
template <typename T>
void DebugVar(const std::string& varName, const T& varValue) {
    std::stringstream ss;
    ss << varValue;
    UpdateDebugValue(varName, ss.str());
}

// 重载的 DebugVar 函数用于 XMFLOAT3
void DebugVar(const std::string& varName, const XMFLOAT3& varValue);

// 宏定义，用于自动获取变量名称并监视变量
#define DEBUG_VAR(variable) DebugVar(#variable, variable)

extern HWND g_DebugWindow;
extern HWND hDebugListBox;
extern std::unordered_map<std::string, int> debugVariableIndices;
