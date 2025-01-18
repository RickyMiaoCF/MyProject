#pragma once
#include "main.h"
#include "renderer.h"
#include "editorDefault.h"
#include "editorWinObj.h"
#include <list>
#include "editorDataStruct.h"
#include "editorWinLight.h"

static HWND g_Window = nullptr;
static ID3D11Device* g_pd3dDevice = nullptr;
static ID3D11DeviceContext* g_pd3dDeviceContext = nullptr; 
static ID3D11RenderTargetView* g_mainRenderTargetView = nullptr;
static IDXGISwapChain* g_pSwapChain = nullptr;
static bool g_SwapChainOccluded = false;

enum EditorWindowType
{
	EW_COMPONENT,
	EW_OBJECT,
	EW_COUNT
};

class EditorsManager
{
private:

	static EditorsManager* m_Instance;
	
	EditorsManager() {};

	std::list<EditorWindow*> m_EditorList;

public:

	static EditorsManager* GetEditorsManagerInstance()
	{
		if (!m_Instance) 
			m_Instance = new EditorsManager;
		return m_Instance;
	};

	EditorsManager(const EditorsManager&) = delete;
	EditorsManager& operator=(const EditorsManager&) = delete;


	template <typename T> //テンプレート関数
	T* AddEditorWindow()
	{
		T* window = new T();
		window->Init();
		m_EditorList.push_back(window);
		return window;
	}


	template <typename T> //テンプレート関数
	T* GetEditorWindow()
	{
		for (EditorWindow* window : m_EditorList)
		{
			T* ret = dynamic_cast<T*>(window);
			if (ret != nullptr)
				return ret;
		}
		return nullptr;
	}

	std::list<EditorWindow*> GetWindowList()
	{
		return m_EditorList;
	}

	//virtual void Uninit()
	//{

	//	for (EditorWindow* window : m_EditorList)
	//	{
	//		window->Uninit();//ポリモフィズム・多態性
	//		delete window;
	//	}
	//	m_EditorList.clear();
	//};


	virtual void Init()
	{
		//リソースセット
		g_Window = GetWindow();
		g_pd3dDevice = Renderer::GetDevice();
		g_pd3dDeviceContext = Renderer::GetDeviceContext();
		g_mainRenderTargetView = Renderer::GetRenderTargetView();
		g_pSwapChain = Renderer::GetSwapChain();



		::ShowWindow(g_Window, SW_SHOWDEFAULT);
		::UpdateWindow(g_Window);

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		//ImGui::StyleColorsLight();

		 // Setup Platform/Renderer backends
		ImGui_ImplWin32_Init(g_Window);
		ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);
	}

	virtual void Update()
	{
		// Start the Dear ImGui frame
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		for (EditorWindow* window : m_EditorList) //範囲Forループ
		{
			window->Update();//ポリモフィズム
		}

	};

	virtual void Draw()
	{

		ImGui::Render();

		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

		// Present
		HRESULT hr = g_pSwapChain->Present(1, 0);   // Present with vsync
		//HRESULT hr = g_pSwapChain->Present(0, 0); // Present without vsync
		g_SwapChainOccluded = (hr == DXGI_STATUS_OCCLUDED);

	};

	void SetConnection(EditorWindowType type,Component* data)
	{
		switch (type)
		{
		case EW_COMPONENT:
			GetEditorWindow<EditorWinDefualt>()->SetTarget(data);
			break;
		case EW_OBJECT:
			break;
		case EW_COUNT:
			break;
		default:
			break;
		}
	}

	void SetConnection(EditorWindowType type, GameObject* data)
	{
		switch (type)
		{
		case EW_COMPONENT:
			
			break;
		case EW_OBJECT:
			GetEditorWindow<EditorWinObj>()->SetTarget(data);
			break;
		case EW_COUNT:
			break;
		default:
			break;
		}
	}

};


EditorsManager* EditorsManager::m_Instance = nullptr;