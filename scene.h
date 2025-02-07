#pragma once
#include <list>
#include <vector>
#include "gameObject.h"
#include "camera.h"
#include "player.h"
//#include "polygon2D.h"
#include "sky.h"
#include "manager.h"

#define CAMERA 0
#define WORLD 1
#define UI 2


class Scene
{
protected:
	std::list<GameObject*> m_GameObject[3];

public:
	virtual ~Scene() {}; //デストラクタ

	virtual void Init()//仮想関数
	{
	}

	template <typename T> //テンプレート関数
	T* AddGameObject(int Layer)
	{
		T* GameObject = new T(this);
		GameObject->Init();
		m_GameObject[Layer].push_back(GameObject);
		return GameObject;
	}

	template <typename T> //テンプレート関数
	T* GetGameObject()
	{
		for (int i = 0; i < 3; i++)
		{
			for (GameObject* object : m_GameObject[i])
			{
				T* ret = dynamic_cast<T*>(object);
				if (ret != nullptr)
					return ret;
			}
		}
		return nullptr;
	}

	template <typename T> 
	std::vector<T*> GetGameObjectList()
	{
		std::vector<T*> objectList;

		for (int i = 0; i < 3; i++)
		{
			for (GameObject* object : m_GameObject[i])
			{
				T* ret = dynamic_cast<T*>(object);
				if (ret != nullptr)
					objectList.push_back(ret);
			}
		}
		return objectList;
	}

	virtual void Uninit() 
	{
		for (int i = 0; i < 3; i++)
		{
			for (GameObject* object : m_GameObject[i])
			{
				object->Uninit();//ポリモフィズム・多態性
				delete object;
			}
			m_GameObject[i].clear();
		}
	};

	virtual void Update() 
	{
		for (int i = 0; i < 3; i++)
		{
			for (GameObject* object : m_GameObject[i]) //範囲Forループ
			{
				object->Update();//ポリモフィズム
			}
			m_GameObject[i].remove_if([](GameObject* object) {return object->Destroy(); }//条件チェック
			);
		}
	};

	virtual void Draw() 
	{
		for (int i = 0; i < 3; i++)
		{
			for (GameObject* object : m_GameObject[i])
			{
				object->Draw();//ポリモフィズム・多態性
			}
		}
	};
};
