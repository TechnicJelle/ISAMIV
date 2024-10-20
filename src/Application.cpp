#include "Application.h"

bool ISAMIV_Application::OnUserCreate() {
	image.LoadImage();
	printf("Image size: %d x %d\n", image.GetRenderable().Sprite()->width, image.GetRenderable().Sprite()->height);
	image.SetupFileWatcher(fileWatcher);
	fileWatcher.watch();

	return true;
}

bool ISAMIV_Application::OnUserUpdate(float fElapsedTime) {
	if (GetKey(olc::ESCAPE).bPressed || GetKey(olc::Q).bPressed)
		return false;

	if (GetKey(olc::R).bPressed)
		image.MarkForReload();

	if (GetKey(olc::F).bPressed) {
		ClearFileWatcher();
		const std::string newImagePath = "/home/technicjelle/Downloads/control_panel.png";
		image = OpenImage(newImagePath);
		image.LoadImage();
		image.SetupFileWatcher(fileWatcher);
	}

	Clear(olc::MAGENTA);

	transformedView.DrawDecal({0, 0}, image.GetRenderable().Decal());
	transformedView.HandlePanAndZoom(0 /*left mouse button*/);

	DrawCenteredString({static_cast<float>(ScreenWidth()) / 2.0f, static_cast<float>(ScreenHeight()) - 50.0f},
	                   "Hello, world!", olc::WHITE, 2);

	return true;
}

bool ISAMIV_Application::OnUserDestroy() {
	ClearFileWatcher();
	return true;
}
