#include <type_traits>
#include "editorWinObj.h"
#include "renderer.h"
#include "player.h"
#include "sky.h"
#include "debug.h"
#include "Sun.h"
#include "wave.h"

static ID3D11Device* g_pd3dDevice = nullptr;
static ID3D11DeviceContext* g_pd3dDeviceContext = nullptr;
static ID3D11RenderTargetView* g_mainRenderTargetView = nullptr;
static IDXGISwapChain* g_pSwapChain = nullptr;
static HWND g_Window = nullptr;

static bool g_SwapChainOccluded = false;
static GameObject* g_TestComponent;
static ImVec4 clear_color = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);

void EditorWinObj::Init()
{
	g_Window = GetWindow();

	g_pd3dDevice = Renderer::GetDevice();
	g_pd3dDeviceContext = Renderer::GetDeviceContext();
	g_mainRenderTargetView = Renderer::GetRenderTargetView();
	g_pSwapChain = Renderer::GetSwapChain();

	m_IsEnable = true;


}

void EditorWinObj::Update()
{

	// 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
	{
		static XMFLOAT3 pos= m_TargetObject->GetPosition();
		static XMFLOAT3 rot = m_TargetObject->GetRotation();
		static float posX = pos.x;
		static float posY = pos.y;
		static float posZ = pos.z;
		static float rotY = rot.y;

		static float scale = m_TargetObject->GetScaleCoefficient();

		static bool enable = m_TargetObject->GetEnabled();
		static int counter = 0;

		static float time = Sun::GetInstance().GetTime();

		ImGui::Begin("Object");        // Create a window called "Hello, world!" and append into it.

		ImGui::Text("Parameter:");               // Display some text (you can use a format strings too)

		/*if(ImGui::SliderFloat("TimeOfDay",&))*/

		if (ImGui::SliderFloat("PosX", &posX, -100.0f, 100.0f))
			m_TargetObject->SetPositionX(posX);
		if (ImGui::SliderFloat("PosY", &posY, -100.0f, 100.0f))
			m_TargetObject->SetPositionY(posY);
		if (ImGui::SliderFloat("RotY", &rotY, -1.0f, 1.0f))
			m_TargetObject->SetRotationY(rotY);
		if (ImGui::SliderFloat("Scale", &scale, -200.0f, 200.0f))
			m_TargetObject->SetScaleCoefficient(scale);

		ImGui::Text("Wave:");
		if (Wave* waveObj = dynamic_cast<Wave*>(m_TargetObject)) // 检查并转换一次
		{
			float amplitude = waveObj->GetAmplitude();
			float waveLength = waveObj->GetWaveLength();
			float waveCycle = waveObj->GetWaveCycle();

			// 调整滑动条，并更新 Wave 的属性
			if (ImGui::SliderFloat("Amplitude", &amplitude, 0.0f, 50.0f))
				waveObj->SetAmplitude(amplitude);

			if (ImGui::SliderFloat("WaveLength", &waveLength, 0.0f, 50.0f))
				waveObj->SetWaveLength(waveLength);

			if (ImGui::SliderFloat("WaveCycle", &waveCycle, 0.0f, 50.0f))
				waveObj->SetWaveCycle(waveCycle);
		}

		ImGui::End();
	}


}

void EditorWinObj::Draw()
{

	ImGui::Render();

	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	// Present
	HRESULT hr = g_pSwapChain->Present(1, 0);   // Present with vsync
	//HRESULT hr = g_pSwapChain->Present(0, 0); // Present without vsync
	g_SwapChainOccluded = (hr == DXGI_STATUS_OCCLUDED);
}
