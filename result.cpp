#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "result.h"
#include "input.h"
#include "title.h"
#include "Polygon2DR.h"



void Result::Init()
{
	AddGameObject<Polygon2DR>(UI);
}

void Result::Update()
{
	//継承元のUpdate呼び出し
	Scene::Update();

	if (Input::GetKeyTrigger(VK_RETURN))
	{
		Manager::SetScene<Title>();
	}
}