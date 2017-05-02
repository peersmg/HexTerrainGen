#pragma once
#include "GameObject.h"

class CCamera;
class MapCamera : public GameObject
{
private:
  sf::Vector2f m_mapSize;
  CCamera* m_camera;

  float m_moveSpeed;
  bool m_clampCamera;

  sf::Vector2i m_mouseAnchor;
  sf::Vector2f m_cameraAnchorPos;
  bool m_anchorActive;
public:
  MapCamera(InitialisationData data);
  ~MapCamera();

  void Update(float deltaTime) override;

  sf::Vector2f CameraKeyboardMovement(float deltaTime);
  sf::Vector2f CameraMouseMovement(float deltaTime);

  sf::Vector2f ClampCameraPosition(sf::Vector2f position);

};

