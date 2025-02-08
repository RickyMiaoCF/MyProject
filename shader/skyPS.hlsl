
//pixelLightingPS.hlsl

#include	"common.hlsl"

void main(in PS_IN In, out float4  outDiffuse : SV_Target)
{

// 从 CameraBuffer 中获取相机位置
    float3 cameraPos = CameraPosition.xyz;

    // 当前像素的世界坐标
    float3 worldPos = In.WorldPosition.xyz;

    // 视线方向（相机→像素）
    float3 viewDir = normalize(worldPos - cameraPos);

    //===============================
    // 简易天空渐变示例：
    //    当 viewDir.y > 0 时，越靠上越接近 SkyColor
    //    当 viewDir.y < 0 时，越靠下越接近 GroundColor
    //===============================
    float t = saturate(viewDir.y * 0.5 + 0.5); // [-1,1] 映射到 [0,1]
    float3 skyColor = lerp(Light.GroundColor.rgb, Light.SkyColor.rgb, t);
    
    outDiffuse = float4(skyColor, 1.0f);

}





