
//C言語から受け取る情報を格納する変数
//コンスタントバッファの内容がここに入る

cbuffer WorldBuffer : register(b0) //定数バッファ0番
{
    matrix World; //ワールド行列
}

cbuffer ViewBuffer : register(b1) //定数バッファ1番
{
    matrix View; //カメラ行列
}

cbuffer ProjectionBuffer : register(b2) //定数バッファ2番
{
    matrix Projection; //プロジェクション行列
}

struct MATERIAL
{
	float4 Ambient;
	float4 Diffuse;
	float4 Specular;
	float4 Emission;
	float Shininess;
	bool TextureEnable;
	float2 Dummy;
};

cbuffer MaterialBuffer : register(b3)
{
	MATERIAL Material;
}


struct LIGHT
{
	bool Enable;
	bool3 Dummy;
	float4 Direction;
	float4 Diffuse;
	float4 Ambient;
    float4 Specular; //ハイライト
    float4 SkyColor; //天球色
    float4 GroundColor; //地面色
    
    float4 GroundNormal; //地面の法線
    float4 Position; //光の位置
    float4 PointLightParam; //x 光の届く距離  y ライトの個数 z 金属感  w 滑らかさ
};

cbuffer LightBuffer : register(b4)
{
	LIGHT Light;
}


cbuffer CameraBuffer : register(b5) //バッファ5番
{
    float4 CameraPosition; //カメラの座標
}

cbuffer ParameterBuffer : register(b6)
{
    float4 Parameter;
}


struct VS_IN
{
    float4 Position : POSITION0; //ポジションゼロ
    float4 Normal : NORMAL0; //ノーマルゼロ
    float4 Diffuse : COLOR0; //カラーゼロ
    float2 TexCoord : TEXCOORD0; //テクスコードゼロ
}; //表示するポリゴンの頂点レイアウトと同じ


struct PS_IN
{
    float4 Position : SV_POSITION; //ピクセルの画面座標
    float4 WorldPosition : POSITION0; //ピクセルの空間での座標
    float4 Normal : NORMAL0; //ピクセルの法線
    float4 Diffuse : COLOR0; //ピクセルの色
    float2 TexCoord : TEXCOORD0; //ピクセルのテクスチャ座標
};