// 学学学
#pragma once

#include "Asset.h"

namespace Resources
{
	class SceneObjectAsset : public Asset
	{
	public:

		virtual bool Load();
		virtual bool Save();

	private:

	};
}