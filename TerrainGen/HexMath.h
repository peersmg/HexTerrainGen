#include "stdafx.h"

class HexMath
{
public:
  static float GetInnerRadius(float radius)
  {
    return radius * 0.866025404f;
  }

  static sf::Vector2i GetMapSize(float radius, int mapWidth, int mapHeight)
  {
    float innerRadius = GetInnerRadius(radius);

    return sf::Vector2i(((float)mapWidth*innerRadius * 2) + innerRadius, ((float)mapHeight * radius * 2) - ((radius / 2)*(mapHeight - 1)));
  }
};