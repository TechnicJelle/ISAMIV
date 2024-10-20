#pragma once

#include "olcPixelGameEngine.h"

class ISAMIV_ImageLoader {
public:
	virtual ~ISAMIV_ImageLoader() = default;

	[[nodiscard]] virtual olc::Renderable LoadImage(const std::filesystem::path& filepath) const = 0;
};
