#include "qoi_loader.h"

#include <qoi.h>

olc::Renderable ISAMIV_QoiLoader::LoadImage(const std::filesystem::path& filepath) const {
	qoi_desc desc;
	void* data = qoi_read(filepath.string().c_str(), &desc, 4);
	if (data == nullptr) {
		printf("qoi error\n");
		return olc::Renderable();
	}

	olc::Renderable img;
	img.Create(desc.width, desc.height);
	memcpy(img.Sprite()->GetData(), data, desc.width * desc.height * 4);
	img.Decal()->Update();

	free(data);

	return img;
}
