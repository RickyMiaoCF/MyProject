#pragma once
#include "main.h"
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include "component.h"
#include "gameObject.h"

class EditorWindow
{

protected:
	
	XMFLOAT2 m_Position;
	float m_Height;
	float m_Width;
	bool m_IsEnable;

public:
	EditorWindow() {};
	~EditorWindow() {};
	
	virtual void Init() {};
	virtual void Update() {};
	virtual void Draw() {};
};

