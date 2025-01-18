#pragma once
#include "gameObject.h"

class ParticleEmitter : public GameObject
{
private:
	ID3D11Buffer* m_VertexBuffer{};
	ID3D11ShaderResourceView* m_Texture{};

	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};
	int m_Count{}; //アニメーション枚数計算用

	struct PARTICLE
	{
		bool Enable;
		int Life;
		float Angle;
		XMFLOAT3 Position;
		XMFLOAT3 Velocity;
	};
	static const int PARTICLE_MAX = 1000;
	PARTICLE m_Particle[PARTICLE_MAX]{};

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};