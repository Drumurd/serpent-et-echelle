#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

#include "Liste_Joueur.hpp"
#include "Joueur.hpp"

#include "Liste_Chemin.hpp"
#include "Chemin.hpp"

#include "Couleur.hpp"

#define LARGEUR_CASE 80.0f
#define HAUTEUR_CASE 70.0f

struct Case {
	sf::Sprite m_sprite;
	sf::Text m_text;
	sf::Vector2f m_position;
};

class Jeu {
private:
	sf::RenderWindow* m_window;
	sf::Event m_event;

	Case m_plancheDeJeu[10][10];
	sf::Texture* m_textureCase;
	sf::Texture* m_textureCaseSpeciale;
	sf::Font* m_textFont;

	Liste_Chemin m_chemins;
	Liste_Joueur m_joueurs;

	unsigned int m_nbJoueurs;

	unsigned int NumeroCaseAColone(const unsigned int& numeroCase);
	unsigned int NumeroCaseALigne(const unsigned int& numeroCase);

	void afficherCases();

	void entrerInfoJoueurs();
	void initialiserJeu();
	void chargerPlancheDeJeu();

	void bouclePrincipale();

	void gererInput();
	void afficher();


public:
	Jeu();
	~Jeu();


	void demarrer();

};
