#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <string>

#include "Joueur.hpp"
#include "Liste_Joueur.hpp"

#include "Chemin.hpp"
#include "Liste_Chemin.hpp"

#include "Case.hpp"
#include "Couleur.hpp"
#include "De.hpp"

class Jeu {
public:
  Jeu();
  ~Jeu();

  enum class Etat { attenteJoueur, brassageDe, mouvementJoueur, partieTermine };

  void demarrer();

private:
  sf::RenderWindow *m_window;
  sf::Event m_event;

  Case m_plancheDeJeu[10][10];
  sf::Texture m_textureCase;
  sf::Texture m_textureCaseSpeciale;

  sf::Font m_textFont;
  sf::Text m_message1;
  sf::Text m_message2;

  Liste_Chemin m_chemins;
  Liste_Joueur m_joueurs;

  De m_de;

  Etat m_etat;
  Joueur *m_joueurCourant;

  sf::SoundBuffer m_bufferSonSerpent;
  sf::SoundBuffer m_bufferSonEchelle;
  sf::Sound m_sonSerpent;
  sf::Sound m_sonEchelle;

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
  void chargerSons();

  void bouclePrincipale();

  void gererInput();

  void afficher();

  void afficherCases();
  void afficherNumeroCases();

  void afficherMessage();

  void jouerTour();
  bool verifierChemins();

  void update();
  void updateMessages();
};
