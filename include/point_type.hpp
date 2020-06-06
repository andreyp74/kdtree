#pragma once

#include <vector>

using point_type = std::vector<double>;
using sample_type = std::vector<point_type>;

inline bool less_at(const point_type& p1, const point_type& p2, int idx) {
	return p1.at(idx) < p2.at(idx);
}

inline double distance_squared(const point_type& p1, const point_type& p2) {
	assert(p1.size() == p2.size());

	double distance = .0;
	for (size_t i = 0; i < p1.size(); ++i) {
		distance += pow(p1.at(i) - p2.at(i), 2);
	}
	return distance;
}