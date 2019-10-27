#pragma once

#define VITESSE_JOUEUR 0.05f

#include <SFML/Graphics.hpp>
#include <cmath>
#include <string>

#include "Case.hpp"
#include "Couleur.hpp"

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

  void ajouterDestination(const unsigned int noCase);

  void afficher(sf::RenderWindow *window);
  bool update();

private:
  unsigned int m_caseActuelle;
  unsigned int m_pileDestinations[7];
  unsigned int m_profondeurPile;

  Couleur m_couleur;
  std::string m_nom;

  sf::Texture m_texture;
  sf::Sprite m_sprite;
  sf::Vector2f m_offset;

  Joueur *m_suivant;

  void chargerSprite();

  void determinerOffset();
};
