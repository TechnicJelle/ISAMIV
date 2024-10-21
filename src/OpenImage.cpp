#include "OpenImage.h"

#include <utility>

void OpenImage::InitFilePath(const std::filesystem::path& initialFilepath) {
	_filepath = initialFilepath;
}

void OpenImage::LoadImage(const std::filesystem::path& filepath) {
	_filepath = filepath;

	//start timing
	const auto start = std::chrono::high_resolution_clock::now();

	_renderable = _loader.LoadImage(_filepath);

	//end timing
	const auto end = std::chrono::high_resolution_clock::now();
	const auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	printf("Image load time: %ld microseconds\n", duration.count());
}

void OpenImage::MarkForReload() {
	_shouldReload = true;
}

const olc::Renderable& OpenImage::GetRenderable() {
	if (_shouldReload) {
		LoadImage(_filepath);
		_shouldReload = false;
	}
	return _renderable;
}

const std::filesystem::path& OpenImage::GetFilepath() const {
	return _filepath;
}
