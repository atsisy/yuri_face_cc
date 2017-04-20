#ifndef INIT_HPP
#define INIT_HPP

#include <opencv2/opencv.hpp>
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <boost/geometry/geometries/box.hpp>
#include <boost/assign/list_of.hpp>

namespace bg = boost::geometry;

typedef bg::model::d2::point_xy<int> point;
typedef bg::model::polygon<point> polygon;
typedef bg::model::box<point> box;
typedef boost::geometry::ring_type<polygon>::type ring_type;

void SleepFor(int mill_sec);
void ShowAndWait(cv::Mat image, std::string window_name, int mill_sec);

#endif
