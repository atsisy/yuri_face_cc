#include "../include/init.hpp"
#include "../include/dot.hpp"
#include "../include/object.hpp"
#include <vector>

ring_type CreateRing(Object *object) {
	ring_type ring;
	for (Dot *dot : *object->getDotsVector()) {
		ring.push_back(point(dot->getX(), dot->getY()));
	}
	return ring;
}

box CreateEnvelope(ring_type ring) {
	box envelope;
	bg::envelope(ring, envelope);
	return envelope;
}

cv::Rect BoostBox2CvRect(box boost_box) {
	return cv::Rect(
		boost_box.min_corner().x(),
		boost_box.min_corner().y(),
		boost_box.max_corner().x() - boost_box.min_corner().x(),
		boost_box.max_corner().y() - boost_box.min_corner().y()
	);
}
