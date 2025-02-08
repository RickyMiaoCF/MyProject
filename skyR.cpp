#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "skyR.h"
#include "modelRenderer.h"
#include "input.h"
#include "scene.h"
#include "sceneCheck.h"

Camera* g_Camera{};

void SkyR::Init()
{

    CreateSkyBoxMesh();

    g_Camera = SceneCheck::GetInstance().getCurScene()->GetGameObject<Camera>();

    m_Position = g_Camera->GetPosition();

    // 3) 设置缩放大一些，便于包围场景
    m_Scale = XMFLOAT3(2000.0f, 2000.0f, 2000.0f);

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"shader\\skyVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\skyPS.cso");
}

void SkyR::Uninit()
{
	delete m_Component;
    g_Camera = nullptr;
    delete g_Camera;
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}


void SkyR::Update()
{   
    if (g_Camera)
    {
        m_Position = g_Camera->GetPosition();
    }
}

void SkyR::Draw()
{
	// 入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	//シェーダ設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	// ワールドマトリクス設定
	XMMATRIX world, scale, rot, trans;
	scale = XMMatrixScaling(m_Scale.x*(1.0f+m_ScaleCoefficient*0.01f), m_Scale.y*(1.0f + m_ScaleCoefficient * 0.01f), m_Scale.z* (1.0f + m_ScaleCoefficient * 0.01f));
	rot = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
	trans = XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;
	Renderer::SetWorldMatrix(world);

    // 5) 绑定顶点缓冲与索引缓冲
    UINT stride = sizeof(VERTEX_3D);
    UINT offset = 0;
    Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);
    Renderer::GetDeviceContext()->IASetIndexBuffer(m_IndexBuffer, DXGI_FORMAT_R32_UINT, 0);

    // 6) 设定图元拓扑结构(三角形列表)
    Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    // 7) 绘制
    Renderer::GetDeviceContext()->DrawIndexed(m_IndexCount, 0, 0);

}

void SkyR::CreateSkyBoxMesh()
{
    // 这里手动构建一个立方体(12个三角形，36个索引)
    // 也可以用其他加载方法，演示用硬编码

    // 8个顶点
    VERTEX_3D vertices[] =
    {
        // 前面
        { XMFLOAT3(-1,  1, -1), XMFLOAT3(0,0,-1), XMFLOAT4(1,1,1,1), XMFLOAT2(0,0) },
        { XMFLOAT3(1,  1, -1), XMFLOAT3(0,0,-1), XMFLOAT4(1,1,1,1), XMFLOAT2(1,0) },
        { XMFLOAT3(1, -1, -1), XMFLOAT3(0,0,-1), XMFLOAT4(1,1,1,1), XMFLOAT2(1,1) },
        { XMFLOAT3(-1, -1, -1), XMFLOAT3(0,0,-1), XMFLOAT4(1,1,1,1), XMFLOAT2(0,1) },

        // 背面
        { XMFLOAT3(-1,  1, 1), XMFLOAT3(0,0,1), XMFLOAT4(1,1,1,1), XMFLOAT2(0,0) },
        { XMFLOAT3(1,  1, 1), XMFLOAT3(0,0,1), XMFLOAT4(1,1,1,1), XMFLOAT2(1,0) },
        { XMFLOAT3(1, -1, 1), XMFLOAT3(0,0,1), XMFLOAT4(1,1,1,1), XMFLOAT2(1,1) },
        { XMFLOAT3(-1, -1, 1), XMFLOAT3(0,0,1), XMFLOAT4(1,1,1,1), XMFLOAT2(0,1) },
    };

    // 36个索引(12个三角形)
    unsigned int indices[] =
    {
        // 前面
        0,1,2, 0,2,3,
        // 后面
        5,4,7, 5,7,6,
        // 左面
        4,0,3, 4,3,7,
        // 右面
        1,5,6, 1,6,2,
        // 上面
        4,5,1, 4,1,0,
        // 下面
        3,2,6, 3,6,7
    };
    m_IndexCount = _countof(indices);

    // 创建顶点缓冲
    D3D11_BUFFER_DESC vbDesc{};
    vbDesc.Usage = D3D11_USAGE_DEFAULT;
    vbDesc.ByteWidth = sizeof(vertices);
    vbDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vbDesc.CPUAccessFlags = 0;

    D3D11_SUBRESOURCE_DATA vbData{};
    vbData.pSysMem = vertices;
    Renderer::GetDevice()->CreateBuffer(&vbDesc, &vbData, &m_VertexBuffer);

    // 创建索引缓冲
    D3D11_BUFFER_DESC ibDesc{};
    ibDesc.Usage = D3D11_USAGE_DEFAULT;
    ibDesc.ByteWidth = sizeof(indices);
    ibDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    ibDesc.CPUAccessFlags = 0;

    D3D11_SUBRESOURCE_DATA ibData{};
    ibData.pSysMem = indices;
    Renderer::GetDevice()->CreateBuffer(&ibDesc, &ibData, &m_IndexBuffer);
}