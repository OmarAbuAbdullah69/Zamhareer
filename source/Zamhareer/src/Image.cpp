#include "ZM/Image.h"
#define STB_IMAGE_IMPLEMENTATION 
#include "ZM/stb_image.h"

#include <cmath>

namespace ZM
{
	Image AlocateImage(int width, int height, Color color)
	{
		unsigned char *img = new unsigned char[width*height*4];
		for(int i=0; i < width*height*4; i+=4)
		{
			unsigned char &Red   = img[i];
			unsigned char &Green = img[i+1];
			unsigned char &Blue  = img[i+2];
			unsigned char &Alpha = img[i+3];
			Red   = std::round(color.R*255);
			Green = std::round(color.G*255);
			Blue  = std::round(color.B*255);
			Alpha = std::round(color.A*255);
		}
		return{
			.Width = width,
			.Height = height,
			.NRC = 4,
			.Data = img
		};
	}
	Image LoadImage(const char * path, int *staterr)
	{
		
		stbi_set_flip_vertically_on_load(true);
		*staterr = 0;
		int width, height, channels;
		unsigned char *img = stbi_load(path, &width, &height, &channels, 0);
		if(!(img))
		{
			*staterr = 1;
			return AlocateImage(256, 256, Color(1, 1, 1, 1));
		}
		unsigned char *data =  new unsigned char[width*height*channels];
		memcpy(data, img, sizeof(unsigned char)*width*height*channels);
		stbi_image_free(img);
		return {
			.Width = width,
			.Height = height,
			.NRC = channels,
			.Data = data
		};
	}
	void DeleteImage(Image i)
	{
		delete i.Data;
	}
}
