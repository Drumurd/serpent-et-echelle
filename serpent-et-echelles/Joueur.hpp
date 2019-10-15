#pragma once

#include <SFML/Graphics.hpp>
#include <string>

#include "Couleur.hpp"

class Joueur {
private:
  unsigned int m_caseActuelle;
  Couleur m_couleur;
  std::string m_nom;

  sf::Sprite m_sprite;
  sf::Vector2f m_offset;

  Joueur *m_suivant;

public:
  Joueur();
  Joueur(const Couleur &couleur, const std::string &nom);
  ~Joueur();

  void determinerSuivant(Joueur *suivant);

  Joueur *obtenirSuivant() const;

  Couleur obtenirCouleur() const;

  sf::Sprite obtenirSprite() const;
};
