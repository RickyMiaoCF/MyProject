#pragma once
#include "editorWinBase.h"

class EditorWinObj : public EditorWindow
{
private:

	GameObject* m_TargetObject;

public:

	void Init() override;
	void Update() override;
	void Draw() override;

	void SetTarget(GameObject* target) { m_TargetObject = target; }
};