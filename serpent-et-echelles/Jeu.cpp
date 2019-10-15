#include "Jeu.hpp"

Jeu::Jeu() :m_window(), m_nbJoueurs(0) {
}

Jeu::~Jeu() {}

unsigned int Jeu::NumeroCaseAColone(const unsigned int& numeroCase) { return 0; }

unsigned int Jeu::NumeroCaseALigne(const unsigned int& numeroCase) { return 0; }

void Jeu::entrerInfoJoueurs() {
	m_nbJoueurs = 0;
	bool valide(false);

	while (!valide)
	{
		std::cout << "Combien de joueurs ? ";

		if (!(std::cin >> m_nbJoueurs)) { // si l'utilisateur entre autre chose qu'un chiffre
			std::cin.clear();
			std::cin.ignore(10000, '\n');
		}

		if (m_nbJoueurs < 2 || m_nbJoueurs > 6)
			std::cout << "Le nombre de joueurs doit etre entre 2 et 6" << std::endl;
		else
			valide = true;
	}



	for (unsigned int i = 0; i < m_nbJoueurs; i++) {
		std::string nom("");

		std::cout << std::endl << "Quel est le nom du joueur " << i + 1 << "? ";
		std::cin >> nom;
		//std::cin.clear();
		//std::cin.ignore(10000, '\n');

		Joueur* joueur = new Joueur(intACouleur(i), nom);
		m_joueurs.ajouter(joueur);

		std::cout << nom << " aura la couleur " << joueur->obtenirCouleur() << std::endl;
	}
}

void Jeu::demarrer() {
	entrerInfoJoueurs();
	std::cout << "Il y aura " << m_nbJoueurs << " joueurs dans cette partie" << std::endl;
}