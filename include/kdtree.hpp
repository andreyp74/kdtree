#include <vector>
#include <stack>
#include <memory>
#include <functional>
#include <cmath>
#include <assert.h>

using point_type = std::vector<double>;
using sample_type = std::vector<point_type>;

bool less_at(const point_type& p1, const point_type& p2, int idx) {
	return p1.at(idx) < p2.at(idx);
}

double distance_squared(const point_type& p1, const point_type& p2) {
	assert(p1.size() == p2.size());

	double distance = .0;
	for (size_t i = 0; i < p1.size(); ++i) {
		distance += pow(p1.at(i) - p2.at(i), 2);
	}
	return distance;
}

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

	const point_type* nearest(const point_type& point) const {
		if (point.size() != dimension)
			throw std::runtime_error("The input point dimension does not match kd_tree dimension");

		std::stack<const kd_tree_node*> nodes;
		nodes.push(root.get());

		double closest_dist = .0;
		const point_type* closest_point = nullptr;

		while(!nodes.empty()) {

			const kd_tree_node* node = nodes.top();
			nodes.pop();

			auto dist = distance_squared(point, node->point);
			if (!closest_point || dist < closest_dist) {
				closest_dist = dist;
				closest_point = &(node->point);
			}

			bool on_the_left = less_at(point, node->point, node->index);

			const kd_tree_node* left_node = node->left.get();
			if (left_node) {
				point_type nearest_point(left_node->point); 
				if (on_the_left) {
					nearest_point.at(left_node->index) = point.at(left_node->index);
				}
				else {
					nearest_point.at(node->index) = node->point.at(node->index);
				}
				if (distance_squared(point, nearest_point) <= closest_dist)
					nodes.push(left_node);
			}
			
			const kd_tree_node* right_node = node->right.get();
			if (right_node) {
				point_type nearest_point(right_node->point);
				if (!on_the_left) {
					nearest_point.at(right_node->index) = point.at(right_node->index);
				}
				else {
					nearest_point.at(node->index) = node->point.at(node->index);
				}
				if (distance_squared(point, nearest_point) <= closest_dist)
					nodes.push(right_node);
			}
		}
		return closest_point;
	}
};