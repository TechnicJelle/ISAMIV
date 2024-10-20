#pragma once

#include <filesystem>
#include "olcPixelGameEngine.h"
#include "loaders/stb/stb_loader.h"
#include "UpdateListener.h"

class OpenImage {
	std::filesystem::path _filepath;
	olc::Renderable _renderable;
	ISAMIV_StbLoader _loader;
	UpdateListener* _listener = nullptr;

	std::atomic<bool> _shouldReload = false;

public:
	explicit OpenImage(std::filesystem::path filepath);
	~OpenImage();

	void LoadImage();

	void SetupFileWatcher(efsw::FileWatcher& fileWatcher);

	void MarkForReload();

	[[nodiscard]] const olc::Renderable& GetRenderable() {
		if (_shouldReload) {
			LoadImage();
			_shouldReload = false;
		}
		return _renderable;
	}

	[[nodiscard]] const std::filesystem::path& GetFilepath() const { return _filepath; }
};
