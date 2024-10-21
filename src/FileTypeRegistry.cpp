#include "FileTypeRegistry.h"

FileTypeRegistry::FileTypeRegistry()
	: _supportedFileExtensions({
		".png",
		".jpg",
		".jpeg",
	}) {
}

bool FileTypeRegistry::IsSupported(const std::string& extension) const {
	return _supportedFileExtensions.contains(extension);
}
