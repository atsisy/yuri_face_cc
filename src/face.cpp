#include "../include/face_part.hpp"

Face::Face(FaceBase *face_base_obj, Mouth *mouth_obj, RightEye *right_eye_obj, LeftEye *left_eye_obj, RightEyeBrows *right_eye_brows_obj, LeftEyeBrows *left_eye_brows_obj)
{
	this->face_base = face_base_obj;
	this->mouth = mouth_obj;
	this->right_eye = right_eye_obj;
	this->left_eye = left_eye_obj;
	this->right_eye_brows = right_eye_brows_obj;
	this->left_eye_brows = left_eye_brows_obj;
}

Face::~Face() {
	delete this->face_base;
	delete this->mouth;
	delete this->right_eye;
	delete this->left_eye;
	delete this->right_eye_brows;
	delete this->left_eye_brows;
}

Mouth *Face::getMouth() {
	return this->mouth;
}

FaceBase *Face::getFaceBase() {
	return this->face_base;
}

