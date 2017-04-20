#include "../include/face_part.hpp"

RightEye::RightEye(std::string object_name, cv::Mat part, cv::Rect rect)
	: Object(object_name)
{
	/*
	* �؂�o���ς݂̉E�ڃp�[�c���󂯎��
	*/
	in_face = rect;
	this->image = part;
}

/*
* �X�[�p�[�N���X��getName���\�b�h���d���Ȃ��I�[�o�[���C�h
*/
std::string RightEye::getName() {
	return Object::getName();
}
