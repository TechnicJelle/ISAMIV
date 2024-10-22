#pragma once

#include <efsw/efsw.hpp>

class OpenDirectory;

class FileWatcherEventHandler final : public efsw::FileWatchListener {
	OpenDirectory* _openDir;

public:
	explicit FileWatcherEventHandler(OpenDirectory* openDir);

public:
	void handleFileAction(efsw::WatchID watchId,
	                      const std::string& dir, const std::string& filename,
	                      efsw::Action action, std::string oldFilename) override;
};
