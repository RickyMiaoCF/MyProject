#pragma once
#include "gameObject.h"
#include <chrono>

class Polygon2D : public GameObject
{
private:

	// 新しく追加するメンバ変数
	float m_DiffuseColor; // 色の強さ
	std::chrono::steady_clock::time_point m_LastUpdateTime; // 最終更新時刻
	bool m_IsFadeOut;
	bool m_FadeOutFinish;

	ID3D11Buffer*				m_VertexBuffer = NULL;
	ID3D11ShaderResourceView*	m_Texture = NULL;

	ID3D11VertexShader*			m_VertexShader;
	ID3D11PixelShader*			m_PixelShader;
	ID3D11InputLayout*			m_VertexLayout;

	class Audio*					m_BGM{};
public:

	Polygon2D(Scene* scene) :GameObject(scene) {}

	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
};