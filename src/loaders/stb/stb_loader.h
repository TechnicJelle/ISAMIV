#pragma once

#include "../../interfaces/loader.h"

class ISAMIV_StbLoader final : public ISAMIV_ImageLoader {
public:
	[[nodiscard]] olc::Renderable LoadImage(const std::filesystem::path& filepath) const override;
};
