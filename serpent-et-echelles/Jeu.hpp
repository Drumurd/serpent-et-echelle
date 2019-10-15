#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

#include "Liste_Joueur.hpp"
#include "Joueur.hpp"

#include "Liste_Chemin.hpp"
#include "Chemin.hpp"

#include "Couleur.hpp"

struct Case {
	sf::Sprite sprite_Case;
	sf::Text txt_Case;
};

class Jeu {
private:
	sf::RenderWindow m_window;

	Case m_plancheDeJeu[10][10];
	Liste_Chemin m_chemins;
	Liste_Joueur m_joueurs;

	unsigned int m_nbJoueurs;

	unsigned int NumeroCaseAColone(const unsigned int& numeroCase);
	unsigned int NumeroCaseALigne(const unsigned int& numeroCase);

	void entrerInfoJoueurs();

public:
	Jeu();
	~Jeu();


	void demarrer();

};
