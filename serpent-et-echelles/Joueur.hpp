#pragma once

#include <SFML/Graphics.hpp>
#include <string>

#include "Couleur.hpp"
#include "case.hpp"

class Joueur {

public:
  Joueur();
  Joueur(const Couleur &couleur, const std::string &nom);
  ~Joueur();

  void placerDansCase(const unsigned int &numeroCase);
  void placerACoordonees(const sf::Vector2f &position);

  void determinerSuivant(Joueur *suivant);

  Joueur *obtenirSuivant() const;

  Couleur obtenirCouleur() const;

  sf::Sprite obtenirSprite() const;

  void afficher(sf::RenderWindow *window);

private:
  unsigned int m_caseActuelle;
  Couleur m_couleur;
  std::string m_nom;

  sf::Texture m_texture;
  sf::Sprite m_sprite;
  sf::Vector2f m_offset;

  Joueur *m_suivant;

  void chargerSprite();

  void determinerOffset();
};
