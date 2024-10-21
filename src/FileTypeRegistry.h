#pragma once

#include <unordered_set>
#include <string>
// #include <unordered_map>
// #include <concepts>

// #include "Application.h"
// #include "interfaces/loader.h"
// #include "loaders/stb/stb_loader.h"

// template<typename T>
// concept IsAnImageLoader = requires(T a)
// {
// 	requires std::derived_from<T, ISAMIV_ImageLoader>;
// };

class FileTypeRegistry {
	//TODO: all this...

	// template<IsAnImageLoader T>
	// std::unordered_map<std::string, T> _fileTypeRegistry{
	// 	".png", ISAMIV_StbLoader(),
	// 	".jpg", ISAMIV_StbLoader(),
	// 	".jpeg", ISAMIV_StbLoader(),
	// 	".jpeg", olc::PixelGameEngine(), //this should not be possible
	// };

	std::unordered_set<std::string> _supportedFileExtensions;

public:
	FileTypeRegistry();

public:
	[[nodiscard]] bool IsSupported(const std::string& extension) const;

	// [[nodiscard]] ISAMIV_ImageLoader& GetLoader(const std::string& extension);
};
