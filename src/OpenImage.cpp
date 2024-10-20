#include "OpenImage.h"

OpenImage::OpenImage(std::filesystem::path filepath) : _filepath(filepath) {}

void OpenImage::LoadImage(const ISAMIV_ImageLoader& loader) {
	//start timing
	auto start = std::chrono::high_resolution_clock::now();

	_renderable = loader.LoadImage(_filepath);

	//end timing
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	printf("Image load time: %ld microseconds\n", duration.count());
}
