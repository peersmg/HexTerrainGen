#pragma once
#include "stdafx.h"

class HexObject;
class HexInfo
{
private:
  HexType m_type;
  int m_heightValue;
  int m_temperature;
  int m_waterSaturation;
  int m_floraLevel;

  bool m_ticks;

  HexObject* m_hexObject;   // Thing that is present in this hex. e.g. Tree, part of building, rock deposit

public:
  HexInfo();
  ~HexInfo();

  void SetHeight(int height);

  void Tick();
  bool GetTicks();

  HexType GetType();

  void RecalculateType();
};

