
//pixelLightingPS.hlsl

#include	"common.hlsl"

Texture2D		g_Texture : register(t0);	//テクスチャ０番
SamplerState	g_SamplerState : register(s0);	//サンプラー０番

void main(in PS_IN In, out float4  outDiffuse : SV_Target)
{

    float3 normal = normalize(In.Normal.xyz);
    float3 lightDir = normalize(Light.Direction.xyz);

    float diffuseIntensity = max(dot(normal, lightDir), 0.0f);
    float3 diffuse = diffuseIntensity * Light.Diffuse.rgb * Material.Diffuse.rgb+0.2f;

    float3 ambient = Light.Ambient.rgb * Material.Ambient.rgb;

    float3 viewDir = normalize(CameraPosition.xyz - In.WorldPosition.xyz);
    float3 reflectDir = reflect(-lightDir, normal);
    float specularIntensity = pow(max(dot(viewDir, reflectDir), 0.0f), Material.Shininess);
    float3 specular = specularIntensity * Light.Specular.rgb;

    float4 texColor = g_Texture.Sample(g_SamplerState, In.TexCoord);

    float3 finalColor = texColor.rgb * (ambient + diffuse) + specular;
    
    outDiffuse = float4(finalColor, texColor.a);
}





