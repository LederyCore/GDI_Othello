#include "pch.h"
#include "GameObject.h"
#include "Transform.h"

GameObject::GameObject()
{
	using namespace OthelloComponent;
	AddComponent<Transform>();
}

GameObject::~GameObject()
{
	m_isActive = false;
	m_isStarted = false;

	for (auto it = m_components.begin(); it != m_components.end(); ++it)
	{
		delete* it;
		*it = nullptr;
	}
}

void GameObject::FixedUpdate(float fixedTime)
{
	if (!m_isActive) return;
	for (const auto& c : m_components)
	{
		c->FixedUpdate(fixedTime);
	}
}

void GameObject::Update(float deltaTime)
{
	if (!m_isActive) return;

	if (!m_isStarted)
	{
		for (const auto& c : m_components)
		{
			c->Start();
		}
		m_isStarted = true;
	}

	for (const auto& c : m_components)
	{
		c->Update(deltaTime);
	}
}

void GameObject::LateUpdate(float deltaTime)
{
	if (!m_isActive) return;
	for (const auto& c : m_components)
	{
		c->LateUpdate(deltaTime);
	}
}

void GameObject::Render(HDC hdc)
{
	for (const auto& c : m_components)
	{
		c->Render(hdc);
	}
}

void GameObject::SetActive(bool active)
{
	if (m_isActive == active) return;
	m_isActive = active;

	for (const auto& c : m_components)
	{
		if (active && c->GetActive())			// 게임오브젝트가 활성화로 바뀌고, 컴포넌트도 활성화 상태일때
		{
			c->OnEnable();						// 컴포넌트의 Enable 호출
		}
		else if (!active && c->GetActive())		// 게임오브젝트가 비활성화로 바뀌고, 컴포넌트가 활성화 상태이면
		{
			c->OnDisable();						// 컴포넌트의 Disable 호출
		}
		else if (!c->GetActive())
		{
			return;								// 게임오브젝트의 활성화 여부에 관계없이 컴포넌트가 원래
												// 비활성화 상태였으면 아무것도 안하고 리턴
		}
	}
}