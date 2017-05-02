#pragma once
#include "GameObject.h"
class GUICamera : public GameObject
{
public:
  GUICamera(InitialisationData data);
  ~GUICamera();

  void Update(float deltaTime) override;

  void ButtonPressed(std::string buttonId) override;
};

