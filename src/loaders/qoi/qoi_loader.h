#pragma once

#include "../../interfaces/loader.h"

class ISAMIV_QoiLoader final : public ISAMIV_ImageLoader {
public:
	[[nodiscard]] olc::Renderable LoadImage(const std::filesystem::path& filepath) const override;
};
