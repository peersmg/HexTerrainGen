#pragma once
#include "GameObject.h"

class CTerrainGenerator;
class Component;
class CTextfield;
class CText;
class TerrainGenerator : public GameObject
{
private:

  CTerrainGenerator* m_terrainGenerator;
  Component* m_generateButton;
  Component* m_rectShape;
  CTextfield* m_seedInput;
  Component* m_seedText;
  Component* m_randomizeSeedBtn;

public:
  TerrainGenerator(InitialisationData data);
  ~TerrainGenerator();

  void Update(float deltaTime) override;

  void ButtonPressed(std::string buttonId) override;
};

