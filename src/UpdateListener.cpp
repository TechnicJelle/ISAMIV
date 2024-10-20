#include <filesystem>

#include "UpdateListener.h"
#include "Application.h"

UpdateListener::UpdateListener(OpenImage* parentImage)
	: _parentImage(parentImage) {
}

void UpdateListener::handleFileAction(efsw::WatchID watchId,
                                      const std::string& dir, const std::string& filename,
                                      efsw::Action action, std::string oldFilename) {
	using namespace std::filesystem;
	// printf("_filepath: %s | fullPath: %s\n", _filepath.string().c_str(), changedFilePath.string().c_str());
	if (const path changedFilePath = path(dir) / path(filename);
		_parentImage->GetFilepath() == changedFilePath) {
		printf("Detected file change! Reloading...\n");
		_parentImage->MarkForReload();
	}
	// switch (action) {
	// 	case efsw::Actions::Add:
	// 		std::cout << "DIR (" << dir << ") FILE (" << filename << ") has event Added" << std::endl;
	// 		break;
	// 	case efsw::Actions::Delete:
	// 		std::cout << "DIR (" << dir << ") FILE (" << filename << ") has event Delete" << std::endl;
	// 		break;
	// 	case efsw::Actions::Modified:
	// 		std::cout << "DIR (" << dir << ") FILE (" << filename << ") has event Modified" << std::endl;
	// 		break;
	// 	case efsw::Actions::Moved:
	// 		std::cout << "DIR (" << dir << ") FILE (" << filename << ") has event Moved from (" << oldFilename << ")" << std::endl;
	// 		break;
	// 	default:
	// 		std::cout << "Should never happen!" << std::endl;
	// }
}
