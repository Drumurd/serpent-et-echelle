#include "Liste_Joueur.hpp"

Liste_Joueur::Liste_Joueur() : m_premier(nullptr) {}
Liste_Joueur::~Liste_Joueur() {
	liberer();
}

void Liste_Joueur::afficher(sf::RenderWindow* window) {}

void Liste_Joueur::ajouter(Joueur* joueur) {


	if (m_premier == nullptr) {
		m_premier = joueur;
		m_premier->determinerSuivant(joueur);
	}
	else {
		Joueur* courant = m_premier;

		joueur->determinerSuivant(m_premier);
		for (;;) {
			if (courant->obtenirSuivant() == m_premier) {
				courant->determinerSuivant(joueur);
				//m_premier = joueur;
				break;
			}
			else
			{
				courant = courant->obtenirSuivant();
			}
		}
	}

}
void Liste_Joueur::liberer() {
	Joueur* courant = m_premier;
	for (;;) {
		Joueur* aLiberer = courant;
		courant = courant->obtenirSuivant();
		if (courant == m_premier) {
			delete aLiberer;
			break;
		}
		delete aLiberer;
	}
	m_premier = nullptr;
}

Joueur* Liste_Joueur::getPremierJoueur() { return m_premier; }