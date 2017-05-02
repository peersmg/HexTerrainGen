#include "stdafx.h"
#include "SDefault.h"
#include "OutputLog.h"
#include "ObjectFactory.h"
#include "Game.h"
#include "DefaultCamera.h"

SDefault::SDefault()
{
}


SDefault::~SDefault()
{
}

void SDefault::LoadScene(InitialisationData data)
{
  OutputLog::GetInstance().AddLine("Loading Default Scene...", MessageType::MESSAGE);

  InitialisationData cameraData;
  cameraData.scene = "DefaultScene";

  GameObject* defaultCamera = ObjectFactory::GetInstance().Spawn("DefaultCamera", cameraData);
  Game::instance.GetWindow()->AddCamera(defaultCamera);

  ObjectFactory::GetInstance().Spawn("MenuManager", cameraData);

}