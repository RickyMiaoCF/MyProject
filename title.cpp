#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "title.h"
#include "input.h"
#include "manager.h"
#include "game.h"
#include "polygon2D.h"

void Title::Init()
{
	AddGameObject<Polygon2D>(UI);
}


void Title::Update()
{
	//継承元のUpdate呼び出し
	Scene::Update();

	if (Input::GetKeyTrigger(VK_RETURN))
	{

		Manager::SetScene<Game>();

	}
}