#pragma once


#include "olcPixelGameEngine.h"
#include "UpdateListener.h"
#include "loaders/stb/stb_loader.h"
#include "olcPGEX_TransformedView.h"

class ISAMIV_Application : public olc::PixelGameEngine {

private:
	std::string filepath;
	olc::Renderable img;
	olc::TransformedView transformedView;
	ISAMIV_StbLoader loader;

	std::atomic<bool> shouldReload = false;

	efsw::FileWatcher fileWatcher = efsw::FileWatcher();
	UpdateListener* listener = nullptr;

public:
	explicit ISAMIV_Application(std::string filepath) : filepath(std::move(filepath)) {
		sAppName = "ISAMIV";
	}

private:
	void ReloadImage();
	void SetupFileWatcher();

public:
	void MarkForReload();
	bool OnUserCreate() override;
	bool OnUserUpdate(float fElapsedTime) override;
	bool OnUserDestroy() override;

public:
	void DrawCenteredString(olc::vf2d pos, const std::string& text, const olc::Pixel& colour = olc::WHITE, int scale = 1) {
		olc::vi2d size = GetTextSize(text) * scale;
		DrawString(pos - size / 2, text, colour, scale);
	}

	void DrawCenteredDecal(olc::vf2d pos, olc::Decal* decal) {
		olc::vi2d size = {decal->sprite->width, decal->sprite->height};
		DrawDecal(pos - size / 2, decal);
	}
};
