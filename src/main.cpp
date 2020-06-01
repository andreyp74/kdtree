
#include <assert.h>
#include <iostream>

#include "kdtree.hpp"


int main() {

	{
		kd_tree the_kd_tree(2);

		the_kd_tree.emplace(point_type({ 0, 0.3 }));
		the_kd_tree.emplace(point_type({ 0.3, 0 }));
		the_kd_tree.emplace(point_type({ 0.3, 0.3 }));
		the_kd_tree.emplace(point_type({ 0.3, 0.6 }));

		std::cout << "nearest(point_type({ 1, 0.3 })) == " << the_kd_tree.nearest(point_type({ 1, 0.3 })); //point_type({ 0.6, 0.3 })
		std::cout << "nearest(point_type({ 1, 0.6 })) == " << the_kd_tree.nearest(point_type({ 1, 0.6 })); //point_type({ 0.6, 0.3 })
	}
	{
		kd_tree the_kd_tree(2);

		the_kd_tree.emplace(point_type({ 0.3, 0.4 }));
		the_kd_tree.emplace(point_type({ 0.15, 0.2 }));
		the_kd_tree.emplace(point_type({ 0.5, 0.8 }));
		the_kd_tree.emplace(point_type({ 0.9, 0.9 }));
		the_kd_tree.emplace(point_type({ 0.6, 0.3 }));
		the_kd_tree.emplace(point_type({ 0.1, 0.1 }));
		the_kd_tree.emplace(point_type({ 0.25, 0.7 }));

		std::cout << "nearest(point_type({ 0.8, 0.6 })) == " << the_kd_tree.nearest(point_type({ 0.8, 0.6 }));
	}

	return 0;
}