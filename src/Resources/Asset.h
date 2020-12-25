// 学学学
#pragma once

#ifndef _ASSET_H_
#define _ASSET_H_

#include <string>

namespace Resources
{
	enum class AssetType
	{
		None = 0,
		SceneObject,
		Texture
	};

	class Asset
	{
	public:
		Asset() = default;
		virtual ~Asset() = default;

		virtual bool Load(const std::string& path);
		virtual bool Save();

		void SetAssetId(const std::string& id) { _id = id; }
		void SetAssetPath(const std::string& path) { _path = path; }

		const std::string& GetAssetId() const { return _id; }
		const std::string& GetAssetPath() const { return _path; }

	protected:
		std::string _id;
		std::string _path;
	};
}

#endif // !_ASSET_H_
