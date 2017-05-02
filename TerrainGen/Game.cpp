#include "stdafx.h"
#include "Game.h"
#include "InputManager.h"
#include "OutputLog.h"
#include "Scene.h"
#include "SSplash.h"
#include "SDefault.h"
#include "STerrainSandbox.h"

#include "ResourceLoader.h"
#include "OutputLog.h"
#include "Component.h"
#include "ObjectFactory.h"
#include "icon.h"

Game::Game()
{
}
Game::~Game()
{
}

void Game::Start()
{
  if (m_gameState != GameState::Uninitialized)
  {
    return;
  }

  m_mainWindow = new Window("Game Title", sf::Vector2i(1228, 768), false, sf::Color(0, 13, 206));
  m_mainWindow->GetRenderWindow()->setIcon(sfml_icon.width, sfml_icon.height, sfml_icon.pixel_data);

//#ifndef NDEBUG
  OutputLog::GetInstance().Initialise();
//#endif

  m_gameState = GameState::Playing;

  // Load files
  ResourceLoader::GetInstance().LoadFonts();
  ResourceLoader::GetInstance().LoadSoundEffects();
  ResourceLoader::GetInstance().LoadTextures();
  ResourceLoader::GetInstance().LoadStyles();

  // Add Scenes
  m_SceneManager.AddScene("DefaultScene", new SDefault());
  m_SceneManager.AddScene("TerrainSandbox", new STerrainSandbox());

  //Input Axis
  InputManager::GetInstance()->AddAction("up", sf::Keyboard::Up);
  InputManager::GetInstance()->AddAction("up", sf::Keyboard::W);

  InputManager::GetInstance()->AddAction("down", sf::Keyboard::Down);
  InputManager::GetInstance()->AddAction("down", sf::Keyboard::S);

  InputManager::GetInstance()->AddAction("left", sf::Keyboard::Left);
  InputManager::GetInstance()->AddAction("left", sf::Keyboard::A);

  InputManager::GetInstance()->AddAction("right", sf::Keyboard::Right);
  InputManager::GetInstance()->AddAction("right", sf::Keyboard::D);

  OutputLog::GetInstance().AddLine("Starting...", MessageType::MESSAGE);

  // Set the initial scene
  InitialisationData data;
  m_SceneManager.SetScene("DefaultScene", data);

  // While the game is not exiting run the game loop
  while (!IsExiting())
  {
    GameLoop();
  }

  delete m_mainWindow;
}

Window* Game::GetWindow()
{
  return m_mainWindow;
}

bool Game::IsExiting()
{
  if (m_gameState == GameState::Exiting)
  {
    return true;
  }
  else
  {
    return false;
  }
}

void Game::GameLoop()
{
  ////

  sf::Time deltaTime = m_deltaClock.restart();

  // Update the inputs
  InputManager::GetInstance()->SampleKeyboard();

  m_mainWindow->Update();

  // Update and Draw GameObjects here
  m_SceneManager.GetScene("PersistentScene")->UpdateObjects(deltaTime.asSeconds());
  m_SceneManager.GetCurrentScene()->UpdateObjects(deltaTime.asSeconds());


  m_SceneManager.GetScene("PersistentScene")->DrawObjects();
  m_SceneManager.GetCurrentScene()->DrawObjects();

  m_SceneManager.DeleteInactiveObjects();

  ////
  m_mainWindow->Display();

//#ifndef NDEBUG
  OutputLog::GetInstance().Draw();
//#endif
  
}

void Game::SetState(GameState newState)
{
  m_gameState = newState;
}

Game Game::instance;