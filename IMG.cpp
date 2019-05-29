#include "IMG.h"

IMG::IMG(const char* output_file, unsigned _width, unsigned _height) :
	output_filename(output_file), height(_height), width(_width)
{
	for(int i = 0; i < height*width; i++)
	{
		buffer.push_back(0);
		buffer.push_back(0);
		buffer.push_back(0);
		buffer.push_back(255);
	}
	cout << buffer.size() << endl;
}

IMG::~IMG(){}

void IMG::encodeOneStep()
{
	cout << "Lengde paa imagevector til encoding: " << buffer.size() << endl;
	//Encode the image
	unsigned error = lodepng::encode(output_filename, buffer, width, height);
	
	//if there's an error, display it
	if (error) std::cout << "encoder error " << error << ": " << lodepng_error_text(error) << std::endl;
}