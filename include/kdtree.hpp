#pragma once

#include <stack>
#include <memory>
#include <functional>
#include <cmath>
#include <assert.h>

#include "point_type.hpp"


class kd_tree {
private:

	struct kd_tree_node {
		point_type point;
		int index;
		std::unique_ptr<kd_tree_node> left;
		std::unique_ptr<kd_tree_node> right;

		kd_tree_node(point_type&& point, int index) : point(std::move(point)), index(index) {}
	};

	std::unique_ptr<kd_tree_node> root;
	size_t dimension;

public:
	kd_tree(const sample_type& sample, size_t dimension) : dimension(dimension) {
		for (auto& point : sample) {
			if (point.size() != dimension)
				throw std::runtime_error("The input point dimension does not match kd_tree dimension");
			insert(point);
		}
	}

	kd_tree(size_t dimention) : kd_tree(sample_type(), dimention) {}

	void insert(const point_type& point) {
		emplace(point_type(point));
	}

	void emplace(point_type&& point) {
		if (point.size() != dimension)
			throw std::runtime_error("The input point dimension does not match kd_tree dimension");
		
		if (!root) {
			root = std::make_unique<kd_tree_node>(std::move(point), 0);
		}
		else {
			kd_tree_node* node = root.get();
			for (int i = 1; ; ++i) {
				int index = i % dimension;
				if (less_at(point, node->point, node->index)) {
					if (!node->left) {
						node->left = std::make_unique<kd_tree_node>(std::move(point), index);
						break;
					}
					else {
						node = node->left.get();
					}
				}
				else {
					if (!node->right) {
						node->right = std::make_unique<kd_tree_node>(std::move(point), index);
						break;
					}
					else {
						node = node->right.get();
					}
				}
			}
		}
	}

	std::pair<const point_type*, double> nearest(const point_type& point) const {
		if (point.size() != dimension)
			throw std::runtime_error("The input point dimension does not match kd_tree dimension");

		std::stack<const kd_tree_node*> nodes;
		nodes.push(root.get());

		double nearest_distance = .0;
		const point_type* nearest_point = nullptr;

		while(!nodes.empty()) {

			const kd_tree_node* node = nodes.top();
			nodes.pop();

			auto dist = distance_squared(point, node->point);
			if (!nearest_point || dist < nearest_distance) {
				nearest_distance = dist;
				nearest_point = &(node->point);
			}

			bool on_the_left = less_at(point, node->point, node->index);

			const kd_tree_node* left_node = node->left.get();
			if (left_node) {
				point_type current_point(left_node->point); 
				if (on_the_left) {
					current_point.at(left_node->index) = point.at(left_node->index);
				}
				else {
					current_point.at(node->index) = node->point.at(node->index);
				}
				if (distance_squared(point, current_point) <= nearest_distance)
					nodes.push(left_node);
			}
			
			const kd_tree_node* right_node = node->right.get();
			if (right_node) {
				point_type current_point(right_node->point);
				if (!on_the_left) {
					current_point.at(right_node->index) = point.at(right_node->index);
				}
				else {
					current_point.at(node->index) = node->point.at(node->index);
				}
				if (distance_squared(point, current_point) <= nearest_distance)
					nodes.push(right_node);
			}
		}
		return { nearest_point, nearest_distance };
	}
};