#pragma once

#include <string>
#include "olcPixelGameEngine.h"

class ISAMIV_ImageLoader {
public:
	[[nodiscard]] virtual olc::Renderable LoadImage(const std::filesystem::path& filepath) const = 0;
};
