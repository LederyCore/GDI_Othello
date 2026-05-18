#pragma once
#include "Component.h"
#include "../utils/Vector2f.h"

struct Vector2f;

namespace OthelloComponent
{
	class Transform : public Component
	{
	public :
		Transform();
		virtual ~Transform() override;

	private :
		Vector2f m_localPosition;
	};
}