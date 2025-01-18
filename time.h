#pragma once
#include "gameObject.h"
#include <chrono>
using namespace std::chrono;

class Time : public GameObject
{
public:
    void Init();
    void Uninit();
    void Update();
    void Draw();
    void AddTime(int Count); // 保留以备将来使用

private:
    XMFLOAT3 m_Position;
    ID3D11Buffer* m_VertexBuffer;
    ID3D11ShaderResourceView* m_Texture;
    ID3D11InputLayout* m_VertexLayout;
    ID3D11VertexShader* m_VertexShader;
    ID3D11PixelShader* m_PixelShader;
    int m_Count; // 保留以备将来使用
    steady_clock::time_point m_StartTime;

};