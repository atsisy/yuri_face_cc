#include <thread>
#include <opencv2/opencv.hpp>

void SleepFor(int mill_sec) {
	std::chrono::milliseconds dura(mill_sec);
	std::this_thread::sleep_for(dura);
}

void ShowAndWait(cv::Mat image, std::string window_name, int mill_sec) {
	cv::imshow(window_name, image);
	cv::waitKey(mill_sec);
}
