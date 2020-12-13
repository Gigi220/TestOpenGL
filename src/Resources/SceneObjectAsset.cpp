// 学学学

#include "SceneObjectAsset.h"

namespace Resources
{
	bool SceneObjectAsset::Load()
	{
		System::Xml::XmlTextReader reader("");

		while (reader.Read())
		{
			switch (reader.NodeType)
			{
				case System::Xml::XmlNodeType::Element:
					if (reader.Name == "asset")
					{
						while (reader.MoveToNextAttribute())
						{
							if (reader.Name == "id")
							{
								std::string f = reader.Value;
								SetAssetId(f);
							}
						}
					}
					break;
				case System::Xml::XmlNodeType::Text: //Display the text in each element.
					break;
				case System::Xml::XmlNodeType::EndElement: //Display the end of the element.
					break;
			}
		}

		return false;
	}

	bool SceneObjectAsset::Save()
	{
		return false;
	}
}