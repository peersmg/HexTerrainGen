#include "TerrainGenerator.h"
#include "ObjectFactory.h"
#include "OutputLog.h"
#include "ResourceLoader.h"
#include "Game.h"
#include "HexMath.h"
#include "InputManager.h"

#include "CRectShape.h"
#include "CMyButton.h"
#include "CTerrainGenerator.h"
#include "CRectShape.h"
#include "CTextfield.h"
#include "CText.h"
#include "DrawManager.h"

GameObject* CreateTerrainGenerator(InitialisationData data)
{
  TerrainGenerator* pTemp = new TerrainGenerator(data);
  return (GameObject*)pTemp;
}

const bool bTerrainGenerator = ObjectFactory::GetInstance().Register("TerrainGenerator", CreateTerrainGenerator);


TerrainGenerator::TerrainGenerator(InitialisationData data)
{

  m_terrainGenerator = new CTerrainGenerator(this);
  AddComponent(m_terrainGenerator);

  m_terrainGenerator->SetHexRadius(40);
  m_terrainGenerator->SetHexMapSize(sf::Vector2i(200, 100));

  m_terrainGenerator->SetHeightSeed(0);
  m_terrainGenerator->SetHeightFrequency(4);
  m_terrainGenerator->SetHeightLacunarity(0);
  m_terrainGenerator->SetHeightPersistence(0);
  m_terrainGenerator->SetHeightOctaveCount(6);

  m_terrainGenerator->SetHeightNoiseScale(100);

  m_terrainGenerator->CreateTerrain();  

  m_rectShape = AddComponent(new CRectShape(this, sf::FloatRect(Game::instance.GetWindow()->GetSize().x, 0, 350, Game::instance.GetWindow()->GetSize().y),
               sf::Color(200, 10, 10, 100), 2, sf::Color::Black, alignment::TOPRIGHT, 1));

  m_generateButton = AddComponent(new CMyButton(this, "GenerateTerrain", "Generate Terrain",
    sf::FloatRect(Game::instance.GetWindow()->GetSize().x - 50, Game::instance.GetWindow()->GetSize().y - 20, 200, 30),
    "DefaultStyle", 18, alignment::BOTTOMRIGHT, 1));

  m_seedInput = new CTextfield(this, sf::Vector2f(Game::instance.GetWindow()->GetSize().x-250, 50), 100, 1, "Seed", "0","DefaultStyle", 18, 8, alignment::TOPLEFT, 1);
  AddComponent(m_seedInput);

  m_seedText = AddComponent(new CText(this, "Seed: ", sf::Vector2f(Game::instance.GetWindow()->GetSize().x - 250, 50), "DefaultStyle", 18, alignment::TOPRIGHT, 1));

  m_randomizeSeedBtn = AddComponent(new CMyButton(this, "RandomizeSeed", "Randomize",
    sf::FloatRect(Game::instance.GetWindow()->GetSize().x - 120, 50, 110, 30),
    "DefaultStyle", 18, alignment::TOPLEFT, 1));
}


TerrainGenerator::~TerrainGenerator()
{
}

void TerrainGenerator::Update(float deltaTime)
{
  if (InputManager::GetInstance()->KeyPressed(sf::Keyboard::C))
  {
    m_generateButton->SetDormant(!m_generateButton->GetDormant());
    m_rectShape->SetDormant(!m_rectShape->GetDormant());
    m_seedText->SetDormant(!m_seedText->GetDormant());
    m_seedInput->SetDormant(!m_seedInput->GetDormant());
    m_randomizeSeedBtn->SetDormant(!m_randomizeSeedBtn->GetDormant());
  }
}

void TerrainGenerator::ButtonPressed(std::string buttonId)
{
  if (buttonId == "GenerateTerrain")
  {
    m_terrainGenerator->SetHexRadius(40);
    m_terrainGenerator->SetHexMapSize(sf::Vector2i(200, 100));

    m_terrainGenerator->SetHeightSeed(std::atoi(m_seedInput->GetText().c_str()));;
    m_terrainGenerator->SetHeightFrequency(4);
    m_terrainGenerator->SetHeightLacunarity(0);
    m_terrainGenerator->SetHeightPersistence(0);
    m_terrainGenerator->SetHeightOctaveCount(6);

    m_terrainGenerator->SetHeightNoiseScale(100);

    m_terrainGenerator->CreateTerrain();
  }
  else if (buttonId == "RandomizeSeed")
  {
    m_seedInput->SetText(std::to_string(rand()%99999999));
  }
}