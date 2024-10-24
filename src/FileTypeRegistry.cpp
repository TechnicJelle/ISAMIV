#include "FileTypeRegistry.h"

FileTypeRegistry::FileTypeRegistry() {
	_fileTypeRegistry.emplace(".png", &_stb_loader);
	_fileTypeRegistry.emplace(".jpg", &_stb_loader);
	_fileTypeRegistry.emplace(".jpeg", &_stb_loader);
	_fileTypeRegistry.emplace(".qoi", &_qoi_loader);
}

bool FileTypeRegistry::IsSupported(const std::string& extension) const {
	return _fileTypeRegistry.contains(extension);
}

ISAMIV_ImageLoader* FileTypeRegistry::GetLoader(const std::string& extension) {
	return _fileTypeRegistry[extension];
}
