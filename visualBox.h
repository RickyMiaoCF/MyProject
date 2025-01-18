#pragma once
#include"component.h"
#include "editorDataStruct.h"
#define BOX_VERTEX_NUM	8

class VisualBox :public Component
{
private:

	class GameObject* m_Parent {};

	ID3D11Buffer* m_VertexBuffer;
	ID3D11Buffer* m_IndexBuffer;

	EditorDataComponent* m_EditorData;

	VERTEX_3D m_Vertex[BOX_VERTEX_NUM];

public:
	using Component::Component;

	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

};

