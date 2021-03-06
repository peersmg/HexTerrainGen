#include "GUICamera.h"
#include "ObjectFactory.h"
#include "Game.h"
#include "CCamera.h"
#include "CMyButton.h"
#include "SDefault.h"

#include "CText.h"

GameObject* CreateGUICamera(InitialisationData data)
{
  GUICamera* pTemp = new GUICamera(data);
  return (GameObject*)pTemp;
}

const bool bGUICamera = ObjectFactory::GetInstance().Register("GUICamera", CreateGUICamera);

GUICamera::GUICamera(InitialisationData data)
{
  AddComponent(new CCamera(this, Game::instance.GetWindow()->GetSize()));
  
  AddComponent(new CMyButton(this, "ReturnButton", "Menu",
    sf::FloatRect(50, Game::instance.GetWindow()->GetSize().y - 20, 200, 30),
    "DefaultStyle", 18, alignment::BOTTOMLEFT, 1));

  m_layer = 10;
}


GUICamera::~GUICamera()
{
}

void GUICamera::Update(float deltaTime)
{
  
}

void GUICamera::ButtonPressed(std::string buttonId)
{
  InitialisationData data;
  Game::instance.m_SceneManager.SetScene("DefaultScene", data);
}