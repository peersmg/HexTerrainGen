#pragma once
#include "Component.h"
#include "noise\noise.h"
#include "HexInfo.h"

class GameObject;
class CTerrainGenerator : public Component
{
private:
  noise::module::Perlin m_heightNoise;        // Basis for everything else, how high the terrain is
  noise::module::Perlin m_temperatureNoise;   // Should be affected by the height (as well as position if the planet is equatorial)
  noise::module::Perlin m_floraNoise;         // If an area has forests (or jungle), affected by height and temperature
  noise::module::Perlin m_featureNoise;       // Special feature noise. e.g. if a hight feature value crosses with a high terrain value volcano is created

  std::vector<sf::Texture> m_textureChunks;
  sf::Sprite m_texture;

  std::vector<HexInfo> m_terrain;

  sf::Vector2i m_mapHexSize;
  float m_hexRadius;
  float m_hexInnerRadius;
  float m_heightNoiseScale;

  int m_seed;

  int m_chunkHexSize;

public:
  CTerrainGenerator(GameObject* pOwner);
  ~CTerrainGenerator();

  void SetHexRadius(float radius);
  void SetHexMapSize(sf::Vector2i mapHexSize);

  void SetHeightSeed(int seed);
  void SetHeightNoiseScale(float scale);
  void SetHeightFrequency(float frequency);
  void SetHeightLacunarity(float lacunarity);
  void SetHeightPersistence(float persistence);
  void SetHeightOctaveCount(int octaveCount);

  void CreateTerrain();

  void GenerateTerrain();
  void GenerateTextures();

  float RemapValues(float value, float inMin, float inMax, float outMin, float outMax);

  void Update(float deltaTime) override;
  void Draw() override;

  int index(int x, int y);
};

