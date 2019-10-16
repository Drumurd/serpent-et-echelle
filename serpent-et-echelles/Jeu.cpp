#include "Jeu.hpp"

/////////////////////////////////////////////////////// public

Jeu::Jeu()
    : m_window(), m_nbJoueurs(0), m_event(), m_textureCase(nullptr),
      m_textureCaseSpeciale(nullptr), m_textFont(nullptr),
      m_etat(Etat::attenteJoueur), m_joueurCourant(nullptr) {}

Jeu::~Jeu() {
  delete m_window;

  delete m_textureCase;
  delete m_textureCaseSpeciale;

  delete m_textFont;
}

void Jeu::demarrer() {

  std::srand((unsigned)std::time(NULL));

  entrerInfoJoueurs();
  initialiserJeu();
  bouclePrincipale();
}

/////////////////////////////////////////////////////// private

void Jeu::entrerInfoJoueurs() {

  m_nbJoueurs = 0;
  bool valide(false);

  while (!valide) {
    std::cout << "Combien de joueurs ? ";

    std::cin >> m_nbJoueurs;

    // empecher les caracteres de déborder
    std::cin.clear();
    std::cin.ignore(10000, '\n');

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
    throw std::runtime_error("Impossible de charger la fenêtre");
  }

  m_window->setVerticalSyncEnabled(true);

  chargerPlancheDeJeu();
  chargerMessages();

  m_joueurCourant = m_joueurs.obtenirPremier();
}

void Jeu::chargerPlancheDeJeu() {
  chargerCases();
  chargerTexteCases();
  chargerCheminsStatiques();
}

void Jeu::chargerTexturesCases() {
  m_textureCase = new sf::Texture();
  m_textureCaseSpeciale = new sf::Texture();

  std::string pathTexture;
  std::string pathTextureSpeciale;

#ifdef _WIN32
  pathTexture = "assets\\textures\\case.jpg";
  pathTextureSpeciale = "assets\\textures\\case-speciale.jpg";
#else  // linux, mac, unix, etc...
  pathTexture = "assets/textures/case.jpg";
  pathTextureSpeciale = "assets/textures/case-speciale.jpg";
#endif // _WIN32

  if (!m_textureCase->loadFromFile(pathTexture)) {
    std::string erreur =
        "Impossible de charger la texture \"" + pathTexture + "\"";
    throw std::runtime_error(erreur.c_str());
  }

  if (!m_textureCaseSpeciale->loadFromFile(pathTextureSpeciale)) {
    std::string erreur =
        "Impossible de charger la texture \"" + pathTextureSpeciale + "\"";
    throw std::runtime_error(erreur.c_str());
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
  path = "assets\\fonts\\press_start_2p\\PressStart2P.ttf";
#else  // linux, mac, unix, etc...
  path = "assets/fonts/press_start_2p/PressStart2P.ttf";
#endif // _WIN32

  if (!m_textFont->loadFromFile(path)) {
    std::string erreur = "Impossible de charger la police \"" + path + "\"";
    throw std::runtime_error(erreur.c_str());
  }

  unsigned noCase = 99;

  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      float x, y;
      x = j * LARGEUR_CASE + 7.0f;
      y = i * HAUTEUR_CASE + 7.0f;

      sf::Vector2f positionTexte(x, y);

      m_plancheDeJeu[i][j].m_text.setFont(*m_textFont);
      m_plancheDeJeu[i][j].m_text.setFillColor(sf::Color(255, 255, 255, 255));
      m_plancheDeJeu[i][j].m_text.setScale(0.35f, 0.35f);
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

void Jeu::chargerMessages() {
  m_message1.setFont(*m_textFont);
  m_message1.setPosition(10.0f, 710.0f);
  m_message1.setScale(0.7f, 0.7f);

  m_message2.setFont(*m_textFont);
  m_message2.setPosition(10.0f, 750.0f);
  m_message2.setScale(0.7f, 0.7f);
}

void Jeu::chargerCheminsStatiques() {
  Chemin *chemin;

  chemin = new Chemin(99u, 78u, Chemin::Type::echelle);
  m_chemins.ajouter(chemin);

  chemin = new Chemin(22u, 2, Chemin::Type::echelle);
  m_chemins.ajouter(chemin);

  chemin = new Chemin(72u, 47u, Chemin::Type::echelle);
  m_chemins.ajouter(chemin);

  chemin = new Chemin(95u, 64u, Chemin::Type::serpent);
  m_chemins.ajouter(chemin);

  chemin = new Chemin(39u, 0u, Chemin::Type::serpent);
  m_chemins.ajouter(chemin);

  chemin = new Chemin(51u, 48u, Chemin::Type::serpent);
  m_chemins.ajouter(chemin);
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
  afficherMessage();

  m_window->display();
}

void Jeu::afficherCases() {
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      m_window->draw(m_plancheDeJeu[i][j].m_sprite);
      m_window->draw(m_plancheDeJeu[i][j].m_text);
    }
  }
}

void Jeu::afficherMessage() {
  std::string message1;
  std::string message2;

  sf::Color couleur1;
  sf::Color couleur2;

  switch (m_etat) {
  case Jeu::Etat::attenteJoueur:
    message1 = "C'est au tour de " + m_joueurCourant->obtenirNom();
    couleur1 = couleurASfColor(m_joueurCourant->obtenirCouleur());

    message2 = "Appuyer sur espace pour lancer le dé";
    couleur2 = sf::Color(255, 255, 255, 255);
    break;
  default:
    message1 = "";
    couleur1 = sf::Color(0, 0, 0, 255);

    message2 = "";
    couleur2 = sf::Color(0, 0, 0, 255);
    break;
  }

  m_message1.setString(message1);
  m_message1.setFillColor(couleur1);

  m_message2.setString(message2);
  m_message2.setFillColor(couleur2);

  m_window->draw(m_message1);
  m_window->draw(m_message2);
}
