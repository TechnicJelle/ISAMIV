#include "OpenDirectory.h"

#include "Application.h"

OpenDirectory::OpenDirectory(const ISAMIV_Application* application, std::filesystem::path openPath) {
	using namespace std::filesystem;
	if (is_directory(openPath)) {
		_directoryPath = std::move(openPath);
	} else {
		const path parentPath = openPath.parent_path();
		_directoryPath = parentPath;
	}

	//TODO: Do this upon FileWatcher as well
	for (const directory_entry& entry : directory_iterator(_directoryPath)) {
		if (entry.is_regular_file()) {
			if (const std::string extension = entry.path().extension().string();
				application->GetFileTypeRegistry().IsSupported(extension)) {
				_files.push_back(entry.path());
				if (entry == openPath) {
					_currentFileIndex = _files.size() - 1;
					_currentOpenImage.InitFilePath(entry);
				}
			}
		}
	}
}

void OpenDirectory::GoToRelativeFile(const int relativeIndex) {
	_currentFileIndex = (_currentFileIndex + relativeIndex + _files.size()) % _files.size();
	_currentOpenImage.LoadImage(_files[_currentFileIndex]);
}

const std::filesystem::path& OpenDirectory::GetDirectoryPath() const {
	return _directoryPath;
}

void OpenDirectory::NextFile() {
	GoToRelativeFile(+1);
}

void OpenDirectory::PreviousFile() {
	GoToRelativeFile(-1);
}

OpenImage& OpenDirectory::GetCurrentOpenImage() {
	return _currentOpenImage;
}
