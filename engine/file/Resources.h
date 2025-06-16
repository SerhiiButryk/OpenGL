#pragma once

#include <filesystem>

namespace xengine::file {

	static inline const std::string assetsFolder = "/res";
	static inline const std::string fontsFolder = "/fonts";
	static inline const std::string shaderFolder = "/shader";
	static inline const std::string textureFolder = "/textures";

	// TODO This could change
	static inline const std::string assetsPath = "../engine" + assetsFolder;

	static inline const std::string fontsPath = assetsPath + fontsFolder;
	static inline const std::string shaderPath = assetsPath + shaderFolder;
	static inline const std::string texturePath = assetsPath + textureFolder;

	inline std::string getPlatformPath(const std::string& path) {
    	std::filesystem::path myPath = path;
    	return myPath.string();
	}

	inline std::string getCurrentPath() {
    	std::filesystem::path currentPath = std::filesystem::current_path();
    	return currentPath.string();
	}

	inline std::string buildShaderPath(const std::string& assetsPath, const std::string& name) {
		return getPlatformPath(assetsPath + shaderFolder + "/" + name);
	}

	inline std::string buildTexturePath(const std::string& assetsPath, const std::string& name) {
		return getPlatformPath(assetsPath + textureFolder + "/" + name);
	}

}

