#include "../include/face_part.hpp"

RightEyeBrows::RightEyeBrows(std::string object_name, cv::Mat part, cv::Rect rect)
	: Object(object_name)
{
	/*
	*�؂�o���ς݂̉E���уp�[�c���󂯎��
	*/
	in_face = rect;
	this->image = part;
}

/*
* �X�[�p�[�N���X��getName���\�b�h���d���Ȃ��I�[�o�[���C�h
*/
std::string RightEyeBrows::getName() {
	return Object::getName();
}
