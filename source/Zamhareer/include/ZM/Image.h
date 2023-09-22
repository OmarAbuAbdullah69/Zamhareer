#pragma once

namespace ZM
{

	struct Image
	{
		int Width, Height, NRC;
		unsigned char *Data;
	};

	Image LoadImage(const char * path, int *staterr);
	void DeleteImage(Image i);
}
