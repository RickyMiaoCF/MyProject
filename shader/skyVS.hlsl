
//pixelLightingVS.hlsl

#include "common.hlsl"

void main(in VS_IN  In, out PS_IN  Out)
{
    
    // 1) 计算世界坐标
    float4 worldPos = mul(In.Position, World);

    // 2) 计算视图坐标
    float4 viewPos = mul(worldPos, View);

    // 3) 计算投影坐标 (裁剪空间)
    float4 projPos = mul(viewPos, Projection);

    // 顶点着色器输出
    Out.Position = projPos; // SV_POSITION
    Out.WorldPosition = worldPos; // 传给像素着色器的世界空间坐标

    // 法线也可按照需要进行变换；若仅做简单天空，可无须光照
    // 此处演示按世界矩阵进行变换（一般需要 3x3 或法线矩阵修正）
    float4 normalWorld = mul(In.Normal, World);
    Out.Normal = normalWorld;

    // 直接传递顶点色与纹理坐标
    Out.Diffuse = In.Diffuse;
    Out.TexCoord = In.TexCoord;

}


