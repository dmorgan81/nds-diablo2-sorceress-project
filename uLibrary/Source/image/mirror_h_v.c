#include "ulib.h"

void ulMirrorImageH(UL_IMAGE *img, int mirrorState)		{
if (mirrorState && img->offsetX1 >= img->offsetX0)
   			{
		//Exchange both coordinates to mirror the image
		int tmpOffset = img->offsetX0;
		img->offsetX0 = img->offsetX1-1;
		img->offsetX1 = tmpOffset-1;
	}
	else if (!mirrorState && img->offsetX1 <= img->offsetX0)
	{
        int tmpOffset = img->offsetX0;
		img->offsetX0 = img->offsetX1+1;
		img->offsetX1 = tmpOffset+1;
	}
}

void ulMirrorImageV(UL_IMAGE *img, int mirrorState)		{
   if (mirrorState && img->offsetY1 >= img->offsetY0)
   			{
		//Exchange both coordinates to mirror the image
		int tmpOffset = img->offsetY0;
		img->offsetY0 = img->offsetY1-1;
		img->offsetY1 = tmpOffset-1;
	}
	else if (!mirrorState && img->offsetY1 <= img->offsetY0)
	{
        int tmpOffset = img->offsetY0;
		img->offsetY0 = img->offsetY1+1;
		img->offsetY1 = tmpOffset+1;
	}
}


