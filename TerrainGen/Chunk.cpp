#include "Chunk.h"
#include "ResourceLoader.h"
#include "HexMath.h"

Chunk::Chunk(sf::Vector2i chunkSize, int hexRadius)
{
  m_chunkSize = chunkSize;

  m_hexRadius = hexRadius;
  m_hexInnerRadius = HexMath::GetInnerRadius(hexRadius);

  m_pixelSize = HexMath::GetMapSize(m_hexRadius, m_chunkSize.x, m_chunkSize.y);
  m_renderTexture.create(m_pixelSize.x, m_pixelSize.y);

  DrawTexture();
}


Chunk::~Chunk()
{
}

void Chunk::DrawTexture()
{

  sf::Texture grass = ResourceLoader::GetInstance().GetTexture("resources/textures/grass.jpg");
  sf::Texture rock = ResourceLoader::GetInstance().GetTexture("resources/textures/rock.jpg");
  sf::Texture sand = ResourceLoader::GetInstance().GetTexture("resources/textures/sand.jpg");
  sf::Texture water = ResourceLoader::GetInstance().GetTexture("resources/textures/water.jpg");
  sf::Texture snow = ResourceLoader::GetInstance().GetTexture("resources/textures/snow.jpg");

  sf::CircleShape hex;

  hex.setRadius(m_hexRadius);
  hex.setPointCount(6);

  for (int y = 0; y < m_chunkSize.y; y++)
  {
    for (int x = 0; x < m_chunkSize.x; x++)
    {

      switch (m_tileInfo->)
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

      m_renderTexture.draw(hex);
    }
  }

  m_renderTexture.display();

  m_sprite = sf::Sprite(m_renderTexture.getTexture());
}

sf::Sprite Chunk::GetSprite()
{
  return m_sprite;
}

int Chunk::index(int x, int y)
{
  return (m_chunkSize.x * y) + x;
}

std::vector<HexInfo>* Chunk::GetTileInfo()
{
  return m_tileInfo;
}