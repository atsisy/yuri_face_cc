#include "../include/transform.hpp"
#include <algorithm>

/*
* PerspectiveTransform�֐�
* �摜�𓧎��ˉe�ϊ����ĕԂ��֐�
* ����
* cv::Mat image
* �����ˉe�ϊ����s���摜
* cv::Point2f *points
* �ǂ�Ȃӂ��ɓ����ˉe�ϊ����s����
* cv::Size dst_size
* ���������摜�̃T�C�Y
* �Ԃ�l
* �������Ŏ󂯎����Mat�̓����ˉe�ϊ����ʂ̉摜
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
* RotationTransform�֐�
* �摜����]�ό`����֐�
* ����
* cv::Mat image
* ��]�ό`������摜
* double angle
* ��]������p�x�i�x���@�Ŏw��j
* �Ԃ�l
* �������Ŏ󂯎����Mat�̉�]�ό`���ʂ̉摜
*/
cv::Mat RotationTransform(cv::Mat image, double angle) {
	//���ʗp
	cv::Mat result;

	//�摜�̒��S���W���擾
	cv::Point2f center(image.cols / 2.0, image.rows / 2.0);
	cv::Mat rot_mat = cv::getRotationMatrix2D(center, angle, 1.0);

	//��`�����肷��
	cv::Rect rect = cv::RotatedRect(center, image.size(), angle).boundingRect();

	//�ϊ��s��𒲐�
	rot_mat.at<double>(0, 2) += rect.width / 2.0 - center.x;
	rot_mat.at<double>(1, 2) += rect.height / 2.0 - center.y;

	cv::warpAffine(image, result, rot_mat, rect.size());

	return result;
}

/*
* CutImage�֐�
* �摜�̎w�肵���͈͂�؂蔲���֐�
* ����
* cv::Mat image
* �؂蔲�����̉摜
* cv::Rect rect
* �؂�o���̈�
* �Ԃ�l
* �؂�o���ꂽcv::Mat
*/
cv::Mat CutImage(cv::Mat image, cv::Rect rect) {
	return cv::Mat(image, rect).clone();
}

/*
* PasteImage�֐�
* �摜��������̉摜�ɓ\��t����֐�
* ����
* cv::Mat dst_image
* �\��t����̉摜
* cv::Mat src_image
* �\��t����摜
* int x
* �������̉摜�̓\��t����X�ʒu
* int y
* �������̉摜�̓\��t����Y�ʒu
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
* BlackPixelMakeClearness�֐�
* �����s�N�Z���𓧉߂���cv::Mat��f���֐�
* ����
* cv::Mat image
* ���߂������摜
* �Ԃ�l
* �����Ŏ󂯎�����摜�ɓ��ߏ������s�����摜
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
* SharpenImage�֐�
* ��]�摜���̎���������s�N�Z���Ŗ��߂�ꂽ�摜�ɂ����āA���������Ɩ{���̉摜�̞B���ȕ��������Ƃ�֐�
* ����
* cv::Mat src_image
* ���Ƃ�摜
* �Ԃ�l
* �����ꂽ�摜
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
