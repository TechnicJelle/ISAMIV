#pragma once

#include <filesystem>
#include "olcPixelGameEngine.h"

class ISAMIV_Application;

class OpenImage {
	ISAMIV_Application* _application = nullptr;

	std::filesystem::path _filepath;
	olc::Renderable _renderable;

	std::atomic<bool> _shouldReload = true; //load on first access

public:
	explicit OpenImage(ISAMIV_Application* application);

public:
	void InitFilePath(const std::filesystem::path& initialFilepath);

	void LoadImage(const std::filesystem::path& filepath);

	void MarkForReload();

	[[nodiscard]] const olc::Renderable& GetRenderable();

	[[nodiscard]] const std::filesystem::path& GetFilepath() const;
};
