#include "Application.h"

int main(const int argc, const char* argv[]) {
	std::filesystem::path filepath;
	if (argc > 1) {
		filepath = argv[1];
		printf("Start File: %s\n", filepath.c_str());
	} else {
		printf("Usage: %s <image file>\n", argv[0]);
		return 1;
	}

	if (ISAMIV_Application app(filepath);
		app.Construct(1280, 710, 1, 1,
		              false, true, true, true))
		app.Start();
	return 0;
}
