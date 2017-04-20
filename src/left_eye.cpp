#include "../include/face_part.hpp"

LeftEye::LeftEye(std::string object_name, cv::Mat part, cv::Rect rect)
	: Object(object_name)
{
	/*
	* �؂�o���ς݂̍��ڃp�[�c���󂯎��
	*/
	in_face = rect;
	this->image = part;
}

/*
* �X�[�p�[�N���X��getName���\�b�h���d���Ȃ��I�[�o�[���C�h
*/
std::string LeftEye::getName() {
	return Object::getName();
}
