#include "OpenImage.h"

OpenImage::OpenImage(std::filesystem::path filepath) : _filepath(filepath) {}

void OpenImage::LoadImage() {
	//start timing
	auto start = std::chrono::high_resolution_clock::now();

	_renderable = _loader.LoadImage(_filepath);

	//end timing
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	printf("Image load time: %ld microseconds\n", duration.count());
}

void OpenImage::MarkForReload() {
	_shouldReload = true;
}
