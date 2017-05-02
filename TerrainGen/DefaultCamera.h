#pragma once
#include "GameObject.h"

class CCamera;
class Window;
class DefaultCamera : public GameObject
{

public:
  DefaultCamera(InitialisationData data);
  ~DefaultCamera();

  void Update(float deltaTime) override;
};

