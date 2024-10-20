#include "stb_loader.h"

#include "stb_image.h"

olc::Renderable ISAMIV_StbLoader::LoadImage(const std::filesystem::path& filepath) const {
	constexpr int channels = 4;
	int width, height;
	unsigned char* data =
			stbi_load(filepath.string().c_str(), &width, &height, nullptr, channels);
	if (data == nullptr) {
		printf("stbi error (%s): %s\n", filepath.string().c_str(), stbi_failure_reason());
		return olc::Renderable();
	}
	//	printf("Size: %d x %d\n", width, height);

	olc::Renderable img;
	img.Create(width, height);
	memcpy(img.Sprite()->GetData(), data, width * height * channels);
	img.Decal()->Update();

	stbi_image_free(data);

	return img;
}
