#pragma once

#include <filesystem>
#include "olcPixelGameEngine.h"
#include "loaders/stb/stb_loader.h"

class OpenImage {
	std::filesystem::path _filepath;
	olc::Renderable _renderable;
	ISAMIV_StbLoader _loader;

	std::atomic<bool> _shouldReload = true; //load on first access

public:
	void InitFilePath(const std::filesystem::path& initialFilepath);

	void LoadImage(const std::filesystem::path& filepath);

	void MarkForReload();

	[[nodiscard]] const olc::Renderable& GetRenderable();

	[[nodiscard]] const std::filesystem::path& GetFilepath() const;
};
