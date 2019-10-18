#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>
#include <string>

#include <ctime>
#include <random>

#include "Joueur.hpp"
#include "Liste_Joueur.hpp"

#include "Chemin.hpp"
#include "Liste_Chemin.hpp"

#include "Couleur.hpp"
#include "De.hpp"
#include "case.hpp"

class Jeu {
public:
  Jeu();
  ~Jeu();

  enum class Etat { attenteJoueur, animation, pause, partieTermine };

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

  De m_de;

  Etat m_etat;
  Joueur *m_joueurCourant;

  unsigned int m_nbJoueurs;

  void entrerInfoJoueurs();
  void initialiserJeu();

  void redemarrerJeu();

  void chargerPlancheDeJeu();

  void chargerTexturesCases();
  void chargerCases();
  void chargerTexteCases();

  void chargerMessages();
  void chargerCheminsStatiques();

  void bouclePrincipale();

  void gererInput();

  void afficher();

  void afficherCases();
  void afficherNumeroCases();

  void afficherMessage();

  void jouerTour(Joueur *joueur);
  void effectuerDeplacements(Joueur *joueur, const unsigned int resultatDe);

  void update();
  void updateMessages();
};
