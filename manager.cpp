#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "modelRenderer.h"
#include "audio.h"
#include "gameObject.h"
#include "input.h"
#include "scene.h"
#include "game.h"
#include "result.h"
#include "title.h"


Scene* Manager::m_Scene{};
Scene* Manager::m_NextScene{};

void Manager::Init()
{
	Renderer::Init();
	Input::Init();
	Audio::InitMaster();
	m_Scene = new Game();
	/*m_Scene = Game::GetGameScene();*/
	m_Scene->Init();
	//SetScene<Title>();
}


void Manager::Uninit()
{
	m_Scene->Uninit();
	delete m_Scene;
	ModelRenderer::UnloadAll();

	Audio::UninitMaster();
	Renderer::Uninit();
	Input::Uninit();

}

void Manager::Update()
{
	Input::Update();

	m_Scene->Update();


}

void Manager::Draw()
{
	Renderer::Begin();
	m_Scene->Draw();
	Renderer::End();

	//画面遷移
	if (m_NextScene != nullptr)
	{
		if (m_Scene)
		{
			m_Scene->Uninit();
			delete m_Scene;
		}

		ModelRenderer::UnloadAll();

		m_Scene = m_NextScene;
		m_Scene->Init();
		
		m_NextScene = nullptr;
	}
}
