#pragma once
#include "editorWinBase.h"
#include "Sun.h"

class EditorWinLight: public EditorWindow
{
private:

	Sun*   m_Sun;

public:

	void Init() override;
	void Update() override;
};