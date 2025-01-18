#pragma once
#include "gameObject.h"

class Snow : public GameObject
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
		float FallSpeed;
		float RotationX;
		float RotationY;
	};
	static const int PARTICLE_MAX = 100000;
	const float FALL_SPEED = 0.1f; // Snowflake falling speed
	const float HORIZONTAL_DRIFT = 0.002f; // Horizontal drift speed
	PARTICLE m_Particle[PARTICLE_MAX]{};

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};