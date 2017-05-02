#include "stdafx.h"
#include "DefaultCamera.h"
#include "CCamera.h"
#include "Game.h"
#include "InputManager.h"
#include "ObjectFactory.h"
#include "OutputLog.h"

GameObject* CreateDefaultCamera(InitialisationData data)
{
  DefaultCamera* pTemp = new DefaultCamera(data);
  return (GameObject*)pTemp;
}

const bool bDefaultCamera = ObjectFactory::GetInstance().Register("DefaultCamera", CreateDefaultCamera);

DefaultCamera::DefaultCamera(InitialisationData data)
{
  AddComponent(new CCamera(this, Game::instance.GetWindow()->GetSize()));
}

DefaultCamera::~DefaultCamera()
{
}

void DefaultCamera::Update(float deltaTime)
{
  
}