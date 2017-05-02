#pragma once
#include "Scene.h"

class SDefault : public Scene
{
public:
  SDefault();
  ~SDefault();

  void LoadScene(InitialisationData data) override;

};

