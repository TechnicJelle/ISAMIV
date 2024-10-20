#pragma once

#include <efsw/efsw.hpp>

class OpenImage;
class ISAMIV_Application;

class UpdateListener final : public efsw::FileWatchListener {
	OpenImage* _parentImage;

public:
	explicit UpdateListener(OpenImage* parentImage);

private:
	void handleFileAction(efsw::WatchID watchId,
	                      const std::string& dir, const std::string& filename,
	                      efsw::Action action, std::string oldFilename) override;
};
