#pragma once
#include "GameObject.h"

class CTextfield;
class CMyButton;
class CDropdown;
class MenuManager : public GameObject
{
private:
  CTextfield* m_seedInput;
  CTextfield* m_widthInput;
  CTextfield* m_heightInput;
  CMyButton* m_button;

public:
  MenuManager(InitialisationData data);
  ~MenuManager();

  void Update(float deltaTime);

  void ButtonPressed(std::string buttonId);
};

