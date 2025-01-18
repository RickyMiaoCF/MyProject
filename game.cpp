#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "editorsManager.h"
#include "game.h"
#include "input.h"
#include "result.h"
#include "title.h"
#include "enemy.h"
#include "particleEmitter.h"
#include "score.h"
#include "fire.h"
#include "snow.h"
#include "time.h"
#include "tree.h"
#include "wave.h"
#include "MeshField.h"
#include "visualBox.h"
#include "Sun.h"
#include"Polygon2DR.h"


EditorsManager* g_EditorsManager = nullptr;


void Game::Init()
{
	AddGameObject<Camera>(CAMERA);

	//AddGameObject<MeshField>(WORLD);

	AddGameObject<Sky>(WORLD)->SetScale(XMFLOAT3(100.0f, 100.0f, 100.0f));
	
	AddGameObject<Wave>(WORLD)->SetPosition(XMFLOAT3(0.0f, 0.0f, 0.0f));

	AddGameObject<Player>(WORLD);
	//->SetScale(XMFLOAT3(1.0f, 1.0f, 1.0f));
	AddGameObject<Polygon2DR>(UI);

	//for (GameObject* tree:GetGameObjectList<Tree>())
	//{
	//	XMFLOAT3 newPos;
	//	newPos.x = tree->GetPosition().x;
	//	newPos.z = tree->GetPosition().z;
	//	newPos.y = GetGameObject<MeshField>()->getHeight(tree->GetPosition());
	//	tree->SetPosition(newPos);
	//}

	//for (GameObject* enemy : GetGameObjectList<Enemy>())
	//{
	//	XMFLOAT3 newPos;
	//	newPos.x = enemy->GetPosition().x;
	//	newPos.z = enemy->GetPosition().z;
	//	newPos.y = GetGameObject<MeshField>()->getHeight(enemy->GetPosition())+1.0f;
	//	enemy->SetPosition(newPos);
	//}

		//AddGameObject<Box>(WORLD)->SetPosition(XMFLOAT3(10.0f, 0.0f, 1.0f));

	//AddGameObject<Score>(UI);
	//AddGameObject<Time>(UI);

	//必ず最後
	//g_EditorsManager = EditorsManager::GetEditorsManagerInstance();

	//g_EditorsManager->Init();

	//g_EditorsManager->AddEditorWindow<EditorWinDefualt>();

	//g_EditorsManager->AddEditorWindow<EditorWinObj>();

	//g_EditorsManager->AddEditorWindow<EditorWinLight>();

	/*g_EditorsManager->SetConnection(EW_COMPONENT, GetGameObject<Player>()->GetComponentsManager()->GetComponent<VisualBox>());*/

	/*g_EditorsManager->SetConnection(EW_OBJECT, GetGameObject<Sky>());*/


}


void Game::Update()
{
	Sun::GetInstance().Update();

	Renderer::UpdateGlobalLight();
	//継承元のUpdate呼び出し
	Scene::Update();
	/*g_EditorsManager->Update();*/


	//if (Input::GetKeyTrigger(VK_RETURN))
	//{
	//	Manager::SetScene<Title>();
	//}

	//auto enemyList = GetGameObjectList<Enemy>();
	//if (enemyList.size() == 0)
	//{

	//	Manager::SetScene<Result>();

	//}
}

void Game::Draw()
{
	Scene::Draw();
	/*g_EditorsManager->Draw();*/
}

