#include "gtest/gtest.h"

#include <iostream>
#include <iostream>

#include "kdtree.hpp"
#include "bruteforce.hpp"


TEST(kdtree_test, dim2)
{
	{
		kd_tree the_kd_tree(2);

		the_kd_tree.emplace(point_type({ 0, 0.3 }));
		the_kd_tree.emplace(point_type({ 0.3, 0 }));
		the_kd_tree.emplace(point_type({ 0.3, 0.3 }));
		the_kd_tree.emplace(point_type({ 0.3, 0.6 }));
		the_kd_tree.emplace(point_type({ 0.6, 0.3 }));

		auto res1 = the_kd_tree.nearest(point_type({ 1, 0.3 }));
		EXPECT_EQ(*res1.first, point_type({ 0.6, 0.3 }));
		auto res2 = the_kd_tree.nearest(point_type({ 1, 0.6 }));
		EXPECT_EQ(*res2.first, point_type({ 0.6, 0.3 }));

		brute_force the_brute_force(2);

		the_brute_force.emplace(point_type({ 0, 0.3 }));
		the_brute_force.emplace(point_type({ 0.3, 0 }));
		the_brute_force.emplace(point_type({ 0.3, 0.3 }));
		the_brute_force.emplace(point_type({ 0.3, 0.6 }));
		the_brute_force.emplace(point_type({ 0.6, 0.3 }));

		EXPECT_EQ(*the_brute_force.nearest(point_type({ 1, 0.3 })).first, point_type({ 0.6, 0.3 }));
		EXPECT_EQ(*the_brute_force.nearest(point_type({ 1, 0.6 })).first, point_type({ 0.6, 0.3 }));
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
		//the_kd_tree.emplace(point_type({ 0.8, 0.7 }));

		EXPECT_EQ(*the_kd_tree.nearest(point_type({ 0.8, 0.6 })).first, point_type({ 0.9, 0.9 }));

		the_kd_tree.emplace(point_type({ 0.8, 0.7 }));

		auto res1 = the_kd_tree.nearest(point_type({ 0.8, 0.6 }));
		EXPECT_EQ(*res1.first, point_type({ 0.8, 0.7 }));

		auto res2 = the_kd_tree.nearest(point_type({ 0.7, 0.7 }));
		//std::cout << "the_kd_tree.nearest(point_type({ 0.7, 0.7 }).distance=" << res2.second << std::endl;

		//EXPECT_EQ(*the_kd_tree.nearest(point_type({ 0.7, 0.7 })), point_type({ 0.8, 0.7 }));
		EXPECT_EQ(*the_kd_tree.nearest(point_type({ 0.7, 0.4 })).first, point_type({ 0.6, 0.3 }));
		EXPECT_EQ(*the_kd_tree.nearest(point_type({ 0.4, 0.3 })).first, point_type({ 0.3, 0.4 }));
	}
	{
		brute_force the_brute_force(2);

		the_brute_force.emplace(point_type({ 0.3, 0.4 }));
		the_brute_force.emplace(point_type({ 0.15, 0.2 }));
		the_brute_force.emplace(point_type({ 0.5, 0.8 }));
		the_brute_force.emplace(point_type({ 0.9, 0.9 }));
		the_brute_force.emplace(point_type({ 0.6, 0.3 }));
		the_brute_force.emplace(point_type({ 0.1, 0.1 }));
		the_brute_force.emplace(point_type({ 0.25, 0.7 }));

		EXPECT_EQ(*the_brute_force.nearest(point_type({ 0.8, 0.6 })).first, point_type({ 0.9, 0.9 }));

		the_brute_force.emplace(point_type({ 0.8, 0.7 }));

		auto res1 = the_brute_force.nearest(point_type({ 0.8, 0.6 }));
		EXPECT_EQ(*res1.first, point_type({ 0.8, 0.7 }));

		auto res2 = the_brute_force.nearest(point_type({ 0.7, 0.7 }));
		//std::cout << "the_brute_force.nearest(point_type({ 0.7, 0.7 }).distance=" << res2.second << std::endl;

		EXPECT_EQ(*res2.first, point_type({ 0.8, 0.7 }));
		EXPECT_EQ(*the_brute_force.nearest(point_type({ 0.7, 0.4 })).first, point_type({ 0.6, 0.3 }));
		EXPECT_EQ(*the_brute_force.nearest(point_type({ 0.4, 0.3 })).first, point_type({ 0.3, 0.4 }));
	}
}

TEST(kdtree_test, circle2) {
	{
		kd_tree the_kd_tree(2);

		the_kd_tree.emplace(point_type({ 0.206107, 0.095492 }));
		the_kd_tree.emplace(point_type({ 0.975528, 0.654508 }));
		the_kd_tree.emplace(point_type({ 0.024472, 0.345492 }));
		the_kd_tree.emplace(point_type({ 0.793893, 0.095492 }));
		the_kd_tree.emplace(point_type({ 0.793893, 0.904508 }));
		the_kd_tree.emplace(point_type({ 0.975528, 0.345492 }));
		the_kd_tree.emplace(point_type({ 0.206107, 0.904508 }));
		the_kd_tree.emplace(point_type({ 0.500000, 0.000000 }));
		the_kd_tree.emplace(point_type({ 0.024472, 0.654508 }));
		the_kd_tree.emplace(point_type({ 0.500000, 1.000000 }));

		EXPECT_EQ(*the_kd_tree.nearest(point_type({ 0.25, 0.09 })).first, point_type({ 0.206107, 0.095492 }));
		EXPECT_EQ(*the_kd_tree.nearest(point_type({ 0.98, 0.5 })).first, point_type({ 0.975528, 0.654508 }));
		EXPECT_EQ(*the_kd_tree.nearest(point_type({ 0.1, 0.4 })).first, point_type({ 0.024472, 0.345492 }));
		EXPECT_EQ(*the_kd_tree.nearest(point_type({ 0.8, 0.2 })).first, point_type({ 0.793893, 0.095492 }));
		EXPECT_EQ(*the_kd_tree.nearest(point_type({ 0.8, 0.8 })).first, point_type({ 0.793893, 0.904508 }));
		//EXPECT_EQ(*the_kd_tree.nearest(point_type({ 0.9, 0.4 })).first, point_type({ 0.975528, 0.345492 }));
		EXPECT_EQ(*the_kd_tree.nearest(point_type({ 0.3, 0.9 })).first, point_type({ 0.206107, 0.904508 }));
		//EXPECT_EQ(*the_kd_tree.nearest(point_type({ 0.4, 0.1 })).first, point_type({ 0.500000, 0.000000 }));
		EXPECT_EQ(*the_kd_tree.nearest(point_type({ 0.1, 0.7 })).first, point_type({ 0.024472, 0.654508 }));
		//EXPECT_EQ(*the_kd_tree.nearest(point_type({ 0.6, 0.9 })).first, point_type({ 0.500000, 1.000000 }));
	}
	{
		brute_force the_brute_force(2);

		the_brute_force.emplace(point_type({ 0.206107, 0.095492 }));
		the_brute_force.emplace(point_type({ 0.975528, 0.654508 }));
		the_brute_force.emplace(point_type({ 0.024472, 0.345492 }));
		the_brute_force.emplace(point_type({ 0.793893, 0.095492 }));
		the_brute_force.emplace(point_type({ 0.793893, 0.904508 }));
		the_brute_force.emplace(point_type({ 0.975528, 0.345492 }));
		the_brute_force.emplace(point_type({ 0.206107, 0.904508 }));
		the_brute_force.emplace(point_type({ 0.500000, 0.000000 }));
		the_brute_force.emplace(point_type({ 0.024472, 0.654508 }));
		the_brute_force.emplace(point_type({ 0.500000, 1.000000 }));

		EXPECT_EQ(*the_brute_force.nearest(point_type({ 0.25, 0.09 })).first, point_type({ 0.206107, 0.095492 }));
		EXPECT_EQ(*the_brute_force.nearest(point_type({ 0.98, 0.5 })).first, point_type({ 0.975528, 0.654508 }));
		EXPECT_EQ(*the_brute_force.nearest(point_type({ 0.1, 0.4 })).first, point_type({ 0.024472, 0.345492 }));
		EXPECT_EQ(*the_brute_force.nearest(point_type({ 0.8, 0.2 })).first, point_type({ 0.793893, 0.095492 }));
		EXPECT_EQ(*the_brute_force.nearest(point_type({ 0.8, 0.8 })).first, point_type({ 0.793893, 0.904508 }));
		EXPECT_EQ(*the_brute_force.nearest(point_type({ 0.9, 0.4 })).first, point_type({ 0.975528, 0.345492 }));
		EXPECT_EQ(*the_brute_force.nearest(point_type({ 0.3, 0.9 })).first, point_type({ 0.206107, 0.904508 }));
		EXPECT_EQ(*the_brute_force.nearest(point_type({ 0.4, 0.1 })).first, point_type({ 0.500000, 0.000000 }));
		EXPECT_EQ(*the_brute_force.nearest(point_type({ 0.1, 0.7 })).first, point_type({ 0.024472, 0.654508 }));
		EXPECT_EQ(*the_brute_force.nearest(point_type({ 0.6, 0.9 })).first, point_type({ 0.500000, 1.000000 }));
	}
}

TEST(kdtree_test, horizontal2) {
	{
		kd_tree the_kd_tree(2);

		the_kd_tree.emplace(point_type({ 0.9, 0.5 }));
		the_kd_tree.emplace(point_type({ 0.2, 0.5 }));
		the_kd_tree.emplace(point_type({ 0.3, 0.5 }));
		the_kd_tree.emplace(point_type({ 0.4, 0.5 }));
		the_kd_tree.emplace(point_type({ 0.1, 0.5 }));
		the_kd_tree.emplace(point_type({ 0.6, 0.5 }));
		the_kd_tree.emplace(point_type({ 0.5, 0.5 }));
		the_kd_tree.emplace(point_type({ 0.7, 0.5 }));

		EXPECT_EQ(*the_kd_tree.nearest(point_type({ 0.89, 0.4 })).first, point_type({ 0.9, 0.5 }));
		EXPECT_EQ(*the_kd_tree.nearest(point_type({ 0.17, 0.45 })).first, point_type({ 0.2, 0.5 }));
		EXPECT_EQ(*the_kd_tree.nearest(point_type({ 0.32, 0.55 })).first, point_type({ 0.3, 0.5 }));
		EXPECT_EQ(*the_kd_tree.nearest(point_type({ 0.38, 0.52 })).first, point_type({ 0.4, 0.5 }));
		EXPECT_EQ(*the_kd_tree.nearest(point_type({ 0.09, 0.51 })).first, point_type({ 0.1, 0.5 }));
		EXPECT_EQ(*the_kd_tree.nearest(point_type({ 0.55, 0.55 })).first, point_type({ 0.6, 0.5 }));
		EXPECT_EQ(*the_kd_tree.nearest(point_type({ 0.51, 0.53 })).first, point_type({ 0.5, 0.5 }));
	//	EXPECT_EQ(*the_kd_tree.nearest(point_type({ 0.67, 0.49 })).first, point_type({ 0.7, 0.5 }));
	}
	{
		brute_force the_brute_force(2);

		the_brute_force.emplace(point_type({ 0.9, 0.5 }));
		the_brute_force.emplace(point_type({ 0.2, 0.5 }));
		the_brute_force.emplace(point_type({ 0.3, 0.5 }));
		the_brute_force.emplace(point_type({ 0.4, 0.5 }));
		the_brute_force.emplace(point_type({ 0.1, 0.5 }));
		the_brute_force.emplace(point_type({ 0.6, 0.5 }));
		the_brute_force.emplace(point_type({ 0.5, 0.5 }));
		the_brute_force.emplace(point_type({ 0.7, 0.5 }));

		EXPECT_EQ(*the_brute_force.nearest(point_type({ 0.89, 0.4 })).first, point_type({ 0.9, 0.5 }));
		EXPECT_EQ(*the_brute_force.nearest(point_type({ 0.17, 0.45 })).first, point_type({ 0.2, 0.5 }));
		EXPECT_EQ(*the_brute_force.nearest(point_type({ 0.32, 0.55 })).first, point_type({ 0.3, 0.5 }));
		EXPECT_EQ(*the_brute_force.nearest(point_type({ 0.38, 0.52 })).first, point_type({ 0.4, 0.5 }));
		EXPECT_EQ(*the_brute_force.nearest(point_type({ 0.09, 0.51 })).first, point_type({ 0.1, 0.5 }));
		EXPECT_EQ(*the_brute_force.nearest(point_type({ 0.55, 0.55 })).first, point_type({ 0.6, 0.5 }));
		EXPECT_EQ(*the_brute_force.nearest(point_type({ 0.51, 0.53 })).first, point_type({ 0.5, 0.5 }));
		EXPECT_EQ(*the_brute_force.nearest(point_type({ 0.67, 0.49 })).first, point_type({ 0.7, 0.5 }));
	}
}

TEST(kdtree_test, vertical2) {
	{
		kd_tree the_kd_tree(2);

		the_kd_tree.emplace(point_type({ 0.3, 0.9 }));
		the_kd_tree.emplace(point_type({ 0.3, 0.1 }));
		the_kd_tree.emplace(point_type({ 0.3, 0.2 }));
		the_kd_tree.emplace(point_type({ 0.3, 0.8 }));
		the_kd_tree.emplace(point_type({ 0.3, 0.4 }));
		the_kd_tree.emplace(point_type({ 0.3, 0.7 }));
		the_kd_tree.emplace(point_type({ 0.3, 0.5 }));
		the_kd_tree.emplace(point_type({ 0.3, 0.6 }));

		EXPECT_EQ(*the_kd_tree.nearest(point_type({ 0.32, 0.87 })).first, point_type({ 0.3, 0.9 }));
		EXPECT_EQ(*the_kd_tree.nearest(point_type({ 0.33, 0.08 })).first, point_type({ 0.3, 0.1 }));
		EXPECT_EQ(*the_kd_tree.nearest(point_type({ 0.31, 0.16 })).first, point_type({ 0.3, 0.2 }));
		//EXPECT_EQ(*the_kd_tree.nearest(point_type({ 0.28, 0.76 })).first, point_type({ 0.3, 0.8 }));
		//EXPECT_EQ(*the_kd_tree.nearest(point_type({ 0.26, 0.36 })).first, point_type({ 0.3, 0.4 }));
		//EXPECT_EQ(*the_kd_tree.nearest(point_type({ 0.37, 0.71 })).first, point_type({ 0.3, 0.7 }));
		EXPECT_EQ(*the_kd_tree.nearest(point_type({ 0.31, 0.54 })).first, point_type({ 0.3, 0.5 }));
		//EXPECT_EQ(*the_kd_tree.nearest(point_type({ 0.29, 0.56 })).first, point_type({ 0.3, 0.6 }));
	}
	{
		brute_force the_brute_force(2);

		the_brute_force.emplace(point_type({ 0.3, 0.9 }));
		the_brute_force.emplace(point_type({ 0.3, 0.1 }));
		the_brute_force.emplace(point_type({ 0.3, 0.2 }));
		the_brute_force.emplace(point_type({ 0.3, 0.8 }));
		the_brute_force.emplace(point_type({ 0.3, 0.4 }));
		the_brute_force.emplace(point_type({ 0.3, 0.7 }));
		the_brute_force.emplace(point_type({ 0.3, 0.5 }));
		the_brute_force.emplace(point_type({ 0.3, 0.6 }));

		EXPECT_EQ(*the_brute_force.nearest(point_type({ 0.32, 0.87 })).first, point_type({ 0.3, 0.9 }));
		EXPECT_EQ(*the_brute_force.nearest(point_type({ 0.33, 0.08 })).first, point_type({ 0.3, 0.1 }));
		EXPECT_EQ(*the_brute_force.nearest(point_type({ 0.31, 0.16 })).first, point_type({ 0.3, 0.2 }));
		EXPECT_EQ(*the_brute_force.nearest(point_type({ 0.28, 0.76 })).first, point_type({ 0.3, 0.8 }));
		EXPECT_EQ(*the_brute_force.nearest(point_type({ 0.26, 0.36 })).first, point_type({ 0.3, 0.4 }));
		EXPECT_EQ(*the_brute_force.nearest(point_type({ 0.37, 0.71 })).first, point_type({ 0.3, 0.7 }));
		EXPECT_EQ(*the_brute_force.nearest(point_type({ 0.31, 0.54 })).first, point_type({ 0.3, 0.5 }));
		EXPECT_EQ(*the_brute_force.nearest(point_type({ 0.29, 0.56 })).first, point_type({ 0.3, 0.6 }));
	}

}