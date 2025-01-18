#pragma once
#include "component.h"

class FloatingSample
{
private:

	XMFLOAT3 m_Position;

public:
	FloatingSample() { m_Position = XMFLOAT3(0.0f, 0.0f, 0.0f); };
	~FloatingSample() {};

	void SetPos(XMFLOAT3 pos) { m_Position = pos; };
	XMFLOAT3 GetPos(){ return m_Position; };
};
