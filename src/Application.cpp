#include "Application.h"

void ISAMIV_Application::ReloadImage() {
	image.LoadImage(loader);
}

void ISAMIV_Application::SetupFileWatcher() {
	const std::filesystem::path& filepath = image.GetFilepath();
	listener = new UpdateListener(filepath, this);

	std::filesystem::path parentDir = filepath.parent_path();
	printf("Watching folder for changes: %s\n", parentDir.c_str());

	efsw::WatchID watchID = fileWatcher.addWatch(parentDir.string(), listener, false);
	if (watchID < 0) {
		printf("Error adding watch! Watch ID: %ld\n", watchID);
		return;
	}
	fileWatcher.watch();
}

void ISAMIV_Application::MarkForReload() {
	shouldReload = true;
}


bool ISAMIV_Application::OnUserCreate() {
	ReloadImage();
	printf("Image size: %d x %d\n", image.GetRenderable().Sprite()->width, image.GetRenderable().Sprite()->height);
	SetupFileWatcher();

	return true;
}

bool ISAMIV_Application::OnUserUpdate(float fElapsedTime) {
	if (GetKey(olc::ESCAPE).bPressed || GetKey(olc::Q).bPressed)
		return false;

	if (GetKey(olc::R).bPressed)
		MarkForReload();

	if (shouldReload) {
		ReloadImage();
		shouldReload = false;
	}

	Clear(olc::MAGENTA);

	transformedView.DrawDecal({0, 0}, image.GetRenderable().Decal());
	transformedView.HandlePanAndZoom(0 /*left mouse button*/);

	DrawCenteredString({float(ScreenWidth()) / 2.0f, float(ScreenHeight()) - 50.0f},
					   "Hello, world!", olc::WHITE, 2);

	return true;
}

bool ISAMIV_Application::OnUserDestroy() {
	delete listener;
	return true;
}


