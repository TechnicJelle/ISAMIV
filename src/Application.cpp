#include "Application.h"

void ISAMIV_Application::ReloadImage() {
	//start timing
	auto start = std::chrono::high_resolution_clock::now();

	img = loader.LoadImage(filepath);

	//end timing
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	printf("Image load time: %ld microseconds\n", duration.count());
}

void ISAMIV_Application::SetupFileWatcher() {
	listener = new UpdateListener(filepath, *this);

	std::filesystem::path path = filepath;
	std::filesystem::path parentDir = path.parent_path();
	std::string parentStr = parentDir.string();
	printf("Watching folder for changes: %s\n", parentStr.c_str());

	efsw::WatchID watchID = fileWatcher.addWatch(parentStr, listener, true);
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
	printf("Image size: %d x %d\n", img.Sprite()->width, img.Sprite()->height);
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

	transformedView.DrawDecal({0, 0}, img.Decal());
	transformedView.HandlePanAndZoom(0 /*left mouse button*/);

	DrawCenteredString({float(ScreenWidth()) / 2.0f, float(ScreenHeight()) - 50.0f},
					   "Hello, world!", olc::WHITE, 2);

	return true;
}

bool ISAMIV_Application::OnUserDestroy() {
	delete listener;
	return true;
}


