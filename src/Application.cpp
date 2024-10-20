#include "Application.h"

void ISAMIV_Application::SetupFileWatcher() {
	const std::filesystem::path& filepath = image.GetFilepath();
	listener = new UpdateListener(filepath, this);

	const std::filesystem::path parentDir = filepath.parent_path();
	printf("Watching folder for changes: %s\n", parentDir.c_str());

	if (const efsw::WatchID watchID = fileWatcher.addWatch(parentDir.string(), listener, false);
		watchID < 0) {
		printf("Error adding watch! Watch ID: %ld\n", watchID);
		return;
	}
	fileWatcher.watch();
}

bool ISAMIV_Application::OnUserCreate() {
	image.LoadImage();
	printf("Image size: %d x %d\n", image.GetRenderable().Sprite()->width, image.GetRenderable().Sprite()->height);
	SetupFileWatcher();

	return true;
}

bool ISAMIV_Application::OnUserUpdate(float fElapsedTime) {
	if (GetKey(olc::ESCAPE).bPressed || GetKey(olc::Q).bPressed)
		return false;

	if (GetKey(olc::R).bPressed)
		image.MarkForReload();

	Clear(olc::MAGENTA);

	transformedView.DrawDecal({0, 0}, image.GetRenderable().Decal());
	transformedView.HandlePanAndZoom(0 /*left mouse button*/);

	DrawCenteredString({static_cast<float>(ScreenWidth()) / 2.0f, static_cast<float>(ScreenHeight()) - 50.0f},
	                   "Hello, world!", olc::WHITE, 2);

	return true;
}

bool ISAMIV_Application::OnUserDestroy() {
	delete listener;
	return true;
}
