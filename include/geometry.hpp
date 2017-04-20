#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

#include "init.hpp"

ring_type CreateRing(Object *object);
box CreateEnvelope(ring_type ring);
cv::Rect BoostBox2CvRect(box boost_box);

#endif
