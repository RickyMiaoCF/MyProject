#pragma once
#include"floatingSample.h"

class FloatingPlate:public Component 
{
private:

	XMFLOAT3 m_Pos;
	float m_Width;
	float m_Length;
	FloatingSample* m_Samples[4];

public:

	using Component::Component;

	void Init() override;
	void Uninit()override;
	void Update() override;

	void SetSize(float width, float length) { m_Width = width; m_Length = length; };
	XMFLOAT3 BuoyancyCal();
};