#include "MenuManager.h"
#include "ObjectFactory.h"
#include "Game.h"
#include "STerrainSandbox.h"

#include "CTextfield.h"
#include "CMyButton.h"
#include "CDropdown.h"
#include "CText.h"

#include "OutputLog.h"

GameObject* CreateMenuManager(InitialisationData data)
{
  MenuManager* pTemp = new MenuManager(data);
  return (GameObject*)pTemp;
}

const bool bMenuManager = ObjectFactory::GetInstance().Register("MenuManager", CreateMenuManager);

MenuManager::MenuManager(InitialisationData data)
{
  OutputLog::GetInstance().AddLine("Menu Started");

  m_seedInput = new CTextfield(this, sf::Vector2f(Game::instance.GetWindow()->GetSize().x / 1.5, Game::instance.GetWindow()->GetSize().y / 2), Game::instance.GetWindow()->GetSize().x / 8,
    1, "Enter Seed", "DefaultStyle", 22, 6, alignment::MIDDLELEFT);

  AddComponent(m_seedInput);

  m_widthInput = new CTextfield(this, sf::Vector2f(Game::instance.GetWindow()->GetSize().x / 1.5, Game::instance.GetWindow()->GetSize().y / 2 - 200), Game::instance.GetWindow()->GetSize().x / 8,
    1, "Width", "DefaultStyle", 22, 6, alignment::MIDDLELEFT);

  AddComponent(m_widthInput);

  m_heightInput = new CTextfield(this, sf::Vector2f(Game::instance.GetWindow()->GetSize().x / 1.5, Game::instance.GetWindow()->GetSize().y / 2 - 100), Game::instance.GetWindow()->GetSize().x / 8,
    1, "Height", "DefaultStyle", 22, 6, alignment::MIDDLELEFT);

  AddComponent(m_heightInput);

  AddComponent(new CText(this, "Map Seed: ", sf::Vector2f((Game::instance.GetWindow()->GetSize().x / 1.5) - 300, (Game::instance.GetWindow()->GetSize().y / 2)),
    "DefaultStyle", 22, alignment::MIDDLELEFT));


  m_button = new CMyButton(this, "SubmitButton", "Generate Terrain",
    sf::FloatRect(Game::instance.GetWindow()->GetSize().x / 2, Game::instance.GetWindow()->GetSize().y - 100, Game::instance.GetWindow()->GetSize().x / 2, 50),
    "DefaultStyle", 22, alignment::MIDDLECENTER);
  AddComponent(m_button);

  OutputLog::GetInstance().AddLine("Menu Finished Starting");
}


MenuManager::~MenuManager()
{
}

void MenuManager::Update(float deltaTime)
{

}

void MenuManager::ButtonPressed(std::string buttonId)
{
  OutputLog::GetInstance().AddLine("Button Pressed");

  InitialisationData terrainData;
  terrainData.floatData["Seed"] = std::atoi(m_seedInput->GetText().c_str());
  terrainData.floatData["HexRadius"] = 40;

  terrainData.floatData["Width"] = std::atoi(m_widthInput->GetText().c_str());
  terrainData.floatData["Height"] = std::atoi(m_heightInput->GetText().c_str());
  
  

  Game::instance.m_SceneManager.SetScene("TerrainSandbox", terrainData);
}