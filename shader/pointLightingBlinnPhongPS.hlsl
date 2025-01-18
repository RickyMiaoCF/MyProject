
//pixelLightingPS.hlsl

#include	"common.hlsl"

Texture2D		g_Texture : register(t0);	//�e�N�X�`���O��
SamplerState	g_SamplerState : register(s0);	//�T���v���[�O��

void	main(in PS_IN In, out float4  outDiffuse : SV_Target)
{
	//���̂�������ւ̃x�N�g��
	float4	lv = In.WorldPosition - Light.Position;
	//���̂ƌ����̋���
	float4	ld = length(lv);
	//�x�N�g���̐��K��
	lv = normalize(lv);

	//�����̌v�Z
	float	ofs = 1.0f - (1.0f / Light.PointLightParam.x) * ld;	//�����̌v�Z
	//������0������0�ɂ���B
	ofs = max(0, ofs);

	//�s�N�Z���̖@���𐳋K��
	float4	normal = normalize(In.Normal);
	//�����v�Z�i�n�[�t�����o�[�g�Łj
	float	light = 0.5f - 0.5f * dot(normal.xyz,lv.xyz);
	light *= ofs;	//���邳������


	//�e�N�X�`���̃s�N�Z���F���擾
	outDiffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);
	outDiffuse.rgb *= In.Diffuse.rgb * light;	//���邳����Z
	outDiffuse.a *= In.Diffuse.a;	//���l�ɖ��邳�͊֌W�Ȃ�
	outDiffuse.rgb += Light.Ambient.rgb;//�����̉��Z
	//=========================================================

	//�J��������s�N�Z���֌������x�N�g��
	float3 eyev = In.WorldPosition.xyz - CameraPosition.xyz;
	eyev = normalize(eyev);

	//�n�[�t�x�N�g�����v�Z
    float3 halfv = eyev + lv.xyz;// Light.Direction.xyz; //�����x�N�g���{���C�g�x�N�g��
	halfv = normalize(halfv);

	//�X�y�L�����[�̌v�Z
	float specular = -dot(halfv, normal.xyz);//�n�[�t�x�N�g���Ɩ@���̓���
	specular = saturate(specular);
	specular = pow(specular, 30);

	outDiffuse.rgb += (specular*ofs);

	
	
}





