#pragma once
#include <SFML/Graphics.hpp>

class Chemin {
public:
  Chemin();
  ~Chemin();

  enum class Type { serpent, echelle };

private:
  unsigned int m_caseHaut;
  unsigned int m_caseBas;
  sf::Sprite m_sprite;

  Type m_type;

  Chemin *m_suivant;
};
