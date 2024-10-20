#pragma once

#include <filesystem>
#include "olcPixelGameEngine.h"
#include "loaders/stb/stb_loader.h"
#include "UpdateListener.h"

class OpenImage {
	const std::filesystem::path _filepath;
	olc::Renderable _renderable;
	const ISAMIV_StbLoader _loader;
	UpdateListener _listener;

	std::atomic<bool> _shouldReload = false;

public:
	explicit OpenImage(std::filesystem::path filepath);

	void LoadImage();

	void SetupFileWatcher(efsw::FileWatcher& fileWatcher);

	void MarkForReload();

	[[nodiscard]] const olc::Renderable& GetRenderable();

	[[nodiscard]] const std::filesystem::path& GetFilepath() const;
};
