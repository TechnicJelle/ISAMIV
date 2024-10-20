#pragma once

#include <string>
#include "olcPixelGameEngine.h"

class ISAMIV_ImageLoader {
	virtual olc::Renderable LoadImage(const std::filesystem::path& filepath) = 0;
};
