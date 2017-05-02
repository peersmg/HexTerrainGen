#pragma once
#include "Scene.h"
class STerrainSandbox : public Scene
{
private:
  int m_seed;
public:
  STerrainSandbox();
  ~STerrainSandbox();

  void LoadScene(InitialisationData data) override;
};