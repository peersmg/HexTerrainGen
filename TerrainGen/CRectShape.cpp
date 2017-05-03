#include "stdafx.h"
#include "CRectShape.h"
#include "Game.h"
#include "DrawManager.h"

CRectShape::CRectShape(GameObject* pOwner, sf::FloatRect rect, sf::Color fillColor, float outlineThickness, sf::Color outlineColor, alignment alignment, int camera)
{
  m_pOwner = pOwner;

  Transform ownerTransform = m_pOwner->GetTransform();

  m_alignment = alignment;
  m_camera = camera;
  m_fillColor = fillColor;
  m_outlineThickness = outlineThickness;
  m_outlineColor = outlineColor;
  m_rect = rect;
}


CRectShape::~CRectShape()
{
}

void CRectShape::Update(float deltatime)
{

}

void CRectShape::Draw()
{
  DrawManager::GetInstance().DrawRect(m_rect, m_fillColor, m_outlineThickness, m_outlineColor, m_alignment, m_camera);
}