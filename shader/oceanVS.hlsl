
//pixelLightingVS.hlsl

#include "common.hlsl"

void main(in VS_IN  In, out PS_IN  Out)
{
    float4 worldPosition = mul(In.Position, World);
    Out.WorldPosition = worldPosition;

    // 裁剪空间位置
    Out.Position = mul(worldPosition, View);
    Out.Position = mul(Out.Position, Projection);

    // 计算世界空间法线
    Out.Normal = normalize(mul(In.Normal, World));

    // 传递纹理坐标
    Out.TexCoord = In.TexCoord;


}


