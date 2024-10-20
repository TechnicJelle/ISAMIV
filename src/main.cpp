#include "Application.h"

int main(int argc, char* argv[]) {
	std::filesystem::path filepath;
	if (argc > 1) {
		filepath = argv[1];
		printf("File: %s\n", filepath.c_str());
	} else {
		printf("Usage: %s <image file>\n", argv[0]);
		return 1;
	}

	ISAMIV_Application demo(filepath);
	if (demo.Construct(1280, 710, 1, 1,
					   false, true, true, true))
		demo.Start();
	return 0;
}
