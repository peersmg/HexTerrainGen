#include "HexInfo.h"
#include "OutputLog.h"

HexInfo::HexInfo()
{
  m_heightValue = 20;
  RecalculateType();
}


HexInfo::~HexInfo()
{
}

void HexInfo::SetHeight(int height)
{
  m_heightValue = height;

  RecalculateType();
}

void HexInfo::Tick()
{

}

void HexInfo::RecalculateType()
{
  //OutputLog::GetInstance().AddLine(m_heightValue);

  if (m_heightValue > 120)
  {
    m_type = HexType::SNOW;
  }
  else if (m_heightValue > 100)
  {
    m_type = HexType::ROCK;
  }
  else if (m_heightValue > 70)
  {
    m_type = HexType::GRASS;
  }
  else if (m_heightValue > 60)
  {
    m_type = HexType::SAND;
  }
  else if (m_heightValue > 50)
  {
    m_type = HexType::SHALLOW_WATER;
  }
  else
  {
    m_type = HexType::DEEP_WATER;
  }
}

bool HexInfo::GetTicks()
{
  return m_ticks;
}

HexType HexInfo::GetType()
{
  return m_type;
}