#pragma once
#include <DirectXMath.h>
using namespace DirectX;

struct EditorDataComponent
{
	bool m_IsEnabled{};
	float m_Width{};	//x
	float m_Height{};	//y
	float m_Length{};	//z
	XMFLOAT3 m_Position{};
	XMFLOAT3 m_Rotation{};
	XMFLOAT3 m_Scale{};
};