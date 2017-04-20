#include "../include/transform.hpp"
#include <algorithm>

/*
* PerspectiveTransform関数
* 画像を透視射影変換して返す関数
* 引数
* cv::Mat image
* 透視射影変換を行う画像
* cv::Point2f *points
* どんなふうに透視射影変換を行うか
* cv::Size dst_size
* 生成される画像のサイズ
* 返り値
* 第一引数で受け取ったMatの透視射影変換結果の画像
*/
cv::Mat PerspectiveTransform(cv::Mat image, cv::Point2f *points, cv::Size dst_size) {
	cv::Mat mat, result;
	cv::Point2f original_ponits[4];

	original_ponits[0] = cv::Point2f(0.0f, 0.0f);
	original_ponits[1] = cv::Point2f(0.0f, image.rows);
	original_ponits[2] = cv::Point2f(image.cols, image.rows);
	original_ponits[3] = cv::Point2f(image.cols, 0.0f);

	mat = cv::getPerspectiveTransform(original_ponits, points);
	cv::warpPerspective(image, result, mat, dst_size);

	return result;

}

/*
* RotationTransform関数
* 画像を回転変形する関数
* 引数
* cv::Mat image
* 回転変形させる画像
* double angle
* 回転させる角度（度数法で指定）
* 返り値
* 第一引数で受け取ったMatの回転変形結果の画像
*/
cv::Mat RotationTransform(cv::Mat image, double angle) {
	//結果用
	cv::Mat result;

	//画像の中心座標を取得
	cv::Point2f center(image.cols / 2.0, image.rows / 2.0);
	cv::Mat rot_mat = cv::getRotationMatrix2D(center, angle, 1.0);

	//矩形を決定する
	cv::Rect rect = cv::RotatedRect(center, image.size(), angle).boundingRect();

	//変換行列を調整
	rot_mat.at<double>(0, 2) += rect.width / 2.0 - center.x;
	rot_mat.at<double>(1, 2) += rect.height / 2.0 - center.y;

	cv::warpAffine(image, result, rot_mat, rect.size());

	return result;
}

/*
* CutImage関数
* 画像の指定した範囲を切り抜く関数
* 引数
* cv::Mat image
* 切り抜き元の画像
* cv::Rect rect
* 切り出す領域
* 返り値
* 切り出されたcv::Mat
*/
cv::Mat CutImage(cv::Mat image, cv::Rect rect) {
	return cv::Mat(image, rect).clone();
}

/*
* PasteImage関数
* 画像をもう一つの画像に貼り付ける関数
* 引数
* cv::Mat dst_image
* 貼り付け先の画像
* cv::Mat src_image
* 貼り付ける画像
* int x
* 第一引数の画像の貼り付けるX位置
* int y
* 第一引数の画像の貼り付けるY位置
*/
cv::Mat PasteImage(cv::Mat dst_image, cv::Mat src_image, int x, int y) {

	cv::Mat dst_image_clone = dst_image.clone();

	if (x >= dst_image_clone.cols || y >= dst_image_clone.rows) {
		std::cout << "Error : Source image too large." << std::endl;
		return dst_image_clone;
	}

	int w = (x >= 0) ? std::min(dst_image_clone.cols - x, src_image.cols) : std::min(std::max(src_image.cols + x, 0), dst_image_clone.cols);
	int h = (y >= 0) ? std::min(dst_image_clone.rows - y, src_image.rows) : std::min(std::max(src_image.rows + y, 0), dst_image_clone.rows);
	int u = (x >= 0) ? 0 : std::min(-x, src_image.cols - 1);
	int v = (y >= 0) ? 0 : std::min(-y, src_image.rows - 1);
	int px = std::max(x, 0);
	int py = std::max(y, 0);

	cv::Mat cut_dst = dst_image_clone(cv::Rect(px, py, w, h));
	cv::Mat result = src_image(cv::Rect(u, v, w, h));
	result.copyTo(cut_dst);

	return dst_image_clone;
}

/*
* BlackPixelMakeClearness関数
* 黒いピクセルを透過したcv::Matを吐く関数
* 引数
* cv::Mat image
* 透過したい画像
* 返り値
* 引数で受け取った画像に透過処理を行った画像
*/
cv::Mat BlackPixelMakeClearness(cv::Mat image) {
	cv::Mat alpha_image(image.size(), CV_8UC3);
	cv::cvtColor(image, alpha_image, CV_RGB2RGBA);

	for (int y = 0; y < alpha_image.rows; y++) {
		for (int x = 0; x < alpha_image.cols; x++) {
			cv::Vec4b px = alpha_image.at<cv::Vec4b>(x, y);
			if (px[0] + px[1] + px[2] == 0) {
				px[3] = 0;
				alpha_image.at<cv::Vec4b>(x, y) = px;
			}
		}
	}
	return alpha_image;
}

cv::Mat YuriFacePasteImage(cv::Mat dst_image, cv::Mat src_image, int dx, int dy) {
	cv::Vec3b *src_y;
	cv::Vec3b *dst_y;

	for (int y = 0; y < src_image.rows; y++) {
		if (y + dy >= dst_image.rows)
			break;

		dst_y = dst_image.ptr<cv::Vec3b>(y + dy);
		src_y = src_image.ptr<cv::Vec3b>(y);
		
		dst_y += dx;
		for (int x = 0; x < src_image.cols; x++) {
			if (x + x >= dst_image.cols)
				break;
			if (src_y[x][0] + src_y[x][0] + src_y[x][0] == 0)
				continue;
			dst_y[x] = src_y[x];
		}
	}
	return dst_image;
}

/*
* SharpenImage関数
* 回転画像等の周りを黒いピクセルで埋められた画像において、黒い部分と本来の画像の曖昧な部分を削りとる関数
* 引数
* cv::Mat src_image
* 削りとる画像
* 返り値
* 削り取られた画像
*/
cv::Mat SharpenImage(cv::Mat src_image, int  *width) {
	cv::Vec3b *src_y;
	int start_x, start_y, end_x, end_y;
	start_x = start_y = end_x = end_y = 0;

	for (int y = 0; y < src_image.rows; y++) {
		src_y = src_image.ptr<cv::Vec3b>(y);
		for (int x = 0; x < src_image.cols; x++) {
			if (src_y[x][0] + src_y[x][1] + src_y[x][2]) {
				start_x = x;
				start_y = y;
			}
		}
	}

	for (int y = src_image.rows - 1; y >= 0; y--) {
		src_y = src_image.ptr<cv::Vec3b>(y);
		for (int x = src_image.cols - 1; x >= 0; x--) {
			if (src_y[x][0] + src_y[x][1] + src_y[x][2]) {
				end_x = x;
				end_y = y;
			}
		}
	}

	cv::line(src_image, cv::Point(start_x, start_y), cv::Point(end_x, start_y), cv::Scalar(0, 0, 0), 5, 2);
	cv::line(src_image, cv::Point(end_x, start_y), cv::Point(end_x, end_y), cv::Scalar(0, 0, 0), 5, 2);
	cv::line(src_image, cv::Point(end_x, end_y), cv::Point(start_x, end_y), cv::Scalar(0, 0, 0), 5, 2);
	cv::line(src_image, cv::Point(start_x, end_y), cv::Point(start_x, start_y), cv::Scalar(0, 0, 0), 5, 2);

	*width = std::abs(end_x - start_x);

	return src_image.clone();
}


cv::Mat YuriInpainting(cv::Mat image, cv::Rect rect) {
	cv::Mat mask(image.size(), CV_8UC1, cv::Scalar::all(0));
	mask(rect).setTo(cv::Scalar::all(255));
	cv::Mat result = image.clone();
	cv::inpaint(image, mask, result, 10, CV_INPAINT_NS);
	return result;
}
