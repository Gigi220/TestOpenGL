// 学学学
#pragma once

#include "../Core/Singleton.h"

namespace Resources
{
	class ResourceLoader : public Singleton<ResourceLoader>
	{
	public:
		ResourceLoader() = default;
		~ResourceLoader() = default;

		void Load();

	private:

	};
}
