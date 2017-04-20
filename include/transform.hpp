#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include <opencv2/opencv.hpp>

cv::Mat PerspectiveTransform(cv::Mat image, cv::Point2f *points, cv::Size dst_size);
cv::Mat RotationTransform(cv::Mat image, double angle);
cv::Mat CutImage(cv::Mat image, cv::Rect rect);
cv::Mat PasteImage(cv::Mat dst_image, cv::Mat src_image, int x, int y);
cv::Mat BlackPixelMakeClearness(cv::Mat image);
cv::Mat YuriFacePasteImage(cv::Mat dst_image, cv::Mat src_image, int x, int y);
cv::Mat SharpenImage(cv::Mat src_image, int  *width);
cv::Mat YuriInpainting(cv::Mat image, cv::Rect rect);

#endif
