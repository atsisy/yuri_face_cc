#include "../include/face_part.hpp"

FaceBase::FaceBase(std::string object_name, cv::Mat image)
	: Object(object_name), face_base(image)
{
	/*
	* ��p�[�c�؂���ς݂ŃC���y�C���e�B���O���ꂽ�摜���ق���
	*/
}

const cv::Mat FaceBase::getFaceBase() {
	return this->face_base;
}
