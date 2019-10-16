#pragma once
#include <SFML/Graphics.hpp>

#include <cassert>
#include <string>

#include "Case.hpp"

#define LONGEUR_SERPENT 1513.0f
#define LONGEUR_ECHELLE 418.0f

class Chemin {
public:
  enum class Type { serpent, echelle };

  Chemin();
  Chemin(unsigned int caseHaut, unsigned int caseBas, Type type);
  ~Chemin();

  void determinerSuivant(Chemin *suivant);

  Chemin *obtenirSuivant() const;

  unsigned int obtenirCaseHaut() const;
  unsigned int obtenirCaseBas() const;

  void afficher(sf::RenderWindow *window);
  void placerSurCases();

private:
  unsigned int m_caseHaut;
  unsigned int m_caseBas;

  sf::Texture m_texture;
  sf::Sprite m_sprite;

  sf::Vector2f m_offsetCaseHaut;
  sf::Vector2f m_offsetCaseBas;

  Type m_type;

  Chemin *m_suivant;

  void chargerSprite();
};
