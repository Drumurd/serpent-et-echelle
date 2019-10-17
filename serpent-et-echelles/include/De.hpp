#pragma once

#include <random>

class De {
public:
  De();
  ~De();

  unsigned int brasser();

private:
  std::random_device m_randomDevice;
  std::mt19937 m_randomEngine;
  std::uniform_int_distribution<> m_distribution;
};