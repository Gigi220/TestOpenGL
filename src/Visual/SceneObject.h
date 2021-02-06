// 学学学
#pragma once

#include "Transform.h"
#include "../Resources/SceneObjectAsset.h"

namespace Visual
{
	class SceneObject : public Resources::SceneObjectAsset
	{
	public:
		//SceneObject() = default;
		explicit SceneObject(const Transform& transform) : SceneObjectAsset(), _transform(transform) { }

		Transform& GetTransform() { return _transform; }

	private:
		Transform _transform;
	};
}
