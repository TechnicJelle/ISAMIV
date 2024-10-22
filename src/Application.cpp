#include "Application.h"

ISAMIV_Application::ISAMIV_Application(std::filesystem::path filepath)
	: _openDirectory(this, std::move(filepath)) {
	sAppName = "ISAMIV";
}

bool ISAMIV_Application::OnUserCreate() {
	return true;
}

void ISAMIV_Application::HandleImagePrevNext(const float fElapsedTime) {
	// Handle a single press
	if (GetKey(olc::RIGHT).bPressed)
		_openDirectory.NextFile();

	if (GetKey(olc::LEFT).bPressed)
		_openDirectory.PreviousFile();

	// When holding the key down, scroll through images fast
	//  (But only after half a second of holding down, to make sure the user really wants to fast scroll)
	if (GetKey(olc::RIGHT).bHeld || GetKey(olc::LEFT).bHeld) {
		_timeSinceScrollStart += fElapsedTime;
		_timeSinceLastGoTo += fElapsedTime;
	}

	if (GetKey(olc::RIGHT).bReleased || GetKey(olc::LEFT).bReleased) {
		_timeSinceScrollStart = 0.0f;
		_timeSinceLastGoTo = -0.5f; //to make up for the .5s of waiting before fast scrolling
	}

	if (_timeSinceScrollStart > 0.5f) {
		constexpr int targetFPS = 24; //TODO: Expose this as a setting
		constexpr float targetFPSSeconds = 1.0f / targetFPS;

		if (_timeSinceLastGoTo > targetFPSSeconds) {
			_timeSinceLastGoTo -= targetFPSSeconds;

			if (GetKey(olc::RIGHT).bHeld)
				_openDirectory.NextFile();

			if (GetKey(olc::LEFT).bHeld)
				_openDirectory.PreviousFile();
		}
	}
}

bool ISAMIV_Application::OnUserUpdate(float fElapsedTime) {
	if (GetKey(olc::ESCAPE).bPressed || GetKey(olc::Q).bPressed)
		return false;

	if (GetKey(olc::R).bPressed)
		_openDirectory.GetCurrentOpenImage().MarkForReload();

	HandleImagePrevNext(fElapsedTime);

	Clear(olc::MAGENTA);

	_transformedView.DrawDecal({0, 0}, _openDirectory.GetCurrentOpenImage().GetRenderable().Decal());
	_transformedView.HandlePanAndZoom(0 /*left mouse button*/);

	DrawCenteredString({static_cast<float>(ScreenWidth()) / 2.0f, 20.0f},
	                   _openDirectory.GetDirectoryPath().string(), olc::WHITE, 2);

	DrawCenteredString({static_cast<float>(ScreenWidth()) / 2.0f, 50.0f},
	                   _openDirectory.GetCurrentOpenImage().GetFilepath().filename().string(), olc::WHITE, 2);

	return true;
}

bool ISAMIV_Application::OnUserDestroy() {
	return true;
}

void ISAMIV_Application::DrawCenteredString(const olc::vf2d& pos, const std::string& text, const olc::Pixel& colour, const int scale) {
	const olc::vi2d size = GetTextSize(text) * scale;
	const olc::vf2d vScale = {static_cast<float>(scale), static_cast<float>(scale)};
	DrawStringDecal(pos - size / 2, text, colour, vScale);
}

void ISAMIV_Application::DrawCenteredDecal(const olc::vf2d& pos, olc::Decal* decal) {
	const olc::vi2d size = {decal->sprite->width, decal->sprite->height};
	DrawDecal(pos - size / 2, decal);
}

const FileTypeRegistry& ISAMIV_Application::GetFileTypeRegistry() const {
	return _fileTypeRegistry;
}
