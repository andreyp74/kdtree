#pragma once

#include "point_type.hpp"

class brute_force {
private:
	sample_type sample;
	size_t dimension;

public:
	brute_force(const sample_type& sample, size_t dimension) : dimension(dimension) {
		for (auto& point : sample) {
			if (point.size() != dimension)
				throw std::runtime_error("The input point dimension does not match kd_tree dimension");
			insert(point);
		}
	}

	brute_force(size_t dimention) : brute_force(sample_type(), dimention) {}

	void insert(const point_type& point) {
		emplace(point_type(point));
	}

	void emplace(point_type&& point) {
		if (point.size() != dimension)
			throw std::runtime_error("The input point dimension does not match kd_tree dimension");
		sample.emplace_back(std::move(point));
	}

	std::pair<const point_type*, double> nearest(const point_type& point) const {
		if (point.size() != dimension)
			throw std::runtime_error("The input point dimension does not match kd_tree dimension");
		double nearest_distance = 0.0;
		const point_type* nearest_point = nullptr;
		for (const auto& p : sample) {
			double dist = distance_squared(p, point);
			if (!nearest_point || dist < nearest_distance) {
				nearest_distance = dist;
				nearest_point = &p;
			}
		}
		return { nearest_point, nearest_distance };
	}
};