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

  m_button = new CMyButton(this, "SubmitButton", "Start",
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

  Game::instance.m_SceneManager.SetScene("TerrainSandbox");
}