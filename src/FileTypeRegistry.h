#pragma once

#include <string>
#include <unordered_map>

#include "loaders/stb/stb_loader.h"
#include "loaders/qoi/qoi_loader.h"

class FileTypeRegistry {
private:
	ISAMIV_StbLoader _stb_loader;
	ISAMIV_QoiLoader _qoi_loader;

	std::unordered_map<std::string, ISAMIV_ImageLoader*> _fileTypeRegistry;

public:
	FileTypeRegistry();

public:
	[[nodiscard]] bool IsSupported(const std::string& extension) const;

	[[nodiscard]] ISAMIV_ImageLoader* GetLoader(const std::string& extension);
};
