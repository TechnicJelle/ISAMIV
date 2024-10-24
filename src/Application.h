#pragma once

#include <efsw/efsw.hpp>

#include "olcPixelGameEngine.h"
#include "olcPGEX_TransformedView.h"
#include "OpenDirectory.h"
#include "FileTypeRegistry.h"
#include "FileWatcherEventHandler.h"

class ISAMIV_Application final : public olc::PixelGameEngine {
	FileTypeRegistry _fileTypeRegistry;

	olc::TransformedView _transformedView;

	OpenDirectory _openDirectory;

	efsw::FileWatcher _fileWatcher;
	FileWatcherEventHandler _fileWatcherEventHandler;

	float _timeSinceScrollStart = 0.0f;
	float _timeSinceLastGoTo = -0.5f;

public:
	explicit ISAMIV_Application(std::filesystem::path filepath);

private:
	void HandleImagePrevNext(float fElapsedTime);

public:
	bool OnUserCreate() override;

	bool OnUserUpdate(float fElapsedTime) override;

	bool OnUserDestroy() override;

public:
	void DrawCenteredString(const olc::vf2d& pos, const std::string& text, const olc::Pixel& colour = olc::WHITE, int scale = 1);

	void DrawCenteredDecal(const olc::vf2d& pos, olc::Decal* decal);

public:
	FileTypeRegistry& GetFileTypeRegistry();
};
