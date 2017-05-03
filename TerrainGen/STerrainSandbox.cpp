#include "STerrainSandbox.h"
#include "OutputLog.h"
#include "ObjectFactory.h"
#include "Game.h"

STerrainSandbox::STerrainSandbox()
{
}


STerrainSandbox::~STerrainSandbox()
{
}

void STerrainSandbox::LoadScene(InitialisationData data)
{
  OutputLog::GetInstance().AddLine("Loading Terrain sandbox...", MessageType::MESSAGE);

  InitialisationData terrainData;
  terrainData.scene = "TerrainSandbox";

  GameObject* mapCamera = ObjectFactory::GetInstance().Spawn("MapCamera", terrainData);
  Game::instance.GetWindow()->AddCamera(mapCamera);

  GameObject* guiCamera = ObjectFactory::GetInstance().Spawn("GUICamera", terrainData);
  Game::instance.GetWindow()->AddCamera(guiCamera);

  ObjectFactory::GetInstance().Spawn("TerrainGenerator", terrainData);

}
