#pragma once
#include <vector>
#include <array>


template<typename T>
struct Grid
{

	int32_t width, height;
	std::vector<T> data;

	Grid()
		: width(0)
		, height(0)
	{}

	Grid(int32_t width_, int32_t height_)
		: width(width_)
		, height(height_)
	{
		data.resize(width * height);
	}
};
