#include "ZM/Image.h"
#define STB_IMAGE_IMPLEMENTATION 
#include "ZM/stb_image.h"
namespace ZM
{
	Image LoadImage(const char * path, int *staterr)
	{
	
		stbi_set_flip_vertically_on_load(true);
		*staterr = 0;
		int width, height, channels;
		unsigned char *img = stbi_load(path, &width, &height, &channels, 0);
		if(!(img))
		{
			*staterr = 1;
		}
		return {
			.Width = width,
			.Height = height,
			.NRC = channels,
			.Data = img
		};
	}
	void DeleteImage(Image i)
	{
		stbi_image_free(i.Data);
	}
}
