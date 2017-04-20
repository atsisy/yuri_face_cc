#include "../include/face_part.hpp"

static float OpenMouth_sub(int level);

/*
*口を開くメソッド
*/
cv::Mat Mouth::OpenMouth(FaceBase *face, int level, float manual) {
	cv::Mat result = this->image.clone();
	cv::Point2f dst_points[4];
	int width;
	float k;

	if ((k = OpenMouth_sub(level)) == -1.0f) {
		k = manual;
	}

	cv::Point center((in_face.x + (in_face.width >> 1)), (in_face.y + (in_face.height >> 1)));

	result = RotationTransform(result, 45);

	dst_points[0] = cv::Point2f(0.0f, 0.0f);
	dst_points[1] = cv::Point2f(result.cols * k, result.rows * (1.0f - k));
	dst_points[2] = cv::Point2f(result.cols, result.rows);
	dst_points[3] = cv::Point2f(result.cols * (1.0f - k), result.rows * k);

	result = SharpenImage(
		RotationTransform(PerspectiveTransform(result, dst_points, cv::Size(result.cols, result.rows)), -45),
		&width
	);

	//変形後の幅（回転等で黒くなっている部分を除く）
	return YuriFacePasteImage(face->getFaceBase().clone(), result.clone(), center.x - (result.cols >> 1), (center.y - (result.rows >> 1)));
}

static float OpenMouth_sub(int level) {
	switch (level)
	{
	case 0:
		return 0.0f;
	case 1:
		return 0.01f;
	case 2:
		return 0.03f;
	case 3:
		return 0.05f;
	case 4:
		return 0.1f;
	case 5:
		return 0.15f;
	case 6:
		return 0.2f;
	case 7:
		return 0.25f;
	case 8:
		return 0.3f;
	case 9:
		return 0.35f;
	case 10:
		return 0.4f;
	default:
		break;
	}
	return -1.0f;
}

/*
* コンストラクタ
*/
Mouth::Mouth(std::string object_name, cv::Mat part, cv::Rect rect)
	: Object(object_name), image(part), in_face(rect)
{
	/*
	* 切り出し済みのパーツをがほすぃ
	*/
}

/*
* スーパークラスのgetNameメソッドを仕方なくオーバーライド
*/
std::string Mouth::getName() {
	return Object::getName();
}

const cv::Mat Mouth::getImage() {
	return this->image;
}
