#pragma once
#include "Color.h"
namespace ZM
{

	struct Image
	{
		int Width, Height, NRC;
		unsigned char *Data;
	};

	Image AlocateImage(int width, int height, Color color);
	Image LoadImage(const char * path, int *staterr);
	void DeleteImage(Image i);
}
