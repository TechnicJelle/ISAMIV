#pragma once

#include <efsw/efsw.hpp>

class OpenImage;
class ISAMIV_Application;

class UpdateListener final : public efsw::FileWatchListener {
	const std::filesystem::path* _filepath;
	OpenImage* _parentImage;

public:
	UpdateListener(const std::filesystem::path* filepath, OpenImage* parentImage);

private:
	void handleFileAction(efsw::WatchID watchId,
	                      const std::string& dir, const std::string& filename,
	                      efsw::Action action, std::string oldFilename) override;
};
