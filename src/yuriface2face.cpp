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
		* パーツの切り出し
		*/
		//パーツの矩形を取得
		cv::Rect rect = BoostBox2CvRect(CreateEnvelope(CreateRing(object)));
		//パーツ切り出し
		cv::Mat part_image = CutImage(all_face, rect);
		//顔面パーツから顔パーツを除去
		base = YuriInpainting(base, rect);
		
		/*
		*パーツの振り分け
		*/
		if (!object->getName().compare("Mouth")) {
			/*
			*口パーツ
			*/
			mouth = new Mouth("Mouth", part_image, rect);
		}
		else if (!object->getName().compare("RightEye")) {
			/*
			*右目パーツ
			*/
			right_eye = new RightEye("RightEye", part_image, rect);
		}
		else if (!object->getName().compare("LeftEye")) {
			/*
			*左目パーツ
			*/
			left_eye = new LeftEye("LeftEye", part_image, rect);
		}
		else if (!object->getName().compare("RightEyebrows")) {
			/*
			* 右眉毛パーツ
			*/
			right_eye_brows = new RightEyeBrows("RightEyebrows", part_image, rect);
		}
		else if (!object->getName().compare("LeftEyebrows")) {
			/*
			* 左眉毛パーツ
			*/
			left_eye_brows = new LeftEyeBrows("LeftEyebrows", part_image, rect);
		}
	}

	//顔パーツが除去された顔面パーツ
	face_base = new FaceBase("FaceBase", base);

	face = new Face(face_base, mouth, right_eye, left_eye, right_eye_brows, left_eye_brows);

}
