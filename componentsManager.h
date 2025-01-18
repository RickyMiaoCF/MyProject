#pragma once
#include <list>
#include"component.h"
class ComponentsManager
{
private:
	GameObject* m_ParentObject;
	std::list<Component*> m_ComponentList;


public:
	ComponentsManager(GameObject* parentObj) { m_ParentObject = parentObj; };
	~ComponentsManager() {};

	GameObject* GetParentObj() { return m_ParentObject; };

	template <typename T> //テンプレート関数
	T* AddComponent()
	{
		T* Component = new T(this);
		Component->Init();
		m_ComponentList.push_back(Component);
		return Component;
	}

	template <typename T> //テンプレート関数
	T* GetComponent()
	{
		for (Component* component : m_ComponentList)
		{
			T* ret = dynamic_cast<T*>(component);
			if (ret != nullptr)
				return ret;
		}
		return nullptr;
	}

	std::list<Component*> GetComponentList()
	{
		return m_ComponentList;
	}

	virtual void Uninit()
	{

		for (Component* component : m_ComponentList)
		{
			component->Uninit();//ポリモフィズム・多態性
			delete component;
		}
		m_ComponentList.clear();
	};

	virtual void Update()
	{

		for (Component* component : m_ComponentList) //範囲Forループ
		{
			component->Update();//ポリモフィズム
		}
		m_ComponentList.remove_if([](Component* compo) {return compo->Destroy(); }//条件チェック
		);

	};

	virtual void Draw()
	{

		for (Component* component : m_ComponentList)
		{
			component->Draw();//ポリモフィズム・多態性
		}

	};
};