#include "editorWinLight.h"

void EditorWinLight::Init()
{
	m_Sun = &Sun::GetInstance();
}

void EditorWinLight::Update()
{
	static float time = m_Sun->GetTime();
	static XMFLOAT4	direction{};
	static XMFLOAT4 diffuse = m_Sun->GetDefualtDiffuse();    //散乱反射
	static XMFLOAT4 ambient	= m_Sun->GetDefualtAmbient();    //環境光
	static XMFLOAT4 specular = m_Sun->GetSpecular();	//ハイライト


	ImGui::Begin("Light");        // Create a window called "Hello, world!" and append into it.

	ImGui::Text("Parameter.");               // Display some text (you can use a format strings too)

	if (ImGui::SliderFloat("Time", &time, 0.0f, 23.0f))
		m_Sun->SetTime(time);

	if (ImGui::ColorEdit4("Diffuse", (float*)&diffuse))
		m_Sun->SetDefualtDiffuse(diffuse);

	if (ImGui::ColorEdit4("Ambient", (float*)&ambient))
		m_Sun->SetDefualtAmbient(ambient);

	if (ImGui::ColorEdit4("Specular", (float*)&specular))
		m_Sun->SetSpecular(specular);

	ImGui::End();
}

