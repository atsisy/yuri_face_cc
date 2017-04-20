#include "../include/face_part.hpp"

LeftEyeBrows::LeftEyeBrows(std::string object_name, cv::Mat part, cv::Rect rect)
	: Object(object_name)
{
	/*
	* 切り出し済みの左眉毛パーツを受け取る
	*/
	in_face = rect;
	this->image = part;

}

/*
* スーパークラスのgetNameメソッドを仕方なくオーバーライド
*/
std::string LeftEyeBrows::getName() {
	return Object::getName();
}
