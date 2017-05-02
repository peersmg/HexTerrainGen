#include "TerrainGenerator.h"
#include "ObjectFactory.h"
#include "OutputLog.h"
#include "ResourceLoader.h"
#include "Game.h"
#include "HexMath.h"

#include "CRectShape.h"
#include "DrawManager.h"

GameObject* CreateTerrainGenerator(InitialisationData data)
{
  TerrainGenerator* pTemp = new TerrainGenerator(data);
  return (GameObject*)pTemp;
}

const bool bTerrainGenerator = ObjectFactory::GetInstance().Register("TerrainGenerator", CreateTerrainGenerator);


TerrainGenerator::TerrainGenerator(InitialisationData data)
{
  m_mapWidth = data.floatData["Width"];
  m_mapHeight = data.floatData["Height"];

  m_hexRadius = data.floatData["HexRadius"];
  m_hexInnerRadius = HexMath::GetInnerRadius(m_hexRadius);

  GenerateTerrain(data.floatData["Seed"]);
  GenerateTexture();
}


TerrainGenerator::~TerrainGenerator()
{
}

void TerrainGenerator::Update(float deltaTime)
{
  sf::Sprite mapSprite(m_mapTexture.getTexture());
  Game::instance.GetWindow()->Draw(mapSprite, 0);
}

void TerrainGenerator::GenerateTerrain(int seed)
{
  m_perlinNoise.SetSeed(seed);

  m_perlinNoise.SetFrequency(0.8);        // How jagged the terrain is

  m_perlinNoise.SetLacunarity(1);       // How much extra random bits
  m_perlinNoise.SetPersistence(0.5);

  m_perlinNoise.SetOctaveCount(6);

  float noiseScale = 10;

  for (int y = 0; y < m_mapHeight; y++)
  {
    for (int x = 0; x < m_mapWidth; x++)
    {
      float normalised = (m_perlinNoise.GetValue((float)x / noiseScale, (float)y / noiseScale, 0) + 1) / 2;

      if (normalised > 0.9)
      {
        m_terrain.push_back(4);
      }
      else if (normalised > 0.7)
      {
        m_terrain.push_back(3);
      }
      else if (normalised > 0.5)
      {
        m_terrain.push_back(2);
      }
      else if (normalised > 0.3)
      {
        m_terrain.push_back(1);
      }
      else
      {
        m_terrain.push_back(0);
      }
    }

    if (ResourceLoader::GetInstance().isTextureLoaded("resources/textures/hex.png"))
    {
      m_texture = ResourceLoader::GetInstance().GetTexture("resources/textures/hex.png");
    }
    else
    {
      OutputLog::GetInstance().AddLine("Terrain Texture failed to load!", MessageType::ERROR);
    }
  }
}

void TerrainGenerator::GenerateTexture()
{
  sf::Vector2i mapSize = HexMath::GetMapSize(m_hexRadius, m_mapWidth, m_mapHeight);
  m_mapTexture.create(mapSize.x, mapSize.y);

  m_mapTexture.clear(sf::Color::Red);

  sf::Color col = sf::Color::Red;

  for (int y = 0; y < m_mapHeight; y++)
  {
    for (int x = 0; x < m_mapWidth; x++)
    {
      if (m_terrain[index(x,y)] == 0)
      {
        col = sf::Color(0, 13, 206);
      }
      else if (m_terrain[index(x, y)] == 1)
      {
        col = sf::Color(0, 206, 44);
      }
      else if (m_terrain[index(x, y)] == 2)
      {
        col = sf::Color(16, 183, 11);
      }
      else if (m_terrain[index(x, y)] == 3)
      {
        col = sf::Color(9, 76, 63);
      }
      else if (m_terrain[index(x, y)] == 4)
      {
        col = sf::Color(126, 130, 129);
      }

      sf::Vector2f position;

      position = sf::Vector2f(((m_hexInnerRadius * 2) * x) + (m_hexInnerRadius*(y % 2)), ((m_hexRadius * 2) * y) - ((m_hexRadius / 2)*y));

      sf::CircleShape hex;

      hex.setRadius(m_hexRadius);
      hex.setPosition(position);
      hex.setPointCount(6);
      hex.setFillColor(col);

      hex.setOutlineColor(sf::Color::White);
      hex.setOutlineThickness(1);

      m_mapTexture.draw(hex);
    }
  }
 
  m_mapTexture.setSmooth(true);
  m_mapTexture.display();
}

int TerrainGenerator::index(int x, int y)
{
  return (m_mapWidth * y) + x;
}