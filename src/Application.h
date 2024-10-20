#pragma once

#include <utility>

#include "olcPixelGameEngine.h"
#include "UpdateListener.h"
#include "olcPGEX_TransformedView.h"
#include "OpenImage.h"

class ISAMIV_Application final : public olc::PixelGameEngine {
	olc::TransformedView transformedView;
	OpenImage image;

	efsw::FileWatcher fileWatcher = efsw::FileWatcher();

public:
	explicit ISAMIV_Application(std::filesystem::path filepath) : image(std::move(filepath)) {
		sAppName = "ISAMIV";
	}

public:
	bool OnUserCreate() override;

	bool OnUserUpdate(float fElapsedTime) override;

	bool OnUserDestroy() override;

public:
	void DrawCenteredString(const olc::vf2d pos, const std::string& text, const olc::Pixel& colour = olc::WHITE, const int scale = 1) {
		const olc::vi2d size = GetTextSize(text) * scale;
		DrawString(pos - size / 2, text, colour, scale);
	}

	void DrawCenteredDecal(const olc::vf2d pos, olc::Decal* decal) {
		const olc::vi2d size = {decal->sprite->width, decal->sprite->height};
		DrawDecal(pos - size / 2, decal);
	}
};
