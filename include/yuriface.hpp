#ifndef YURIFACE_HPP
#define YURIFACE_HPP

#include <vector>
#include <opencv2/opencv.hpp>
#include "object.hpp"
#include "face_part.hpp"

class YuriFace {
private:
	std::vector<Object *> *objects;
	cv::Mat image;

public:
	YuriFace();
	~YuriFace();

	std::vector<Object *> *getObjects();
	cv::Mat getImage();

	void setImage(cv::Mat src_image);

};

YuriFace *LoadYFML(std::string file_name);
void yuriface2face(YuriFace *yuriface, Face* & face);

#endif
