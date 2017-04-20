#include "../include/init.hpp"

#include <iostream>
#include <cmath>
#include <opencv2/opencv.hpp>
#include <boost/version.hpp>
#include "../include/yuriface.hpp"
#include "../include/transform.hpp"
#include "../include/geometry.hpp"
#include "../include/face_part.hpp"


int main(int argc, char **argv) {

	std::cout << "Start Yuri Face" << std::endl;

	YuriFace *yuriface = LoadYFML(argv[1]);
	cv::Mat img = yuriface->getImage();

	Face *face_obj = NULL;
	yuriface2face(yuriface, face_obj);


	/*
	std::cout << "dots" << std::endl;
	
	for (Dot *dot : *yuriface->getObjects()->at(0)->getDotsVector()) {
		std::cout << dot->getX() << ":" << dot->getY() << std::endl;
		cv::circle(img, cv::Point(dot->getX(), dot->getY()), 5, cv::Scalar(0, 0, 0), 1, 1);
	}
	std::cout << "line" << std::endl;
	for (Dot *dot : *yuriface->getObjects()->at(0)->getDotsVector()) {
		std::cout << dot->getX() << ":" << dot->getY() << " ";
		for (Dot *dot2 : *dot->getConnectedDotsVector()) {
			std::cout << dot2->getX() << ":" << dot2->getY() << std::endl;
			cv::line(img, cv::Point(dot->getX(), dot->getY()), cv::Point(dot2->getX(), dot2->getY()), cv::Scalar(0, 0, 0));
		}
	}
	std::cout << "name : " << yuriface->getObjects()->at(0)->getName() << std::endl;
	
	*/

	cv::Point2f dst_points[4];

	cv::Rect rect = BoostBox2CvRect(CreateEnvelope(CreateRing(yuriface->getObjects()->at(0))));
	cv::Mat result = CutImage(img, rect);
	result = RotationTransform(result, 45);

	cv::Mat face = YuriInpainting(img, rect);

	dst_points[0] = cv::Point2f(0.0f, 0.0f);
	dst_points[1] = cv::Point2f(result.cols * 0.2, result.rows * 0.8);
	dst_points[2] = cv::Point2f(result.cols, result.rows);
	dst_points[3] = cv::Point2f(result.cols * 0.8, result.rows * 0.2);

	result = PerspectiveTransform(result, dst_points, cv::Size(result.cols, result.rows));

	result = RotationTransform(result, -45);
	
	int i;
	result = SharpenImage(result, &i);

	cv::namedWindow("Yuri Face");
	//result = YuriFacePasteImage(face, result, rect.x * 0.90, rect.y * 0.85).clone();
	result = face_obj->getMouth()->OpenMouth(face_obj->getFaceBase(), 6).clone();
	cv::Mat level3 = face_obj->getMouth()->OpenMouth(face_obj->getFaceBase(), 4).clone();
	
	while (true) {
		ShowAndWait(img, "Yuri Face", 180);
		ShowAndWait(level3, "Yuri Face", 180);
		ShowAndWait(result, "Yuri Face", 180);
	}

}
