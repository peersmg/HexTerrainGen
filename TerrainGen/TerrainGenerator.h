#pragma once
#include "GameObject.h"
#include "noise\noise.h"

class TerrainGenerator : public GameObject
{
private:
  int m_mapWidth;
  int m_mapHeight;

  float m_hexRadius;
  float m_hexInnerRadius;

  std::vector<int> m_terrain;

  sf::Texture m_texture;

  noise::module::Perlin m_perlinNoise;

  sf::RenderTexture m_mapTexture;

public:
  TerrainGenerator(InitialisationData data);
  ~TerrainGenerator();

  void Update(float deltaTime) override;

  void GenerateTerrain(int seed);
  void GenerateTexture();

  int index(int x, int y);
};

