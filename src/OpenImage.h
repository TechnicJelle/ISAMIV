#pragma once

#include <filesystem>
#include "olcPixelGameEngine.h"
#include "loaders/stb/stb_loader.h"
#include "UpdateListener.h"

class OpenImage {
	std::filesystem::path _filepath;
	olc::Renderable _renderable;
	ISAMIV_StbLoader _loader;
	UpdateListener _listener;

	std::atomic<bool> _shouldReload = false;

public:
	explicit OpenImage(std::filesystem::path filepath);

	~OpenImage();

	//move assignment operator
	OpenImage& operator=(OpenImage&& other) noexcept {
		if (this != &other) {
			_filepath = std::move(other._filepath);
			_renderable = std::move(other._renderable);
			_loader = std::move(other._loader);
			_listener = std::move(other._listener);
			_shouldReload = other._shouldReload.load();
		}
		return *this;
	}

	void LoadImage();

	void SetupFileWatcher(efsw::FileWatcher& fileWatcher);

	void MarkForReload();

	[[nodiscard]] const olc::Renderable& GetRenderable();

	[[nodiscard]] const std::filesystem::path& GetFilepath() const;
};
