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
	for (int i = 0; i < p1.size(); ++i) {
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

		kd_tree_node(point_type&& point) : point(std::move(point)) {}

		double distance_squared(const point_type& p) const {
			point_type node_closest_point = p;
			node_closest_point.at(index) = point.at(index);
			return ::distance_squared(node_closest_point, p);
		}
	};

	std::unique_ptr<kd_tree_node> root;
	int dimension;

private:

public:
	kd_tree(const sample_type& sample, int dimension) : dimension(dimension) {
		for (auto& point : sample) {
			if (point.size() != dimension)
				throw std::runtime_error("The input point dimension does not match kd_tree dimension");
			insert(point);
		}
	}

	kd_tree(int dimention) : kd_tree(sample_type(), dimention) {}

	void insert(const point_type& point) {
		emplace(point_type(point));
	}

	void emplace(point_type&& point) {
		if (point.size() != dimension)
			throw std::runtime_error("The input point dimension does not match kd_tree dimension");

		auto new_node = std::make_unique<kd_tree_node>(point);
		kd_tree_node* node = root.get();
		for (kd_tree_node* next = nullptr, int i = 0; next; node = next, ++i) {
			int index = i % dimension;
			if (less_at(point, node->point, index)) {
				next = node->left.get();
				if (!next) {
					new_node->index = index;
					node->left.swap(new_node);
				}
			}
			else {
				next = node->right.get();
				if (!next) {
					new_node->index = index;
					node->right.swap(new_node);
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

			const kd_tree_node* left_node = node->left.get();
			if (left_node && left_node->distance_squared(point) <= closest_dist)
				nodes.push(left_node);

			const kd_tree_node* right_node = node->right.get();
			if (right_node && right_node->distance_squared(point) <= closest_dist)
				nodes.push(right_node);
		}
		return closest_point;
	}
};