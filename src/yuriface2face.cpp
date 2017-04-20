#include "../include/yuriface.hpp"
#include "../include/face_part.hpp"
#include "../include/geometry.hpp"

void yuriface2face(YuriFace *yuriface, Face* & face) {
	cv::Mat all_face = yuriface->getImage().clone();
	cv::Mat base = all_face.clone();

	FaceBase *face_base = NULL;
	Mouth *mouth = NULL;
	RightEye *right_eye = NULL;
	LeftEye *left_eye = NULL;
	RightEyeBrows *right_eye_brows = NULL;
	LeftEyeBrows *left_eye_brows = NULL;

	for (Object *object : *yuriface->getObjects()) {
		/*
		* �p�[�c�̐؂�o��
		*/
		//�p�[�c�̋�`���擾
		cv::Rect rect = BoostBox2CvRect(CreateEnvelope(CreateRing(object)));
		//�p�[�c�؂�o��
		cv::Mat part_image = CutImage(all_face, rect);
		//��ʃp�[�c�����p�[�c������
		base = YuriInpainting(base, rect);
		
		/*
		*�p�[�c�̐U�蕪��
		*/
		if (!object->getName().compare("Mouth")) {
			/*
			*���p�[�c
			*/
			mouth = new Mouth("Mouth", part_image, rect);
		}
		else if (!object->getName().compare("RightEye")) {
			/*
			*�E�ڃp�[�c
			*/
			right_eye = new RightEye("RightEye", part_image, rect);
		}
		else if (!object->getName().compare("LeftEye")) {
			/*
			*���ڃp�[�c
			*/
			left_eye = new LeftEye("LeftEye", part_image, rect);
		}
		else if (!object->getName().compare("RightEyebrows")) {
			/*
			* �E���уp�[�c
			*/
			right_eye_brows = new RightEyeBrows("RightEyebrows", part_image, rect);
		}
		else if (!object->getName().compare("LeftEyebrows")) {
			/*
			* �����уp�[�c
			*/
			left_eye_brows = new LeftEyeBrows("LeftEyebrows", part_image, rect);
		}
	}

	//��p�[�c���������ꂽ��ʃp�[�c
	face_base = new FaceBase("FaceBase", base);

	face = new Face(face_base, mouth, right_eye, left_eye, right_eye_brows, left_eye_brows);

}
