#pragma once
#include <SFML/Graphics.hpp>

#include <string>

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

private:
  unsigned int m_caseHaut;
  unsigned int m_caseBas;

  sf::Texture m_texture;
  sf::Sprite m_sprite;

  Type m_type;

  Chemin *m_suivant;

  void chargerSprite();
};
