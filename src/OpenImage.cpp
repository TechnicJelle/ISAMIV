#include "OpenImage.h"

#include <utility>

OpenImage::OpenImage(std::filesystem::path filepath)
	: _filepath(std::move(filepath)), _listener(this) {
	printf("OpenImage constructor %s\n", _filepath.c_str());
}

OpenImage::~OpenImage() {
	printf("OpenImage destructor %s\n", _filepath.c_str());
}

void OpenImage::LoadImage() {
	//start timing
	const auto start = std::chrono::high_resolution_clock::now();

	_renderable = _loader.LoadImage(_filepath);

	//end timing
	const auto end = std::chrono::high_resolution_clock::now();
	const auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	printf("Image load time: %ld microseconds\n", duration.count());
}

void OpenImage::SetupFileWatcher(efsw::FileWatcher& fileWatcher) {
	const std::filesystem::path parentDir = _filepath.parent_path();
	printf("Watching folder for changes: %s\n", parentDir.c_str());

	if (const efsw::WatchID watchID = fileWatcher.addWatch(parentDir.string(), &_listener, false);
		watchID < 0) {
		printf("Error adding watch! Watch ID: %ld\n", watchID);
	}
}

void OpenImage::MarkForReload() {
	_shouldReload = true;
}

const olc::Renderable& OpenImage::GetRenderable() {
	if (_shouldReload) {
		LoadImage();
		_shouldReload = false;
	}
	return _renderable;
}

const std::filesystem::path& OpenImage::GetFilepath() const {
	return _filepath;
}
