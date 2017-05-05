#pragma once
#include "stdafx.h"
#include "HexInfo.h"

class Chunk
{
private:
  std::vector<HexInfo>* m_tileInfo;
  sf::Vector2i m_chunkSize;
  sf::Vector2i m_pixelSize;
  sf::RenderTexture m_renderTexture;
  sf::Sprite m_sprite;

  float m_hexRadius;
  float m_hexInnerRadius;

public:
  Chunk(sf::Vector2i chunkSize, int hexRadius);
  ~Chunk();

  void DrawTexture();
  sf::Sprite GetSprite();

  std::vector<HexInfo>* GetTileInfo();

  int index(int x, int y);
};

