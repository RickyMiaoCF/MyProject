#include "debug.h"

HWND g_DebugWindow;
HWND hDebugListBox;
std::unordered_map<std::string, int> debugVariableIndices;

// デバッグウィンドウの初期化
void InitDebugWindow(HINSTANCE hInstance, int nCmdShow) {
    const char* DEBUG_CLASS_NAME = "DebugWindowClass";
    const char* DEBUG_WINDOW_NAME = "Debug Information";

    WNDCLASSEX debugWcex = { sizeof(WNDCLASSEX), 0, DebugWndProc, 0, 0, hInstance, nullptr,
                             LoadCursor(nullptr, IDC_ARROW), (HBRUSH)(COLOR_WINDOW + 1),
                             nullptr, DEBUG_CLASS_NAME, nullptr };

    if (!RegisterClassEx(&debugWcex)) {
        MessageBox(nullptr, "Failed to register debug window class", "Error", MB_ICONERROR);
        return;
    }

    g_DebugWindow = CreateWindowEx(
        0, DEBUG_CLASS_NAME, DEBUG_WINDOW_NAME, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
        400, 300, nullptr, nullptr, hInstance, nullptr
    );

    if (!g_DebugWindow) {
        MessageBox(nullptr, "Failed to create debug window", "Error", MB_ICONERROR);
        return;
    }

    ShowWindow(g_DebugWindow, nCmdShow);
    UpdateWindow(g_DebugWindow);

    hDebugListBox = CreateWindowEx(
        0, "LISTBOX", nullptr,
        WS_CHILD | WS_VISIBLE | WS_VSCROLL | LBS_NOTIFY,
        10, 10, 360, 240,
        g_DebugWindow, nullptr, hInstance, nullptr
    );

    if (!hDebugListBox) {
        MessageBox(nullptr, "Failed to create debug list box", "Error", MB_ICONERROR);
        return;
    }
}

LRESULT CALLBACK DebugWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_CREATE:
        return 0;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    default:
        return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
}

void UpdateDebugValue(const std::string& varName, const std::string& value) {
    if (hDebugListBox) {
        auto it = debugVariableIndices.find(varName);
        if (it != debugVariableIndices.end()) {
            // 如果该变量已存在，更新它在列表框中的内容
            int listIndex = it->second;
            SendMessage(hDebugListBox, LB_DELETESTRING, listIndex, 0); // 删除旧的条目
            std::string displayText = varName + ": " + value;
            listIndex = SendMessage(hDebugListBox, LB_INSERTSTRING, listIndex, (LPARAM)displayText.c_str()); // 插入新的条目
            debugVariableIndices[varName] = listIndex; // 更新索引映射
        }
        else {
            // 如果该变量不存在，添加新条目
            std::string displayText = varName + ": " + value;
            int listIndex = SendMessage(hDebugListBox, LB_ADDSTRING, 0, (LPARAM)displayText.c_str());
            debugVariableIndices[varName] = listIndex; // 存储变量名与行索引的映射
        }
    }
}

void DebugVar(const std::string& varName, const XMFLOAT3& varValue) {
    std::stringstream ss;
    ss << "x: " << varValue.x << ", y: " << varValue.y << ", z: " << varValue.z;
    UpdateDebugValue(varName, ss.str());
}
