#pragma once

#include <string>

#include "Couleur.hpp"


class Joueur {
private:
	unsigned int m_caseActuelle;
	Couleur m_couleur;
	std::string m_nom;

	Joueur* m_suivant;

public:
	Joueur();
	Joueur(const Couleur& couleur, const std::string& nom);
	~Joueur();

	void determinerSuivant(Joueur* suivant);

	Joueur* obtenirSuivant() const;

	Couleur obtenirCouleur() const;
};
