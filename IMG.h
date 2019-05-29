#pragma once
#include "lodepng.h"
#include <vector>
#include <iostream>
#include <thread>
#include "gif.h"

using namespace std;

class IMG
{
public:
	IMG(const char* output_file, unsigned _height, unsigned _width);
	~IMG();
	unsigned height;
	unsigned width;
	const char* output_filename;
	vector<unsigned char> buffer;
	void encodeOneStep();

};

