#pragma once
#include "gameObject.h"
#include <chrono>

class Polygon2DR : public GameObject
{
private:

	// 新しく追加するメンバ変数
	float m_DiffuseColor = 0.0f; // 色の強さ
	std::chrono::steady_clock::time_point m_LastUpdateTime = {}; // 最終更新時刻
	bool m_IsFadeOut = false;
	bool m_FadeOutFinish =false;
	bool m_StartFlag = false;

	ID3D11Buffer* m_VertexBuffer = NULL;
	ID3D11ShaderResourceView* m_Texture = NULL;

	ID3D11VertexShader* m_VertexShader = NULL;
	ID3D11PixelShader* m_PixelShader = NULL;
	ID3D11InputLayout* m_VertexLayout = NULL;

	class Audio* m_BGM{};
public:

	Polygon2DR(Scene* scene) :GameObject(scene) {}

	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
};