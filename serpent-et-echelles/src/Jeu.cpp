#include "Jeu.hpp"

/////////////////////////////////////////////////////// public

Jeu::Jeu()
    : m_window(), m_nbJoueurs(0u), m_event(), m_textureCase(nullptr),
      m_textureCaseSpeciale(nullptr), m_textFont(nullptr),
      m_etat(Etat::attenteJoueur), m_joueurCourant(nullptr) {}

Jeu::~Jeu() {
  delete m_window;

  delete m_textureCase;
  delete m_textureCaseSpeciale;

  delete m_textFont;
}

void Jeu::demarrer() {

  entrerInfoJoueurs();
  initialiserJeu();
  bouclePrincipale();
}

/////////////////////////////////////////////////////// private

void Jeu::entrerInfoJoueurs() {

  bool valide(false);

  while (!valide) {
    std::cout << "Combien de joueurs ? ";

    std::cin >> m_nbJoueurs;

    // empecher les caracteres de déborder
    std::cin.clear();
    std::cin.ignore(10000, '\n');

    if (m_nbJoueurs < 2u || m_nbJoueurs > 6u)
      std::cout << "Le nombre de joueurs doit etre entre 2 et 6" << std::endl;
    else
      valide = true;
  }

  for (unsigned int i = 0u; i < m_nbJoueurs; i++) {
    std::string nom("");
    Couleur couleur(intACouleur(i));

    std::cout << std::endl << "Quel est le nom du joueur " << i + 1 << "? ";
    std::cin >> nom;

    Joueur *joueur = new Joueur(couleur, nom);
    m_joueurs.ajouter(joueur);

    std::cout << nom << " aura la couleur " << joueur->obtenirCouleur()
              << std::endl;
  }
}

void Jeu::initialiserJeu() {
  m_window =
      new sf::RenderWindow(sf::VideoMode(800u, 800u), "Serpents et Echelles");

  if (m_window == nullptr) {
    throw std::runtime_error("Impossible de charger la fenetre");
  }

  m_window->setFramerateLimit(60u);

  chargerPlancheDeJeu();
  chargerMessages();

  m_joueurCourant = m_joueurs.obtenirPremier();
}

void Jeu::redemarrerJeu() {
  m_joueurs.replacer();
  m_joueurCourant = m_joueurs.obtenirPremier();

  m_etat = Etat::attenteJoueur;
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

#ifdef _WIN32 // windows
  pathTexture = "assets\\textures\\case.jpg";
  pathTextureSpeciale = "assets\\textures\\case-speciale.jpg";
#else // linux, mac, unix, etc...
  pathTexture = "assets/textures/case.jpg";
  pathTextureSpeciale = "assets/textures/case-speciale.jpg";
#endif

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

      m_plancheDeJeu[i][j].m_sprite = sf::Sprite(*m_textureCase);
      m_plancheDeJeu[i][j].m_sprite.setPosition(x, y);
    }
  }
  m_plancheDeJeu[9][0].m_sprite.setTexture(*m_textureCaseSpeciale);
  m_plancheDeJeu[0][0].m_sprite.setTexture(*m_textureCaseSpeciale);
}

void Jeu::chargerTexteCases() {
  m_textFont = new sf::Font;
  std::string path;

#ifdef _WIN32 // windows
  path = "assets\\fonts\\press_start_2p\\PressStart2P.ttf";
#else // linux, mac, unix, etc...
  path = "assets/fonts/press_start_2p/PressStart2P.ttf";
#endif

  if (!m_textFont->loadFromFile(path)) {
    std::string erreur = "Impossible de charger la police \"" + path + "\"";
    throw std::runtime_error(erreur.c_str());
  }

  unsigned noCase = 99u;

  for (unsigned int i = 0u; i < 10u; i++) {
    for (unsigned int j = 0u; j < 10u; j++) {
      float x, y;
      x = j * LARGEUR_CASE + 7.f;
      y = i * HAUTEUR_CASE + 7.f;

      m_plancheDeJeu[i][j].m_text.setFont(*m_textFont);
      m_plancheDeJeu[i][j].m_text.setFillColor(
          sf::Color(255u, 255u, 255u, 255u));
      m_plancheDeJeu[i][j].m_text.setScale(0.35f, 0.35f);
      m_plancheDeJeu[i][j].m_text.setPosition(x, y);

      if (i % 2) { // placer en alternant la direction des nombres
        m_plancheDeJeu[i][9 - j].m_text.setString(std::to_string(noCase));
      } else {
        m_plancheDeJeu[i][j].m_text.setString(std::to_string(noCase));
      }

      noCase--;
    }
  }

  // cases spéciales
  m_plancheDeJeu[9][0].m_text.setString("Depart");
  m_plancheDeJeu[0][0].m_text.setString("Fin");
}

void Jeu::chargerMessages() {
  m_message1.setFont(*m_textFont);
  m_message1.setPosition(10.f, 710.f);
  m_message1.setScale(0.7f, 0.7f);

  m_message2.setFont(*m_textFont);
  m_message2.setPosition(10.f, 750.f);
  m_message2.setScale(0.5f, 0.5f);
}

void Jeu::chargerCheminsStatiques() {
  Chemin *chemin;

  chemin = new Chemin(99u, 78u, Chemin::Type::echelle);
  m_chemins.ajouter(chemin);

  chemin = new Chemin(23u, 2u, Chemin::Type::echelle);
  m_chemins.ajouter(chemin);

  chemin = new Chemin(72u, 48u, Chemin::Type::echelle);
  m_chemins.ajouter(chemin);

  chemin = new Chemin(95u, 62u, Chemin::Type::serpent);
  m_chemins.ajouter(chemin);

  chemin = new Chemin(38u, 0u, Chemin::Type::serpent);
  m_chemins.ajouter(chemin);

  chemin = new Chemin(45u, 32u, Chemin::Type::serpent);
  m_chemins.ajouter(chemin);
}

void Jeu::bouclePrincipale() {
  while (m_window->isOpen()) {
    gererInput();
    update();
    afficher();
  }
}

void Jeu::gererInput() {
  while (m_window->pollEvent(m_event)) {
    switch (m_event.type) {
    case sf::Event::Closed:
      m_window->close();
      break;

    case sf::Event::KeyReleased:

      switch (m_event.key.code) {
      case sf::Keyboard::Space:
        if (m_etat == Etat::attenteJoueur) {
          jouerTour(m_joueurCourant);
        }
        break;

      case sf::Keyboard::N:
        if (m_etat == Etat::partieTermine) {
          redemarrerJeu();
        }
        break;
      }
      break;
    }
  }
}

void Jeu::afficher() {
  m_window->clear(sf::Color(0u, 0u, 0u, 255u));

  afficherCases();
  m_chemins.afficher(m_window);
  m_joueurs.afficher(m_window);

  afficherNumeroCases();
  afficherMessage();

  m_window->display();
}

void Jeu::afficherCases() {
  for (unsigned int i = 0u; i < 10u; i++) {
    for (unsigned int j = 0u; j < 10u; j++) {
      m_window->draw(m_plancheDeJeu[i][j].m_sprite);
    }
  }
}

void Jeu::afficherNumeroCases() {
  for (unsigned int i = 0u; i < 10u; i++) {
    for (unsigned int j = 0u; j < 10u; j++) {
      m_window->draw(m_plancheDeJeu[i][j].m_text);
    }
  }
}

void Jeu::afficherMessage() {
  m_window->draw(m_message1);
  m_window->draw(m_message2);
}

void Jeu::jouerTour(Joueur *joueur) {
  unsigned int resultatDe = m_de.brasser();

  effectuerDeplacements(joueur, resultatDe);

  if (m_joueurCourant->obtenirCaseCourante() == 99u) { // le joueur a gagné
    m_etat = Etat::partieTermine;
  }

  m_joueurCourant = joueur->obtenirSuivant();

  std::cout << resultatDe << std::endl;
}

void Jeu::effectuerDeplacements(Joueur *joueur, const unsigned int resultatDe) {
  unsigned int emplacement = joueur->obtenirCaseCourante() + resultatDe;

  joueur->placerDansCase(emplacement);

  Chemin *chemin = m_chemins.chercherBas(emplacement);

  if (chemin == nullptr) { // aucun chemin avec la case du bas à l'emplacement

    chemin = m_chemins.chercherHaut(emplacement); // on cherche en haut

    if (chemin != nullptr) { // un chemin avec la case du haut à l'emplacement
      if (chemin->obtenirType() == Chemin::Type::serpent) {
        // Si le chemin est un serpent, on descend
        joueur->placerDansCase(chemin->obtenirCaseBas());
      }
    }
  } else { // si il y a un chemin avec la case du haut à l'emplacement
    if (chemin->obtenirType() == Chemin::Type::echelle) {
      // si on a une échelle, on monte
      joueur->placerDansCase(chemin->obtenirCaseHaut());
    }
  }
}

void Jeu::update() {
  updateMessages();
  m_joueurs.update();
}

void Jeu::updateMessages() {
  std::string message1;
  std::string message2;

  sf::Color couleur1;
  sf::Color couleur2;

  switch (m_etat) {
  case Jeu::Etat::attenteJoueur:
    message1 = "C'est au tour de " + m_joueurCourant->obtenirNom();
    couleur1 = couleurASfColor(m_joueurCourant->obtenirCouleur());

    message2 = "Appuyer sur espace pour lancer le dé";
    couleur2 = sf::Color(255u, 255u, 255u, 255u);
    break;
  case Jeu::Etat::partieTermine:
    message1 = "Partie terminée";
    couleur1 = sf::Color(255u, 0u, 0u, 255u);

    message2 = "Appuyez sur 'n' pour lancer une nouvelle partie";
    couleur2 = sf::Color(255u, 255u, 255u, 255u);
    break;

  default:
    message1 = "";
    couleur1 = sf::Color(0u, 0u, 0u, 255u);

    message2 = "";
    couleur2 = sf::Color(0u, 0u, 0u, 255);
    break;
  }

  m_message1.setString(message1);
  m_message1.setFillColor(couleur1);

  m_message2.setString(message2);
  m_message2.setFillColor(couleur2);
}
