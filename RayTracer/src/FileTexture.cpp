#include "FileTexture.h"


FileTexture::FileTexture(const string &path)
{
	ilInit();
	imageHandle = ilGenImage();
	ilBindImage(imageHandle);
	ILboolean result = ilLoadImage(path.c_str());

	if (result) {
		width = ilGetInteger(IL_IMAGE_WIDTH);
		height = ilGetInteger(IL_IMAGE_HEIGHT);
		channels = ilGetInteger(IL_IMAGE_CHANNELS);
	}
}


FileTexture::~FileTexture()
{
	ilDeleteImage(imageHandle);
}

const vec3 FileTexture::getTexel(float s, float t, const vec2 &scale) const {
	s *= scale.s;
	t *= scale.t;

	float wrappedS;
	float wrappedT;

	if (s >= 0)
		wrappedS = s - (int)s;
	else
		wrappedS = 1 - (abs(s) - (int)abs(s));

	if (t >= 0)
		wrappedT = t - (int)t;
	else
		wrappedT = 1 - (abs(t) - (int)abs(t));

	//return getTexelFromFile(wrappedS*(width-1), wrappedT*(height-1));
	return bilinearInterpolation(wrappedS, wrappedT);
}

const vec3 FileTexture::bilinearInterpolation(float u, float v) const {
	const float pu = (width-1) * u;
	const float pv = (height-1) * v;
	const int x = (int)pu;
	const int y = (int)pv;
	const float uPrime = pu - x;
	const float vPrime = pv - y;

	const int xl = x - 1 >= 0 ? x - 1 : width - 1;
	const int xr = x + 1 < width ? x + 1 : 0;
	const int yb = y - 1 >= 0 ? y - 1 : height - 1;
	const int yt = y + 1 < height ? y + 1 : 0;

	return (1.0f - uPrime) * (1.0f - vPrime) * getTexelFromFile(xl, yb) +
		uPrime * (1.0f - vPrime) * getTexelFromFile(xr, yb) +
		(1.0f - uPrime) * vPrime * getTexelFromFile(xl, yt) +
		uPrime * vPrime * getTexelFromFile(xr, yt);
}

const vec3 FileTexture::getTexelFromFile(const int x, const int y) const {
	ilBindImage(imageHandle);
	ILubyte *data = ilGetData();
	int basePixel = (x + (((height-1) - y) * width)) * channels;
	return { data[basePixel] / 255.0f, data[basePixel + 1] / 255.0f, data[basePixel + 2] / 255.0f };
}
