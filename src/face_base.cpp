#include "../include/face_part.hpp"

FaceBase::FaceBase(std::string object_name, cv::Mat image)
	: Object(object_name), face_base(image)
{
	/*
	* 顔パーツ切り取り済みでインペインティングされた画像がほすぃ
	*/
}

const cv::Mat FaceBase::getFaceBase() {
	return this->face_base;
}
