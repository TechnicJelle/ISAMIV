#pragma once

#include "../../interfaces/loader.h"

class ISAMIV_StbLoader : public ISAMIV_ImageLoader {
public:
	olc::Renderable LoadImage(const std::filesystem::path& filepath) override;
};
