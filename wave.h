#pragma once

#include <d3d11.h>
#include "gameObject.h"
#include "renderer.h"




class Wave : public GameObject
{
private:
	ID3D11Buffer* m_VertexBuffer{};
	ID3D11Buffer* m_IndexBuffer{};				// インデックスBuffer

	ID3D11ShaderResourceView* m_Texture{};

	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

	VERTEX_3D m_Vertex[21][21] = {};

	float m_Amplitude = 1.0f;
	float m_WaveLength = 0.45f;
	float m_WaveCycle = 4.5f;

	float m_Time = 0.0f;

public:

	Wave(Scene* scene) :GameObject(scene) {}

	void Init();
	void Uninit();
	void Update();
	void Draw();

	float GetAmplitude() { return m_Amplitude; }
	float GetWaveLength() { return m_WaveLength; }
	float GetWaveCycle() { return m_WaveCycle; }

	void SetAmplitude(float amplitude) { m_Amplitude = amplitude; }
	void SetWaveLength(float waveLength) { m_WaveLength = waveLength; }
	void SetWaveCycle(float waveCyecle) { m_WaveCycle = waveCyecle; }

	float getHeight(XMFLOAT3 position);
};