#pragma once
#include <SFML/Graphics.hpp>

class Chemin {
private:
  unsigned int m_caseHaut;
  unsigned int m_caseBas;
  sf::Sprite m_sprite;

  Chemin *m_suivant;

public:
  Chemin();
  ~Chemin();
};
