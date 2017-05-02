#include "MapCamera.h"
#include "CCamera.h"
#include "Game.h"
#include "HexMath.h"

#include "InputManager.h"
#include "ObjectFactory.h"
#include "OutputLog.h"
#include "DrawManager.h"

GameObject* CreateMapCamera(InitialisationData data)
{
  MapCamera* pTemp = new MapCamera(data);
  return (GameObject*)pTemp;
}

const bool bMapCamera = ObjectFactory::GetInstance().Register("MapCamera", CreateMapCamera);

MapCamera::MapCamera(InitialisationData data)
{
  m_camera = new CCamera(this, Game::instance.GetWindow()->GetSize(), sf::FloatRect(0, 0, 1, 1), 0, 1, true);
  AddComponent(m_camera);


  m_moveSpeed = 500;
  m_clampCamera = false;
  m_mouseAnchor = sf::Vector2i(0,0);

  float hexRadius = data.floatData["HexRadius"];

  float mapWidth = data.floatData["Width"];
  float mapHeight = data.floatData["Height"];

  m_mapSize = sf::Vector2f(HexMath::GetMapSize(hexRadius, mapWidth, mapHeight));

  m_transform.SetPosition(sf::Vector2f((m_mapSize.x / 2) - Game::instance.GetWindow()->GetSize().x / 2, (m_mapSize.y / 2) - Game::instance.GetWindow()->GetSize().y / 2));
}

MapCamera::~MapCamera()
{
}

void MapCamera::Update(float deltaTime)
{
  sf::Vector2f newCameraPosition;
  
  newCameraPosition = ClampCameraPosition(CameraKeyboardMovement(deltaTime));
  m_transform.SetPosition(newCameraPosition);

  newCameraPosition = ClampCameraPosition(CameraMouseMovement(deltaTime));
  m_transform.SetPosition(newCameraPosition);
}

sf::Vector2f MapCamera::CameraMouseMovement(float deltaTime)
{
  sf::Vector2f newPos = m_transform.GetPosition();

  if (InputManager::GetInstance()->ButtonDown(sf::Mouse::Left))
  {
    newPos -= sf::Vector2f(InputManager::GetInstance()->GetMousePosition(0, false) - m_lastMousePos)*m_camera->GetZoom();
  }

  m_lastMousePos = InputManager::GetInstance()->GetMousePosition(0, false);
  return newPos;
}

sf::Vector2f MapCamera::CameraKeyboardMovement(float deltaTime)
{
  sf::Vector2f newPos = m_transform.GetPosition();

  if (InputManager::GetInstance()->KeyDown("right"))
  {
    newPos = sf::Vector2f(newPos.x + (m_moveSpeed * deltaTime), newPos.y);
  }
  if (InputManager::GetInstance()->KeyDown("left"))
  {
    newPos = sf::Vector2f(newPos.x - (m_moveSpeed * deltaTime), newPos.y);
  }
  if (InputManager::GetInstance()->KeyDown("up"))
  {
    newPos = sf::Vector2f(newPos.x, newPos.y - (m_moveSpeed * deltaTime));
  }
  if (InputManager::GetInstance()->KeyDown("down"))
  {
    newPos = sf::Vector2f(newPos.x, newPos.y + (m_moveSpeed * deltaTime));
  }

  return newPos;
}

sf::Vector2f MapCamera::ClampCameraPosition(sf::Vector2f position)
{

  sf::Vector2f windowSize = (sf::Vector2f(Game::instance.GetWindow()->GetSize()) * m_camera->GetZoom());
  float windowWidthOffset = ((Game::instance.GetWindow()->GetSize().x * m_camera->GetZoom()) - Game::instance.GetWindow()->GetSize().x) / 2;
  float windowHeightOffset = ((Game::instance.GetWindow()->GetSize().y * m_camera->GetZoom()) - Game::instance.GetWindow()->GetSize().y) / 2;

  sf::Vector2f newPos = m_transform.GetPosition();

  if (m_clampCamera)
  {
    if (position.x < m_mapSize.x - (Game::instance.GetWindow()->GetSize().x + windowWidthOffset)
      && position.x > windowWidthOffset)
    {
      newPos = (sf::Vector2f(position.x, newPos.y));
    }

    if (position.y < m_mapSize.y - (Game::instance.GetWindow()->GetSize().y + windowHeightOffset)
      && position.y > windowHeightOffset)
    {
      newPos = (sf::Vector2f(newPos.x, position.y));
    }
  }
  else
  {
    newPos = position;
  }

  return newPos;
  
}