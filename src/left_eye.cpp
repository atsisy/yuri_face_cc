#include "../include/face_part.hpp"

LeftEye::LeftEye(std::string object_name, cv::Mat part, cv::Rect rect)
	: Object(object_name)
{
	/*
	* 切り出し済みの左目パーツを受け取る
	*/
	in_face = rect;
	this->image = part;
}

/*
* スーパークラスのgetNameメソッドを仕方なくオーバーライド
*/
std::string LeftEye::getName() {
	return Object::getName();
}
