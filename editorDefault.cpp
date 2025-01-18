#include "editorDefault.h"
#include "renderer.h"
#include "player.h"
#include "visualBox.h"
#include "debug.h"
#include "Sun.h"


static ID3D11Device* g_pd3dDevice = nullptr;
static ID3D11DeviceContext* g_pd3dDeviceContext = nullptr;
static ID3D11RenderTargetView* g_mainRenderTargetView = nullptr;
static IDXGISwapChain* g_pSwapChain = nullptr;
static HWND g_Window = nullptr;

static bool g_SwapChainOccluded = false;
static Component* g_TestComponent;
static ImVec4 clear_color = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);

void EditorWinDefualt::Init()
{
	g_Window = GetWindow();

	g_pd3dDevice = Renderer::GetDevice();
	g_pd3dDeviceContext = Renderer::GetDeviceContext();
	g_mainRenderTargetView = Renderer::GetRenderTargetView();
	g_pSwapChain = Renderer::GetSwapChain();

	m_IsEnable = true;


}

void EditorWinDefualt::Update()
{

	// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
	if (m_IsEnable)
		ImGui::ShowDemoWindow(&m_IsEnable);

	// 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
	{
		static float posx = m_TargetComponent->GetPositionX();
		static float width = m_TargetComponent->GetWidth();
		static float length = m_TargetComponent->GetLength();
		static float heigth = m_TargetComponent->GetHeight();
		static float scaleX = m_TargetComponent->GetScaleX();
		static bool enable = m_TargetComponent->GetEnabled();
		static int counter = 0;


		ImGui::Begin("VisualBox");        // Create a window called "Hello, world!" and append into it.

		ImGui::Text("Parameter.");               // Display some text (you can use a format strings too)
		ImGui::Checkbox("Demo Window", &m_IsEnable);      // Edit bools storing our window open/close state

		if (ImGui::Checkbox("Enable", &enable)) {
			enable != enable;
			m_TargetComponent->SetEnabled(enable);
		}
		
		/*if(ImGui::SliderFloat("TimeOfDay",&))*/

		if (ImGui::SliderFloat("PosX", &posx, 0.0f, 1000.0f))
			m_TargetComponent->SetPosition(XMFLOAT3(posx,0,0));
		if (ImGui::SliderFloat("Width", &width, 0.0f, 100.0f))
			m_TargetComponent->SetWidth(width);
		if (ImGui::SliderFloat("Length", &length, 0.0f, 100.0f))
			m_TargetComponent->SetLength(length);
		if (ImGui::SliderFloat("Height", &heigth, 0.0f, 100.0f))
			m_TargetComponent->SetHeight(heigth);
		
		DEBUG_VAR(posx);
		DEBUG_VAR(m_TargetComponent->GetPositionX());

		ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

		if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
			counter++;
		ImGui::SameLine();
		ImGui::Text("counter = %d", counter);

		ImGui::End();
	}


}

void EditorWinDefualt::Draw()
{	

	ImGui::Render();

	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	// Present
	HRESULT hr = g_pSwapChain->Present(1, 0);   // Present with vsync
	//HRESULT hr = g_pSwapChain->Present(0, 0); // Present without vsync
	g_SwapChainOccluded = (hr == DXGI_STATUS_OCCLUDED);
}
