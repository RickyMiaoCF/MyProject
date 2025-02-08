#pragma once
#include <DirectXMath.h>
#include <algorithm>
#include <minwindef.h>
using namespace DirectX;

class Sun {
private:
	XMFLOAT4 m_Direction;  // 太阳方向
	XMFLOAT4 m_Diffuse;    // 太阳漫反射颜色
	XMFLOAT4 m_Ambient;    // 环境光颜色
	XMFLOAT4 m_Specular;

	XMFLOAT4 m_SkyColor;
	XMFLOAT4 m_GroundColor;

	XMFLOAT4 m_DefualtDiffuse;    // 太阳漫反射颜色
	XMFLOAT4 m_DefualtAmbient;    // 环境光颜色

	bool m_Enable;         // 光照开关
	float m_Time;          // 当前时间，范围 [0.0, 24.0]

	Sun() {
		// 初始化默认值
		m_Enable = true;
		m_Time = 12.0f; // 默认正午

		m_DefualtDiffuse = XMFLOAT4(0.9f, 0.57f, 0.27f, 0.39f);    // 默认白色偏暖
		//m_DefualtAmbient = XMFLOAT4(0.3f, 0.3f, 0.4f, 1.0f);    // 默认柔和环境光
		m_DefualtAmbient = XMFLOAT4(0.5f, 0.42f, 0.337f, 1.0f);    // 默认柔和环境光

		m_SkyColor = XMFLOAT4(0.6f, 0.7f, 1.0f, 1.0f);
		m_GroundColor = XMFLOAT4(0.4f, 0.3f, 0.2f, 1.0f);

		m_Direction = XMFLOAT4(0.0f, -1.0f, 0.0f, 0.0f);
		m_Diffuse = m_DefualtDiffuse;    // 太阳漫反射颜色
		m_Ambient = m_DefualtAmbient;    // 环境光颜色
		/*m_Specular = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);;*/
		m_Specular = XMFLOAT4(0.55f, 0.36f, 0.117f, 1.0f);; 
	}

public:
	static Sun& GetInstance() {
		static Sun instance;
		return instance;
	}


	// 更新太阳状态
	void Update() {
		// 根据时间计算太阳轨迹
		float angle = (m_Time / 24.0f) * XM_2PI; // 一天从 0 到 2PI
		float elevation = XM_PIDIV4 * sin(angle - XM_PIDIV2);
		float azimuth = cos(angle) * XM_PI;        // 方位角范围 -180° 到 180°

		m_Direction = XMFLOAT4(
			cos(angle),
			sin(elevation),
			sin(angle),
			0.0f
		);

		// 调整漫反射颜色和强度
		float intensity = (sin(elevation) > 0.5f) ? sin(elevation) : 0.5f; // 光强随高度变化

		m_Diffuse = XMFLOAT4(
			m_DefualtDiffuse.x * intensity,       // 红色
			m_DefualtDiffuse.y * intensity,       // 绿色
			m_DefualtDiffuse.z * intensity,       // 蓝色
			1.0f
		);

		// 调整环境光颜色
		m_Ambient = XMFLOAT4(
			m_DefualtAmbient.x * intensity,       // 红色
			m_DefualtAmbient.y * intensity,       // 绿色
			m_DefualtAmbient.z * intensity,       // 蓝色
			1.0f
		);
	}

	// 获取光源属性
	const XMFLOAT4& GetDefualtDiffuse() const { return m_DefualtDiffuse; }
	const XMFLOAT4& GetDefualtAmbient() const { return m_DefualtAmbient; }

	const XMFLOAT4& GetDirection() const { return m_Direction; }
	const XMFLOAT4& GetDiffuse() const { return m_Diffuse; }
	const XMFLOAT4& GetAmbient() const { return m_Ambient; }
	const XMFLOAT4& GetSpecular() const { return m_Specular; }
	const XMFLOAT4& GetSkyColor() const { return m_SkyColor; }
	const XMFLOAT4& GetGroundColor() const { return m_GroundColor; }

	float GetTime() const { return m_Time; }
	bool IsEnabled() const { return m_Enable; }

	void SetDefualtDiffuse(XMFLOAT4 diffuse) { m_DefualtDiffuse = diffuse; }
	void SetDefualtAmbient(XMFLOAT4 ambient) { m_DefualtAmbient = ambient; }
	void SetSpecular(XMFLOAT4 specular) { m_Specular = specular; }
	void SetSkyColor(XMFLOAT4 skyColor) { m_SkyColor = skyColor; }
	void SetGroundColor(XMFLOAT4 groundColor) { m_GroundColor = groundColor; }

	void SetTime(float time) { m_Time = fmod(time, 24.0f); } // 限制在 [0.0, 24.0] 范围
	void SetEnabled(bool enable) { m_Enable = enable; }


};