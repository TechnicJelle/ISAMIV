#include "Application.h"

bool ISAMIV_Application::OnUserCreate() {
	_openImage.LoadImage();
	printf("Image size: %d x %d\n", _openImage.GetRenderable().Sprite()->width, _openImage.GetRenderable().Sprite()->height);
	_openImage.SetupFileWatcher(_fileWatcher);
	_fileWatcher.watch();

	return true;
}

bool ISAMIV_Application::OnUserUpdate(float fElapsedTime) {
	if (GetKey(olc::ESCAPE).bPressed || GetKey(olc::Q).bPressed)
		return false;

	if (GetKey(olc::R).bPressed)
		_openImage.MarkForReload();

	if (GetKey(olc::F).bPressed) {
		ClearFileWatcher();
		const std::string newImagePath = "/home/technicjelle/Downloads/control_panel.png";
		_openImage = OpenImage(newImagePath);
		_openImage.LoadImage();
		_openImage.SetupFileWatcher(_fileWatcher);
	}

	Clear(olc::MAGENTA);

	_transformedView.DrawDecal({0, 0}, _openImage.GetRenderable().Decal());
	_transformedView.HandlePanAndZoom(0 /*left mouse button*/);

	DrawCenteredString({static_cast<float>(ScreenWidth()) / 2.0f, static_cast<float>(ScreenHeight()) - 50.0f},
	                   "Hello, world!", olc::WHITE, 2);

	return true;
}

bool ISAMIV_Application::OnUserDestroy() {
	ClearFileWatcher();
	return true;
}
