#pragma once
#include "stdafx.h"
#include "Component.h"

class CRectShape : public Component
{
private:
  int m_camera;
  alignment m_alignment;
  sf::Color m_fillColor;
  sf::Color m_outlineColor;
  int m_outlineThickness;
  sf::FloatRect m_rect;

public:

  /**
  * Constructor for Rectangle shape.
  *
  * @param rect - Rectangle.
  * @param fillColor - Rectangle fill color.
  */
  CRectShape(GameObject* pOwner, sf::FloatRect rect, sf::Color fillColor, float outlineThickness = 0, sf::Color outlineColor = sf::Color::Black, alignment alignment = alignment::TOPLEFT, int camera = 0);

  /**
  * Destructor.
  */
  ~CRectShape();

  void Update(float deltatime) override;
  void Draw() override;
};

