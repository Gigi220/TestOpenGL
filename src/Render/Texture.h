// 学学学
#pragma once

#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include <string.h>
#include "GL/glew.h"
#include "SOIL2/SOIL2.h"
#include "SOIL2/stb_image.h"

namespace Render
{
	class Texture
	{
	public:
		Texture(const char* fileName)
		{
			glGenTextures(1, &_texture);
			glBindTexture(GL_TEXTURE_2D, _texture);

			// Встановлення режиму врапінга
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			// Встановлення фільрації
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

			// загрузка текстури
			unsigned char* image = stbi_load(fileName, &_width, &_height, &_nrChannels, SOIL_LOAD_RGB);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
			glGenerateMipmap(GL_TEXTURE_2D);
			// очистка 
			stbi_image_free(image);
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		/*static Texture Load(const char* fileName)
		{
			auto&& texture = Texture(fileName);
			return texture;
		}*/

		int GetWidth() const { return _width; }
		int GetHeight() const { return _height; }

		GLuint& GetData() { return _texture; }

	private:
		GLuint _texture;
		int _width;
		int _height;
		int _nrChannels;
	};

}

#endif // !_TEXTURE_H_


