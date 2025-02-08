#include "editorWinLight.h"

static float g_Time{};
static XMFLOAT4	g_Direction{};
static XMFLOAT4 g_Diffuse{};    //散乱反射
static XMFLOAT4 g_Ambient{};    //環境光
static XMFLOAT4 g_Specular{};	//ハイライト
static XMFLOAT4 g_SkyColor{};
static XMFLOAT4 g_GroundColor{};


void EditorWinLight::Init()
{
	m_Sun = &Sun::GetInstance();
}

void EditorWinLight::Update()
{
	g_Time = m_Sun->GetTime();
	g_Direction = m_Sun->GetDirection();
	g_Diffuse = m_Sun->GetDefualtDiffuse();    //散乱反射
	g_Ambient	= m_Sun->GetDefualtAmbient();    //環境光
	g_Specular = m_Sun->GetSpecular();	//ハイライト
	g_SkyColor = m_Sun->GetSkyColor();
	g_GroundColor = m_Sun->GetGroundColor();
	


	ImGui::Begin("Light");        // Create a window called "Hello, world!" and append into it.

	ImGui::Text("Parameter.");               // Display some text (you can use a format strings too)

	if (ImGui::SliderFloat("Time", &g_Time, 0.0f, 23.0f))
		m_Sun->SetTime(g_Time);

	if (ImGui::ColorEdit4("Diffuse", (float*)&g_Diffuse))
		m_Sun->SetDefualtDiffuse(g_Diffuse);

	if (ImGui::ColorEdit4("Ambient", (float*)&g_Ambient))
		m_Sun->SetDefualtAmbient(g_Ambient);

	if (ImGui::ColorEdit4("Specular", (float*)&g_Specular))
		m_Sun->SetSpecular(g_Specular);

	if (ImGui::ColorEdit4("SkyColor", (float*)&g_SkyColor))
		m_Sun->SetSkyColor(g_SkyColor);

	if (ImGui::ColorEdit4("GroundColor", (float*)&g_GroundColor))
		m_Sun->SetGroundColor(g_GroundColor);



	ImGui::End();
}

