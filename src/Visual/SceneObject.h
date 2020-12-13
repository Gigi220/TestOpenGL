// 学学学
#pragma once

#include "Transform.h"
#include "../Resources/Asset.h"

namespace Visual
{
	class SceneObject : public Resources::Asset
	{
	public:
		SceneObject() = default;
		explicit SceneObject(const Transform& transform) : _transform(transform) { }

		Transform& GetTransform() { return _transform; }

	private:
		Transform _transform;
	};
}
