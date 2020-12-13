// 学学学

#include "SceneObjectAsset.h"
#include "../pugi/pugixml.hpp"

namespace Resources
{
	bool SceneObjectAsset::Load()
	{
		pugi::xml_document doc;

		pugi::xml_parse_result result = doc.load_file("../../base/objects/cube_test.xml");

		if (result == pugi::xml_parse_status::status_ok)
		{
			return true;
		}

		return false;
	}

	bool SceneObjectAsset::Save()
	{
		return false;
	}
}