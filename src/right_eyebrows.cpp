#include "../include/face_part.hpp"

RightEyeBrows::RightEyeBrows(std::string object_name, cv::Mat part, cv::Rect rect)
	: Object(object_name)
{
	/*
	*切り出し済みの右眉毛パーツを受け取る
	*/
	in_face = rect;
	this->image = part;
}

/*
* スーパークラスのgetNameメソッドを仕方なくオーバーライド
*/
std::string RightEyeBrows::getName() {
	return Object::getName();
}
