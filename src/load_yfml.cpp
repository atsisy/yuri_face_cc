#define _CRT_SECURE_NO_WARNINGS

#include <fstream>
#include <string>
#include <vector>
#include "../include/yuriface.hpp"

YuriFace *LoadYFML(std::string file_name) {
	int section_count = 0;
	YuriFace *yuri_face = new YuriFace();
	cv::Mat img;
	
	std::ifstream yfml_doc(file_name);
	std::string line, word;

	Object *object = NULL;

	if(yfml_doc.fail()){
		std::cout << "can't open" << std::endl;
	}

	/*
	* 一行目のシグネチャを確認
	*/
	std::getline(yfml_doc, line);
	if (line.compare("yfml"))
		return NULL;

	/*
	*画像を読み込んで、空ならNULLを返して終了
	*/
	std::getline(yfml_doc, line);
	img = cv::imread(line.substr(8));
	if (img.empty())
		return NULL;
	
	//読み込んだ画像をセット
	yuri_face->setImage(img);

	while (std::getline(yfml_doc, line)) {
		std::stringstream stream(line);

		stream >> word;
		if (!word.compare("{")) {
			section_count++;
		}
		else if (!word.compare("}")) {
			section_count--;
		}
		else {
			if (!word.compare("LayerName")) {
				stream >> word;
				object = new Object(word);
			}
			else if (!word.compare("dots")) {
				std::getline(yfml_doc, line);
				std::stringstream stream2(line);
				while (line.compare("lines")) {
					std::string x, y;
					stream2 >> x >> y;
					object->getDotsVector()->push_back(new Dot(std::stoi(x), std::stoi(y)));
					std::getline(yfml_doc, line);
					stream2.str("");
					stream2.clear(std::stringstream::goodbit);
					stream2 << line;
				}
				std::getline(yfml_doc, line);
				
				while (line != "}") {
					std::stringstream stream3(line);
					std::string x, y;
					stream3 >> x >> y;
					Dot finding_dot(std::stoi(x), std::stoi(y));
					for (Dot *dot : *(object->getDotsVector())) {
						if (dot->equals(finding_dot)) {
							stream3 >> x >> y;
							Dot finding_dot_c(std::stoi(x), std::stoi(y));
							for (Dot *dot_c : *object->getDotsVector()) {
								if (finding_dot_c.equals(*dot_c)) {
									dot->getConnectedDotsVector()->push_back(new Dot(std::stoi(x), std::stoi(y)));
									goto a_line_finish;
								}
							}
							break;
						}
					}
					a_line_finish:
					std::getline(yfml_doc, line);
				}
				section_count--;
			}
			yuri_face->getObjects()->push_back(object);
		}
	}

	if (!section_count)
		std::cout << "SUCCESS" << std::endl;

	return yuri_face;
}
