#ifndef FACE_PART_HPP
#define FACE_PART_HPP


#include <opencv2/opencv.hpp>
#include "transform.hpp"
#include "object.hpp"


class FaceBase : Object {
private:
	const cv::Mat face_base;
public:
	FaceBase(std::string object_name, cv::Mat image);

	const cv::Mat getFaceBase();

};

class Mouth : Object {
private:
	const cv::Mat image;
	const cv::Rect in_face;

public:
	Mouth(std::string object_name, cv::Mat part, cv::Rect rect);

	/*
	* äÁÉpÅ[ÉcÇ…å˚Çï`âÊÇµÇΩâÊëúÇï‘Ç∑
	*/
	cv::Mat OpenMouth(FaceBase *face, int level, float manual = 0.0f);
	std::string getName();
	const cv::Mat getImage();
};

class RightEye : Object {
private:
	cv::Mat image;
	cv::Rect in_face;
public:
	RightEye(std::string object_name, cv::Mat part, cv::Rect rect);
	std::string getName();
};

class LeftEye : Object {
private:
	cv::Mat image;
	cv::Rect in_face;
public:
	LeftEye(std::string object_name, cv::Mat part, cv::Rect rect);
	std::string getName();
};

class RightEyeBrows : Object {
private:
	cv::Mat image;
	cv::Rect in_face;
public:
	RightEyeBrows(std::string object_name, cv::Mat part, cv::Rect rect);
	std::string getName();
};

class LeftEyeBrows : Object {
private:
	cv::Mat image;
	cv::Rect in_face;
public:
	LeftEyeBrows(std::string object_name, cv::Mat part, cv::Rect rect);
	std::string getName();
};

class Face {
private:
	FaceBase *face_base;
	RightEye *right_eye;
	LeftEye *left_eye;
	RightEyeBrows *right_eye_brows;
	LeftEyeBrows *left_eye_brows;
	Mouth *mouth;
public:
	Face(FaceBase *face_base_obj, Mouth *mouth_obj, RightEye *right_eye_obj, LeftEye *left_eye_obj, RightEyeBrows *right_eye_brows_obj, LeftEyeBrows *left_eye_brows_obj);
	~Face();

	FaceBase *getFaceBase();
	Mouth *getMouth();
};

#endif
