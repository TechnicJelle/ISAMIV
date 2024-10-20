#pragma once

#include <efsw/efsw.hpp>

class ISAMIV_Application;

class UpdateListener final : public efsw::FileWatchListener {
	const std::filesystem::path _filepath;
	ISAMIV_Application* _app;

public:
	UpdateListener(std::filesystem::path filepath, ISAMIV_Application* app);

private:
	void handleFileAction(efsw::WatchID watchId,
	                      const std::string& dir, const std::string& filename,
	                      efsw::Action action, std::string oldFilename) override;
};
