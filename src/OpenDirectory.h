#pragma once

#include <vector>
#include <filesystem>

#include "OpenImage.h"

class ISAMIV_Application;

class OpenDirectory {
	std::filesystem::path _directoryPath;
	std::vector<std::filesystem::path> _files;

	size_t _currentFileIndex = 0;
	OpenImage _currentOpenImage;

public:
	OpenDirectory(const ISAMIV_Application* application, std::filesystem::path openPath);

private:
	void GoToRelativeFile(int relativeIndex);

public:
	[[nodiscard]] const std::filesystem::path& GetDirectoryPath() const;

	void NextFile();

	void PreviousFile();

	[[nodiscard]] OpenImage& GetCurrentOpenImage();
};
