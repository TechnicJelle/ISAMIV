#include "FileWatcherEventHandler.h"

#include "OpenDirectory.h"

FileWatcherEventHandler::FileWatcherEventHandler(OpenDirectory* openDir)
	: _openDir(openDir) {
}

void FileWatcherEventHandler::handleFileAction(const efsw::WatchID watchId,
                                               const std::string& dir, const std::string& filename,
                                               const efsw::Action action, const std::string oldFilename) {
	using namespace std::filesystem;

	printf("Event (%d): %s%s\n", action, dir.c_str(), filename.c_str());

	const path changedFilepath = path(dir) / path(filename);
	const path& openImagePath = _openDir->GetCurrentOpenImage().GetFilepath();

	if (changedFilepath == openImagePath) {
		_openDir->GetCurrentOpenImage().MarkForReload();
	}
	//TODO: Handle renames and deletions
}
