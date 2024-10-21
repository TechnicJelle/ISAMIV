#pragma once

#include "olcPixelGameEngine.h"
#include "olcPGEX_TransformedView.h"
#include "OpenDirectory.h"
#include "FileTypeRegistry.h"

class ISAMIV_Application final : public olc::PixelGameEngine {
	FileTypeRegistry _fileTypeRegistry;

	olc::TransformedView _transformedView;

	OpenDirectory _openDirectory;

public:
	explicit ISAMIV_Application(std::filesystem::path filepath);

public:
	bool OnUserCreate() override;

	bool OnUserUpdate(float fElapsedTime) override;

	bool OnUserDestroy() override;

public:
	void DrawCenteredString(const olc::vf2d& pos, const std::string& text, const olc::Pixel& colour = olc::WHITE, int scale = 1);

	void DrawCenteredDecal(const olc::vf2d& pos, olc::Decal* decal);

public:
	const FileTypeRegistry& GetFileTypeRegistry() const;
};
