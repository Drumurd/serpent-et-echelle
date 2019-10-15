#include "Jeu.hpp"

unsigned int NumeroCaseAColone(const unsigned int &numeroCase) {
  // on arrondit à la dixaine la plus basse
  unsigned int numeroColonne = numeroCase - (numeroCase % 10);

  // on un chiffre entre 1 et 9 correspondant à la hauteur de la case
  numeroColonne /= 10;

  // on inverse le resultat pour avoir la même direction que le tableau de cases
  return 9 - numeroColonne;
}

unsigned int NumeroCaseALigne(const unsigned int &numeroCase) {

  // on arrondit à la dixaine la plus basse
  unsigned int numeroColonne = numeroCase - (numeroCase % 10);

  // on un chiffre entre 1 et 9 correspondant à la hauteur de la case
  numeroColonne /= 10;

  unsigned int numeroLigne = numeroCase - (10 * numeroColonne);

  // si la colonne est pair, on inverse le sens de la ligne
  if (numeroColonne % 2) {
    numeroLigne = 9 - numeroLigne;
  }
  return numeroLigne;
}

Jeu::Jeu()
    : m_window(), m_nbJoueurs(0), m_event(), m_textureCase(nullptr),
      m_textureCaseSpeciale(nullptr), m_textFont(nullptr),
      m_joueurCourant(nullptr) {}

Jeu::~Jeu() {
  delete m_window;

  delete m_textureCase;
  delete m_textureCaseSpeciale;

  delete m_textFont;
}

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

  while (!valide) {
    std::cout << "Combien de joueurs ? ";

    // si l'utilisateur entre autre chose qu'un chiffre
    if (!(std::cin >> m_nbJoueurs)) {
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
    Couleur couleur(intACouleur(i));

    std::cout << std::endl << "Quel est le nom du joueur " << i + 1 << "? ";
    std::cin >> nom;
    // std::cin.clear();
    // std::cin.ignore(10000, '\n');

    Joueur *joueur = new Joueur(couleur, nom);
    m_joueurs.ajouter(joueur);

    std::cout << nom << " aura la couleur " << joueur->obtenirCouleur()
              << std::endl;
  }
}
void Jeu::initialiserJeu() {
  m_window =
      new sf::RenderWindow(sf::VideoMode(800, 800), "Serpents et Échelles");

  if (m_window == nullptr) {
    throw std::exception("Impossible de charger la fenêtre");
  }

  m_window->setVerticalSyncEnabled(true);

  chargerPlancheDeJeu();
}

void Jeu::chargerPlancheDeJeu() {
  chargerCases();
  chargerTexteCases();
}

void Jeu::chargerTexturesCases() {
  m_textureCase = new sf::Texture();
  m_textureCaseSpeciale = new sf::Texture();

  std::string pathTexture;
  std::string pathTextureSpeciale;

#ifdef _WIN32
  pathTexture = "assets\\textures\\case.jpg";
  pathTextureSpeciale = "assets\\textures\\case-speciale.jpg";
#else
  pathTexture = "assets/textures/case.jpg";
  pathTextureSpeciale = "assets/textures/case-speciale.jpg";
#endif // _WIN32

  if (!m_textureCase->loadFromFile(pathTexture)) {
    std::string erreur =
        "Impossible de charger la texture \"" + pathTexture + "\"";
    throw std::exception(erreur.c_str());
  }

  if (!m_textureCaseSpeciale->loadFromFile(pathTextureSpeciale)) {
    std::string erreur =
        "Impossible de charger la texture \"" + pathTextureSpeciale + "\"";
    throw std::exception(erreur.c_str());
  }
}

void Jeu::chargerCases() {
  chargerTexturesCases();
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {

      float x, y;
      x = j * LARGEUR_CASE;
      y = i * HAUTEUR_CASE;
      sf::Vector2f positionTexture(x, y);

      m_plancheDeJeu[i][j].m_sprite = sf::Sprite(*m_textureCase);
      m_plancheDeJeu[i][j].m_sprite.setPosition(positionTexture);
      m_plancheDeJeu[i][j].m_position = positionTexture;
    }
  }
  m_plancheDeJeu[9][0].m_sprite.setTexture(*m_textureCaseSpeciale);
  m_plancheDeJeu[0][0].m_sprite.setTexture(*m_textureCaseSpeciale);
}

void Jeu::chargerTexteCases() {
  m_textFont = new sf::Font;
  std::string path;

#ifdef _WIN32
  path = "assets\\fonts\\pixelated\\pixelated.ttf";
#else
  path = "assets/fonts/pixelated/pixelated.ttf";
#endif // _WIN32

  if (!m_textFont->loadFromFile(path)) {
    std::string erreur = "Impossible de charger la police \"" + path + "\"";
    throw std::exception(erreur.c_str());
  }

  unsigned noCase = 99;

  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      float x, y;
      x = j * LARGEUR_CASE + 7.0f;
      y = i * HAUTEUR_CASE;

      sf::Vector2f positionTexte(x, y);

      m_plancheDeJeu[i][j].m_text.setFont(*m_textFont);
      m_plancheDeJeu[i][j].m_text.setFillColor(sf::Color(255, 255, 255, 255));
      m_plancheDeJeu[i][j].m_text.setScale(0.7f, 0.7f);
      m_plancheDeJeu[i][j].m_text.setPosition(positionTexte);

      if (i % 2) {
        m_plancheDeJeu[i][9 - j].m_text.setString(std::to_string(noCase));
      } else {
        m_plancheDeJeu[i][j].m_text.setString(std::to_string(noCase));
      }

      noCase--;
    }
  }
  m_plancheDeJeu[9][0].m_text.setString("Depart");
  m_plancheDeJeu[0][0].m_text.setString("Fin");
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
