#include "../include/yuriface.hpp"

YuriFace::YuriFace() {
	objects = new std::vector<Object *>();
}

YuriFace::~YuriFace() {
	for (Object *object : *objects) {
		delete objects;
	}
	delete objects;
}

std::vector<Object *> *YuriFace::getObjects() {
	return objects;
}

cv::Mat YuriFace::getImage() {
	return image;
}

void YuriFace::setImage(cv::Mat src_image) {
	image = src_image;
}
