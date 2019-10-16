#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>
#include <string>

#include "Joueur.hpp"
#include "Liste_Joueur.hpp"

#include "Chemin.hpp"
#include "Liste_Chemin.hpp"

#include "Couleur.hpp"
#include "case.hpp"

class Jeu {
public:
  Jeu();
  ~Jeu();

  enum class Etat { attenteJoueur, animation, pause };

  void demarrer();

private:
  sf::RenderWindow *m_window;
  sf::Event m_event;

  Case m_plancheDeJeu[10][10];
  sf::Texture *m_textureCase;
  sf::Texture *m_textureCaseSpeciale;

  sf::Font *m_textFont;
  sf::Text m_message1;
  sf::Text m_message2;

  Liste_Chemin m_chemins;
  Liste_Joueur m_joueurs;

  Etat m_etat;
  Joueur *m_joueurCourant;

  unsigned int m_nbJoueurs;

  void entrerInfoJoueurs();
  void initialiserJeu();

  void chargerPlancheDeJeu();
  void chargerTexturesCases();
  void chargerCases();
  void chargerTexteCases();
  void chargerMessages();

  void bouclePrincipale();

  void gererInput();

  void afficher();
  void afficherCases();
  void afficherMessage();
};
