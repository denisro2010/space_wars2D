#include "stdafx.h"
#include "AnimatedSprite.h"
#include "../3rd-party/SOIL/src/SOIL.h"
#include <string>

AnimatedSprite::AnimatedSprite(const char* textureFilename, int numSubImagesX, int numSubImagesY, bool loop)
:Sprite(string(""))
{
	int width, height, nChannels;
	unsigned char* pImage= SOIL_load_image(textureFilename, &width, &height, &nChannels, 0);
	if (pImage)
	{
		int numImageBytes = width * height*nChannels;
		char* pDstBuffer = new char[numImageBytes];

		int subImageSizeX = width / numSubImagesX;
		int subImageSizeY = height / numSubImagesY;

		int numSubImages = numSubImagesX * numSubImagesY;
		int numSubImageRows = numSubImages * subImageSizeY;
		int subImageX, subImageY;
		int srcOffsetInBytes = 0, dstOffsetInBytes;
		int dstSubImageIndex;
		int numBytesPerSubImage = nChannels * subImageSizeX * subImageSizeY;
		int numBytesPerSubImageRow = nChannels * subImageSizeX;
		int numSubImageRowsPerImageRow = subImageSizeY*numSubImagesX;

		for (int subImageRow = 0; subImageRow < numSubImageRows; subImageRow++)
		{

			subImageY = subImageRow / numSubImageRowsPerImageRow;
			subImageX = (subImageRow % numSubImageRowsPerImageRow) % numSubImagesX;

			//dstSubImageIndex = subImageY * numSubImagesX + subImageX;
			dstOffsetInBytes= (subImageY*numSubImagesX + subImageX) * numBytesPerSubImage 
				+ ((subImageRow%numSubImageRowsPerImageRow) / numSubImagesX)* numBytesPerSubImageRow;

			memcpy_s(&pDstBuffer[dstOffsetInBytes],numImageBytes-dstOffsetInBytes,&pImage[srcOffsetInBytes]
				,numBytesPerSubImageRow);

			srcOffsetInBytes += numBytesPerSubImageRow;
		}

		glEnable(GL_TEXTURE_3D);
		glGenTextures(1, &m_textureId);
		glBindTexture(GL_TEXTURE_3D, m_textureId);
		glTexImage3D(GL_TEXTURE_3D, 0, GL_RGBA, subImageSizeX, subImageSizeY, numSubImages, 0
			, GL_RGBA, GL_UNSIGNED_BYTE, pDstBuffer);

		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		if (!loop)
			glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		else
			glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_REPEAT);

		glTexEnvi(GL_TEXTURE_3D, GL_TEXTURE_ENV_MODE, GL_DECAL);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glDisable(GL_TEXTURE_3D); //disable 3d textures and enable 2d textures
		//glEnable(GL_TEXTURE_2D);
		delete [] pDstBuffer;
		delete [] pImage;
	}
}


AnimatedSprite::~AnimatedSprite()
{
	glDeleteTextures(1, &m_textureId);
}



void AnimatedSprite::draw()
{
	//0. Calculate what point of the animation [0,1] to show this frame
	animationPoint += 0.0013;

	//2. Save the current transformation matrix
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	//3. Set the transformation matrix of the quad using position, size and angle
	glTranslated(m_x, m_y, 0.0);
	glRotated(m_angle, 0.0, 0.0, 1.0);
	glScaled(m_size, m_size, 1.0);

	//4. Draw the quad centered in [0,0] with coordinates: [-1,-1], [1,-1], [1,1] and [-1,1]
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D); //disable 2d textures and enable 3d textures
	glEnable(GL_TEXTURE_3D);
	glBindTexture(GL_TEXTURE_3D, m_textureId);

	glBegin(GL_QUADS);
	glTexCoord3d(0.0, 1.0, animationPoint);
	glVertex3d(-1.0, -1.0, -m_depth);
	glTexCoord3d(1.0, 1.0, animationPoint);
	glVertex3d(1.0, -1.0, -m_depth);
	glTexCoord3d(1.0, 0.0, animationPoint);
	glVertex3d(1.0, 1.0, -m_depth);
	glTexCoord3d(0.0, 0.0, animationPoint);
	glVertex3d(-1.0, 1.0, -m_depth);
	glEnd();

	//5. Restore the transformation matrix
	glPopMatrix();
	glDisable(GL_TEXTURE_3D); //disable 3d textures and enable 2d textures
	glEnable(GL_TEXTURE_2D);
}