// 学学学

#include "Asset.h"

namespace Resources
{
	bool Asset::Load(const std::string& path)
	{
		SetAssetPath(path);
		return false;
	}

	bool Asset::Save()
	{
		return false;
	}
}