#pragma once

#include <SFML/Graphics.hpp>

struct Case {
  sf::Sprite m_sprite;
  sf::Text m_text;
};

#define LARGEUR_CASE 80.f
#define HAUTEUR_CASE 70.f

unsigned int NumeroCaseAColone(const unsigned int &numeroCase);
unsigned int NumeroCaseALigne(const unsigned int &numeroCase);
