#include "Core/RaycastPCH.h"
#include "Map.h"

char Map::m_Map[50 * 50];

uint Map::m_Width;
uint Map::m_Height;

void Map::setMap(const std::string& filepath, const std::string& mapname)
{
	loadMap(filepath, mapname);
}

std::shared_ptr<Map> Map::Get()
{
	static std::shared_ptr<Map> map;
	return map;
}

void Map::loadMap(const std::string& filepath, const std::string& mapname)
{
	std::ifstream stream(filepath.c_str());

	std::string mapStr;

	m_Map[0] = '\0';

	bool mapFound = false;
	std::string line;
	while (std::getline(stream, line))
	{
		if (line.find('[') != std::string::npos && mapFound == true)
			stream.close();

		if (line.find(mapname) != std::string::npos)
			mapFound = true;

		if (mapFound == true)
		{
			if (line.find('m') != std::string::npos)
			{
				strcat_s(m_Map, std::string(line.begin() + 2, line.end()).c_str());
			}

			if (line.find('w') != std::string::npos)
			{
				m_Width = std::atoi(std::string(line.begin() + 2, line.end()).c_str());
				break;
			}

			if (line.find('h') != std::string::npos)
				m_Height = std::atoi(std::string(line.begin() + 2, line.end()).c_str());
		}
	}

}
