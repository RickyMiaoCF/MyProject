#include "main.h"
#include "renderer.h"
#include "polygon2D.h"
#include "audio.h"
#include "input.h"

void Polygon2D::Init()
{
	// フェードインを開始するための初期化
	m_DiffuseColor = 0.0f;
	m_LastUpdateTime = std::chrono::steady_clock::now();
	m_IsFadeOut = false;
	m_FadeOutFinish = false;

	VERTEX_3D vertex[4];

	vertex[0].Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[0].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);

	vertex[1].Position = XMFLOAT3(1280.0f, 0.0f, 0.0f);
	vertex[1].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f);

	vertex[2].Position = XMFLOAT3(0.0f, 720.0f, 0.0f);
	vertex[2].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);

	vertex[3].Position = XMFLOAT3(1280.0f, 720.0f, 0.0f);
	vertex[3].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = XMFLOAT2(1.0f, 1.0f);

	//頂点バッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);


	//テクスチャ読み込み
	TexMetadata metadata;
	ScratchImage image;
	LoadFromWICFile(L"asset\\texture\\Brick.png", WIC_FLAGS_NONE, &metadata, image);
	CreateShaderResourceView(Renderer::GetDevice(), image.GetImages(), image.GetImageCount(), metadata, &m_Texture);
	assert(m_Texture);

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"shader\\unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\unlitTexturePS.cso");

	//BGM再生
	m_BGM = new Audio(this);
	m_BGM->Load("asset\\audio\\bgm.wav");
	m_BGM->Play(true);
}

void Polygon2D::Uninit()
{
	//BGM終了・解放
	m_BGM->Uninit();
	delete m_BGM;
	m_VertexBuffer->Release();
	m_Texture->Release();

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

}

void Polygon2D::Update()
{
	auto currentTime = std::chrono::steady_clock::now();
	std::chrono::duration<float> elapsedTime = currentTime - m_LastUpdateTime;

	// m_DiffuseColorを増加させてフェードイン
	float fadeSpeed = 0.3f; // フェードインの速度を調整
	m_DiffuseColor += elapsedTime.count() * fadeSpeed;
	if (m_DiffuseColor > 1.0f) 
	{
		m_DiffuseColor = 1.0f;
	}
	// 最終更新時間を現在の時間に更新
	m_LastUpdateTime = currentTime;
	if (Input::GetKeyTrigger(VK_ADD))
	{
		m_BGM->VolumeUp();
	}

	if (Input::GetKeyTrigger(VK_SUBTRACT))
	{

		m_BGM->VolumeDown();
	}

	if (Input::GetKeyTrigger(VK_MULTIPLY))
	{

		//m_BGM->VolumeDown();
	}
}

void Polygon2D::Draw()
{
	//入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	//シェーダ設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	//マトリクス設定
	Renderer::SetWorldViewProjection2D();

	//頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	// マテリアル設定
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = XMFLOAT4(m_DiffuseColor, m_DiffuseColor, m_DiffuseColor, 1.0f);
	material.TextureEnable = true;
	Renderer::SetMaterial(material);

	//テクスチャ設定
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);

	//プリミティブポロジ設定
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//ポリゴン描画
	Renderer::GetDeviceContext()->Draw(4, 0);
}
