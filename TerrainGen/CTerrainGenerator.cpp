#include "CTerrainGenerator.h"
#include "OutputLog.h"
#include "Game.h"
#include "HexMath.h"
#include "ResourceLoader.h"

CTerrainGenerator::CTerrainGenerator(GameObject* pOwner)
{
  m_heightNoise.SetSeed(0);

  m_heightNoise.SetFrequency(1.5);        // How jagged the terrain is

  m_heightNoise.SetLacunarity(1);         // How much extra random bits
  m_heightNoise.SetPersistence(0.5);

  m_heightNoise.SetOctaveCount(6);

  m_hexRadius = 40;
  m_hexInnerRadius = HexMath::GetInnerRadius(m_hexRadius);

  m_mapHexSize = sf::Vector2i(100, 50);

  m_heightNoiseScale = 30;
}


CTerrainGenerator::~CTerrainGenerator()
{
}

void CTerrainGenerator::Update(float deltaTime)
{

}

void CTerrainGenerator::Draw()
{
  sf::Vector2i chunkSize = HexMath::GetMapSize(m_hexRadius, 5, 5);

  for (int i = 0; i < m_textureChunks.size(); i++)
  {
    sf::Sprite chunk = sf::Sprite(m_textureChunks[i]);
    Game::instance.GetWindow()->Draw(chunk, 0);
  }
}

void CTerrainGenerator::CreateTerrain()
{
  GenerateTerrain();
  GenerateTextures();
}

void CTerrainGenerator::GenerateTerrain()
{
  float maxValue = -100;
  float minValue = 100;

  m_terrain.erase(m_terrain.begin(), m_terrain.end());

  for (int y = 0; y < m_mapHexSize.y; y++)
  {
    for (int x = 0; x < m_mapHexSize.x; x++)
    {
      if (m_heightNoise.GetValue((float)x / m_heightNoiseScale, (float)y / m_heightNoiseScale, 0) < minValue)
      {
        minValue = m_heightNoise.GetValue((float)x / m_heightNoiseScale, (float)y / m_heightNoiseScale, 0);
      }
      else if (m_heightNoise.GetValue((float)x / m_heightNoiseScale, (float)y / m_heightNoiseScale, 0) > maxValue)
      {
        maxValue = m_heightNoise.GetValue((float)x / m_heightNoiseScale, (float)y / m_heightNoiseScale, 0);
      }
    }
  }

  for (int y = 0; y < m_mapHexSize.y; y++)
  {
    for (int x = 0; x < m_mapHexSize.x; x++)
    {
      float inNoise = m_heightNoise.GetValue((float)x / m_heightNoiseScale, (float)y / m_heightNoiseScale, 0);
      float heightNoiseVal = RemapValues(inNoise, minValue, maxValue, 0, 1);
      int heightVal = int(heightNoiseVal * 128.f);

      HexInfo hexInfo;

      hexInfo.SetHeight(heightVal);

      m_terrain.push_back(hexInfo);
    }
  }
}

void CTerrainGenerator::GenerateTextures()
{
  sf::Vector2i mapSize = HexMath::GetMapSize(m_hexRadius, m_mapHexSize.x, m_mapHexSize.y);
  sf::Vector2i chunkSize = HexMath::GetMapSize(m_hexRadius, 5, 5);

  sf::Texture grass = ResourceLoader::GetInstance().GetTexture("resources/textures/grass.jpg");
  sf::Texture rock = ResourceLoader::GetInstance().GetTexture("resources/textures/rock.jpg");
  sf::Texture sand = ResourceLoader::GetInstance().GetTexture("resources/textures/sand.jpg");
  sf::Texture water = ResourceLoader::GetInstance().GetTexture("resources/textures/water.jpg");
  sf::Texture snow = ResourceLoader::GetInstance().GetTexture("resources/textures/snow.jpg");

  m_textureChunks.erase(m_textureChunks.begin(), m_textureChunks.end());

  sf::CircleShape hex;

  hex.setRadius(m_hexRadius);
  hex.setPointCount(6);

  sf::RenderTexture renderTexture;
  renderTexture.create(mapSize.x, mapSize.y);

  for (int y = 0; y < m_mapHexSize.y; y++)
  {
    for (int x = 0; x < m_mapHexSize.x; x++)
    {

      switch (m_terrain[index(x, y)].GetType())
      {
      case HexType::DEEP_WATER:
        hex.setTexture(&water);
        break;
      case HexType::SHALLOW_WATER:
        hex.setTexture(&water);
        break;
      case HexType::SAND:
        hex.setTexture(&sand);
        break;
      case HexType::GRASS:
        hex.setTexture(&grass);
        break;
      case HexType::TUNDRA:
        break;
      case HexType::ICE:
        break;
      case HexType::SNOW:
        hex.setTexture(&snow);
        break;
      case HexType::ROCK:
        hex.setTexture(&rock);
        break;
      case HexType::SWAMP:
        break;
      default:
        break;
      }

      sf::Vector2f position;

      position = sf::Vector2f(((m_hexInnerRadius * 2) * x) + (m_hexInnerRadius*(y % 2)), ((m_hexRadius * 2) * y) - ((m_hexRadius / 2)*y));

      hex.setPosition(position);
      //hex.setOutlineColor(sf::Color::White);
      //hex.setOutlineThickness(1);

      renderTexture.draw(hex);
    }
  }

  renderTexture.display();

  m_textureChunks.push_back(renderTexture.getTexture());
}

int CTerrainGenerator::index(int x, int y)
{
  return (m_mapHexSize.x * y) + x;
}

float CTerrainGenerator::RemapValues(float value, float inMin, float inMax, float outMin, float outMax)
{
  return outMin + ((outMax - outMin) / (inMax - inMin)) * (value - inMin);
}

void CTerrainGenerator::SetHexRadius(float radius)
{
  m_hexRadius = radius;
  m_hexInnerRadius = HexMath::GetInnerRadius(radius);
}

void CTerrainGenerator::SetHexMapSize(sf::Vector2i mapHexSize)
{
  m_mapHexSize = mapHexSize;
}

void CTerrainGenerator::SetHeightSeed(int seed)
{
  m_heightNoise.SetSeed(seed);
}

void CTerrainGenerator::SetHeightNoiseScale(float scale)
{
  m_heightNoiseScale = scale;
}

void CTerrainGenerator::SetHeightFrequency(float frequency)
{
  m_heightNoise.SetFrequency(frequency);
}

void CTerrainGenerator::SetHeightLacunarity(float lacunarity)
{
  m_heightNoise.SetLacunarity(lacunarity);
}

void CTerrainGenerator::SetHeightPersistence(float persistence)
{
  m_heightNoise.SetPersistence(persistence);
}

void CTerrainGenerator::SetHeightOctaveCount(int octaveCount)
{
  m_heightNoise.SetOctaveCount(octaveCount);
}
