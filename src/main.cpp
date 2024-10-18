#include <utility>

#include "olcPixelGameEngine.h"
#include "olcPGEX_TransformedView.h"
#include "loaders/stb/stb_loader.h"

class ISAMIV_Application : public olc::PixelGameEngine {
public:
	explicit ISAMIV_Application(std::string filename) : filename(std::move(filename)) {
		sAppName = "ISAMIV";
	}

	void DrawCenteredString(olc::vf2d pos, const std::string &text, const olc::Pixel &colour = olc::WHITE, int scale = 1) {
		olc::vi2d size = GetTextSize(text) * scale;
		DrawString(pos - size / 2, text, colour, scale);
	}

	void DrawCenteredDecal(olc::vf2d pos, olc::Decal* decal) {
		olc::vi2d size = {decal->sprite->width, decal->sprite->height};
		DrawDecal(pos - size / 2, decal);
	}

private:
	std::string filename;
	olc::Renderable img;
	olc::TransformedView transformedView;

public:
	bool OnUserCreate() override {
		ISAMIV_StbLoader loader;

		//start timing
		auto start = std::chrono::high_resolution_clock::now();

		img = loader.LoadImage(filename);

		//end timing
		auto end = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
		printf("Time it took to load the image: %ld microseconds\n", duration.count());

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override {
		if (GetKey(olc::ESCAPE).bPressed || GetKey(olc::Q).bPressed)
			return false;

		Clear(olc::MAGENTA);

		transformedView.DrawDecal({0, 0}, img.Decal());
		transformedView.HandlePanAndZoom(0 /*left mouse button*/);

		DrawCenteredString({float(ScreenWidth()) / 2.0f, float(ScreenHeight()) - 50.0f}, "Hello, world!", olc::WHITE, 2);

		return true;
	}
};

int main(int argc, char* argv[]) {
	std::string file;
	if (argc > 1) {
		file = argv[1];
		printf("File: %s\n", file.c_str());
	} else {
		printf("Usage: %s <image file>\n", argv[0]);
		return 1;
	}

	ISAMIV_Application demo(file);
	if (demo.Construct(1280, 710, 1, 1, false, true, true, true))
		demo.Start();
	return 0;
}
