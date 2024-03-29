#include "Core/RaycastPCH.h"
#include "Map.h"

#include "Renderer/Renderer.h"

void Map::setMap(const std::string& filepath)
{
	loadMap(filepath);
}

std::shared_ptr<Sprite>& Map::getSprite(char symbol)
{
	if (m_SymbolCache.find(symbol) == m_SymbolCache.end())
	{
		auto it = std::find_if(m_Elements.begin(), m_Elements.end(), [&](const MapElement& elem) -> bool {
			return (elem.Symbol == symbol); }
		);

		if (it != m_Elements.end())
		{
			m_SymbolCache[symbol] = it->Sprite;
			return it->Sprite;
		}
	}
	return m_SymbolCache[symbol];
}

std::shared_ptr<Sprite>& Map::getSprite(int x, int y)
{
	return getSprite(m_Buffer[y * m_Width + x]);
}

void Map::loadMap(const std::string& filepath)
{
	m_Elements.clear();
	m_SymbolCache.clear();
	std::ifstream stream(filepath);

	m_Buffer[0] = '\0';

	std::string line;
	while (std::getline(stream, line))
	{
		if (line[0] == 'm')
			strcat_s(m_Buffer, std::string(line.begin() + 2, line.end()).c_str());

		if (line[0] == 'w')
			m_Width = std::atoi(std::string(line.begin() + 2, line.end()).c_str());

		if (line[0] == 'h')
			m_Height = std::atoi(std::string(line.begin() + 2, line.end()).c_str());

		else if (line[0] == 's' || line[0] == 'f')
		{
			std::string m_Filepath = "Resources/" + std::string(line.begin() + 4, line.end());
			char Symbol = line[2];
			std::shared_ptr<Sprite> sprite = SpriteManager::loadSprite(m_Filepath);
			bool isWall;
			if (line[0] == 's')
				isWall = true;
			else isWall = false;

			MapElement newElem;
			newElem.isWall = isWall;
			newElem.Sprite = sprite;
			newElem.Symbol = Symbol;

			m_Elements.push_back(newElem);
		}
	}
	stream.close();
}

void Map::Draw(float x, float y, float sizex, float sizey)
{
	float posY = y + sizey * m_Height;
	for (uint i = 0; i < m_Height; i++)
	{
		float posX = x;
		for (uint j = 0; j < m_Width; j++)
		{
			for (const auto& elem : getElements())
				if (m_Buffer[i * m_Width + j] == elem.Symbol && elem.isWall)
					Renderer::drawQuad({ posX, posY }, { sizex, sizey }, 0x00000000);

			if (j == (int)m_PlayerPos.x && i == (int)m_PlayerPos.y)
				Renderer::drawQuad({ posX, posY }, { sizex, sizey }, 0x000000ff);

			posX += sizex;
		}
		posY -= sizey;
	}
}

void Map::updatePlayerPosition(const vec2& pos)
{
	m_PlayerPos = pos;
}
