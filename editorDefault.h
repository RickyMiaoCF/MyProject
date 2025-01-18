#pragma once
#include "editorWinBase.h"

class EditorWinDefualt : public EditorWindow
{
private:

	Component* m_TargetComponent = nullptr;
	
public:

	void Init() override;
	void Update() override;
	void Draw() override;

	void SetTarget(Component* target) { m_TargetComponent = target; }
};
