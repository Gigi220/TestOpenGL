// 学学学
#pragma once

#include "Asset.h"

namespace Resources
{
	class SceneObjectAsset : public Asset
	{
	public:
		SceneObjectAsset() = default;

		bool Load(const std::string& path) override;
		bool Save() override;

	private:

	};
}