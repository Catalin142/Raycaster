#include "Core/RaycastPCH.h"
#include "Sprite.h"

#include "Utils/Color.h"

Sprite::Sprite(const std::string& filepath): m_Filepath(filepath)
{
	assert(loadSprite(filepath));
}

bool Sprite::loadSprite(const std::string& filepath)
{
	std::ifstream readFile(m_Filepath.c_str(), std::ios::in | std::ios::binary);
	std::string extension = std::string(m_Filepath.begin() + m_Filepath.find_last_of(".") + 1, m_Filepath.end());

	if (!readFile.good())
		return false;

	if (extension != "spr")
		return false;

	readFile.read((char*)&m_Width, sizeof(m_Width));
	readFile.read((char*)&m_Height, sizeof(m_Height));

	if (m_Buffer != nullptr)
		delete[] m_Buffer;
	
	m_Buffer = new vec3[m_Width * m_Height];
	long temp = 0;
	for (int i = 0; i < m_Width * m_Height; i++)
	{
		readFile.read((char*)&temp, sizeof(long));
		if (temp != -1)
			m_Buffer[i] = createRGB(temp);
		else m_Buffer[i] = { -1.0f, -1.0f, -1.0f };
	}

	return true;
}

vec3& Sprite::getPixelColor(float x, float y)
{
	if (x < 0) x = -x;
	if (y < 0) y = -y;
	
	float xCoord = x * m_Width;
	float yCoord = y * m_Height;

	return *(m_Buffer + (int)yCoord * m_Width + (int)xCoord);
}
