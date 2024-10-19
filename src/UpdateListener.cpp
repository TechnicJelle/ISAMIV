#include <filesystem>

#include "UpdateListener.h"
#include "Application.h"

void UpdateListener::handleFileAction(efsw::WatchID watchId,
									  const std::string& dir, const std::string& filename,
									  efsw::Action action, std::string oldFilename) {
	std::filesystem::path dirPath = dir;
	std::filesystem::path filePath = filename;
	std::filesystem::path fullPath = dirPath / filePath;
	std::string fullPathStr = fullPath.string();
//	printf("_filepath: %s | fullPath: %s\n", _filepath.c_str(), fullPathStr.c_str());
	if (_filepath == fullPathStr) {
		printf("Detected file change! Reloading...\n");
		_app.MarkForReload();
	}
//	switch (action) {
//		case efsw::Actions::Add:
//			std::cout << "DIR (" << dir << ") FILE (" << filename << ") has event Added" << std::endl;
//			break;
//		case efsw::Actions::Delete:
//			std::cout << "DIR (" << dir << ") FILE (" << filename << ") has event Delete" << std::endl;
//			break;
//		case efsw::Actions::Modified:
//			std::cout << "DIR (" << dir << ") FILE (" << filename << ") has event Modified" << std::endl;
//			break;
//		case efsw::Actions::Moved:
//			std::cout << "DIR (" << dir << ") FILE (" << filename << ") has event Moved from (" << oldFilename << ")" << std::endl;
//			break;
//		default:
//			std::cout << "Should never happen!" << std::endl;
//	}
}
