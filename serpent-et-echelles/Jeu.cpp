#include "Jeu.hpp"

Jeu::Jeu() :m_window(), m_nbJoueurs(0), m_event(), m_textureCase(nullptr), m_textureCaseSpeciale(nullptr), m_textFont(nullptr) {
}

Jeu::~Jeu() {
	delete m_textureCase;
	delete m_textureCaseSpeciale;
	delete m_window;
}

unsigned int Jeu::NumeroCaseAColone(const unsigned int& numeroCase) { return 0; }

unsigned int Jeu::NumeroCaseALigne(const unsigned int& numeroCase) { return 0; }

void Jeu::afficherCases() {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			m_window->draw(m_plancheDeJeu[i][j].m_sprite);
			m_window->draw(m_plancheDeJeu[i][j].m_text);

		}
	}
}


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
void Jeu::initialiserJeu() {
	m_window = new sf::RenderWindow(sf::VideoMode(800, 800), "Serpents et Échelles");
	if (m_window == nullptr) {
		throw std::exception("Impossible de charger la fenêtre");
	}
	m_window->setVerticalSyncEnabled(true);

	chargerPlancheDeJeu();
}

void Jeu::chargerPlancheDeJeu() {
	m_textureCase = new sf::Texture();
	m_textureCaseSpeciale = new sf::Texture();

	if (!m_textureCase->loadFromFile("assets\\textures\\case.jpg")) {
		throw std::exception("Impossible de charger la texture \"case.jpg\"");
	}
	if (!m_textureCaseSpeciale->loadFromFile("assets\\textures\\caseSpeciale.jpg")) {
		throw std::exception("Impossible de charger la texture \"caseSpeciale.jpg\"");
	}

	unsigned noCase = 99;

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {

			float x, y;
			x = j * LARGEUR_CASE;
			y = i * HAUTEUR_CASE;
			sf::Vector2f positionTexture(x, y);

			m_plancheDeJeu[i][j].m_sprite = sf::Sprite(*m_textureCase);
			m_plancheDeJeu[i][j].m_sprite.setPosition(positionTexture);
			m_plancheDeJeu[i][j].m_position = positionTexture;

			m_textFont = new sf::Font;
			if (!m_textFont->loadFromFile("assets\\fonts\\pixelated\\pixelated.ttf")) {
				throw std::exception("Impossible de charger la police \"pixelated.ttf\"");
			}

			x += 7.0f; // centrer le texte
			sf::Vector2f positionTexte(x, y);

			m_plancheDeJeu[i][j].m_text.setFont(*m_textFont);
			m_plancheDeJeu[i][j].m_text.setFillColor(sf::Color(255, 255, 255, 255));
			m_plancheDeJeu[i][j].m_text.setScale(0.7f, 0.7f);
			m_plancheDeJeu[i][j].m_text.setPosition(positionTexte);

			if (i % 2) {
				m_plancheDeJeu[i][9 - j].m_text.setString(std::to_string(noCase));
			}
			else {
				m_plancheDeJeu[i][j].m_text.setString(std::to_string(noCase));
			}

			noCase--;
		}
	}
	m_plancheDeJeu[9][0].m_text.setString("Depart");
	m_plancheDeJeu[0][0].m_text.setString("Fin");

	m_plancheDeJeu[9][0].m_sprite.setTexture(*m_textureCaseSpeciale);
	m_plancheDeJeu[0][0].m_sprite.setTexture(*m_textureCaseSpeciale);

}


void Jeu::bouclePrincipale() {
	while (m_window->isOpen()) {
		gererInput();

		afficher();
	}
}

void Jeu::gererInput() {
	while (m_window->pollEvent(m_event)) {
		switch (m_event.type) {
		case sf::Event::Closed:
			m_window->close();
			break;
		}
	}
}

void Jeu::afficher() {
	m_window->clear(sf::Color(0, 0, 0, 255));

	afficherCases();
	m_chemins.afficher(m_window);
	m_joueurs.afficher(m_window);

	m_window->display();
}


void Jeu::demarrer() {
	entrerInfoJoueurs();
	initialiserJeu();
	bouclePrincipale();
}

