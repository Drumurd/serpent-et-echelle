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

  void placerDansCase(unsigned int numeroCase);

  void determinerSuivant(Joueur *suivant);

  Joueur *obtenirSuivant() const;

  Couleur obtenirCouleur() const;

  sf::Sprite obtenirSprite() const;

  std::string obtenirNom() const;

  unsigned int obtenirCaseCourante() const;

  void afficher(sf::RenderWindow *window);
  void update();

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
