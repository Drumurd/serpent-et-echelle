#pragma once

struct Case {
  sf::Sprite m_sprite;
  sf::Text m_text;
  sf::Vector2f m_position;
};

#define LARGEUR_CASE 80.0f
#define HAUTEUR_CASE 70.0f

unsigned int NumeroCaseAColone(const unsigned int &numeroCase);
unsigned int NumeroCaseALigne(const unsigned int &numeroCase);