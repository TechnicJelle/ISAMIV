#pragma once

#include <filesystem>
#include "olcPixelGameEngine.h"
#include "interfaces/loader.h"

class OpenImage {
	std::filesystem::path _filepath;
	olc::Renderable _renderable;

public:
	explicit OpenImage(std::filesystem::path filepath);

	void LoadImage(const ISAMIV_ImageLoader& loader);

	[[nodiscard]] const olc::Renderable& GetRenderable() const { return _renderable; }

	[[nodiscard]] const std::filesystem::path& GetFilepath() const { return _filepath; }
};
