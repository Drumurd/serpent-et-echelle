#include "Jeu.hpp"

/////////////////////////////////////////////////////// public

Jeu::Jeu()
    : m_window(), m_nbJoueurs(0u), m_event(), m_textureCase(),
      m_textureCaseSpeciale(), m_textFont(), m_etat(Etat::attenteJoueur),
      m_joueurCourant(nullptr) {}

Jeu::~Jeu() { delete m_window; }

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

    std::cout << std::endl << "Quel est le nom du joueur " << i + 1u << "? ";
    std::cin >> nom;

    Joueur *joueur = new Joueur(couleur, nom);
    m_joueurs.ajouter(joueur);

    std::cout << nom << " aura la couleur " << joueur->obtenirCouleur()
              << std::endl;
  }
}

void Jeu::initialiserJeu() {
  m_window =
      new sf::RenderWindow(sf::VideoMode(800, 800), "Serpents et Echelles");

  if (m_window == nullptr) {
    throw std::runtime_error("Impossible de charger la fenetre");
  }

  m_window->setFramerateLimit(60);

  chargerPlancheDeJeu();
  chargerMessages();
  chargerSons();

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
  std::string pathTexture;
  std::string pathTextureSpeciale;

#ifdef _WIN32 // windows
  pathTexture = "assets\\textures\\case.jpg";
  pathTextureSpeciale = "assets\\textures\\case-speciale.jpg";
#else // linux, mac, unix, etc...
  pathTexture = "assets/textures/case.jpg";
  pathTextureSpeciale = "assets/textures/case-speciale.jpg";
#endif

  if (!m_textureCase.loadFromFile(pathTexture)) {
    std::string erreur =
        "Impossible de charger la texture \"" + pathTexture + "\"";
    throw std::runtime_error(erreur.c_str());
  }

  if (!m_textureCaseSpeciale.loadFromFile(pathTextureSpeciale)) {
    std::string erreur =
        "Impossible de charger la texture \"" + pathTextureSpeciale + "\"";
    throw std::runtime_error(erreur.c_str());
  }
}

void Jeu::chargerCases() {
  chargerTexturesCases();
  for (unsigned int i = 0u; i < 10u; i++) {
    for (unsigned int j = 0u; j < 10u; j++) {

      float x, y;
      x = j * LARGEUR_CASE;
      y = i * HAUTEUR_CASE;

      m_plancheDeJeu[i][j].m_sprite = sf::Sprite(m_textureCase);
      m_plancheDeJeu[i][j].m_sprite.setPosition(x, y);
    }
  }
  m_plancheDeJeu[9][0].m_sprite.setTexture(m_textureCaseSpeciale);
  m_plancheDeJeu[0][0].m_sprite.setTexture(m_textureCaseSpeciale);
}

void Jeu::chargerTexteCases() {
  std::string path;

#ifdef _WIN32 // windows
  path = "assets\\fonts\\press_start_2p\\PressStart2P.ttf";
#else // linux, mac, unix, etc...
  path = "assets/fonts/press_start_2p/PressStart2P.ttf";
#endif

  if (!m_textFont.loadFromFile(path)) {
    std::string erreur = "Impossible de charger la police \"" + path + "\"";
    throw std::runtime_error(erreur.c_str());
  }

  unsigned noCase = 99u;

  for (unsigned int i = 0u; i < 10u; i++) {
    for (unsigned int j = 0u; j < 10u; j++) {
      float x, y;
      x = j * LARGEUR_CASE + 7.f;
      y = i * HAUTEUR_CASE + 7.f;

      m_plancheDeJeu[i][j].m_text.setFont(m_textFont);
      m_plancheDeJeu[i][j].m_text.setFillColor(sf::Color(255, 255, 255, 255));
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
  m_message1.setFont(m_textFont);
  m_message1.setPosition(10.f, 710.f);
  m_message1.setScale(0.7f, 0.7f);

  m_message2.setFont(m_textFont);
  m_message2.setPosition(10.f, 755.f);
  m_message2.setScale(0.4f, 0.4f);
}

void Jeu::chargerCheminsStatiques() {
  Chemin *chemin;

  chemin = new Chemin(99u, 78u, Chemin::Type::echelle);
  m_chemins.ajouter(chemin);

  chemin = new Chemin(23u, 2u, Chemin::Type::echelle);
  m_chemins.ajouter(chemin);

  chemin = new Chemin(72u, 48u, Chemin::Type::echelle);
  m_chemins.ajouter(chemin);

  chemin = new Chemin(63u, 44u, Chemin::Type::echelle);
  m_chemins.ajouter(chemin);

  chemin = new Chemin(86u, 65u, Chemin::Type::echelle);
  m_chemins.ajouter(chemin);

  chemin = new Chemin(27u, 11u, Chemin::Type::echelle);
  m_chemins.ajouter(chemin);

  chemin = new Chemin(95u, 62u, Chemin::Type::serpent);
  m_chemins.ajouter(chemin);

  chemin = new Chemin(38u, 0u, Chemin::Type::serpent);
  m_chemins.ajouter(chemin);

  chemin = new Chemin(45u, 32u, Chemin::Type::serpent);
  m_chemins.ajouter(chemin);
}

void Jeu::chargerSons() {
  std::string pathEchelle;
  std::string pathSerpent;

#ifdef _WIN32 // windows
  pathEchelle = "assets\\sounds\\echelle.ogg";
#else // linux, mac, unix, etc...
  pathEchelle = "assets/sounds/echelle.ogg";
#endif
#ifdef _WIN32 // windows
  pathSerpent = "assets\\sounds\\serpent.ogg";
#else // linux, mac, unix, etc...
  pathSerpent = "assets/sounds/serpent.ogg";
#endif

  if (!m_bufferSonEchelle.loadFromFile(pathEchelle)) {
    std::string erreur = "Impossible de charger le son \"" + pathEchelle + "\"";
    throw std::runtime_error(erreur.c_str());
  }

  if (!m_bufferSonSerpent.loadFromFile(pathSerpent)) {
    std::string erreur = "Impossible de charger le son \"" + pathSerpent + "\"";
    throw std::runtime_error(erreur.c_str());
  }

  m_sonEchelle.setBuffer(m_bufferSonEchelle);
  m_sonSerpent.setBuffer(m_bufferSonSerpent);
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
          m_etat = Etat::brassageDe;
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
  m_window->clear(sf::Color(0, 0, 0, 255));

  afficherCases();
  m_chemins.afficher(m_window);
  m_joueurs.afficher(m_window);

  afficherNumeroCases();
  afficherMessage();

  m_de.afficher(m_window);

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

void Jeu::jouerTour() {
  unsigned int resultatDe = m_de.obtenirResultat();

  unsigned int emplacement =
      m_joueurCourant->obtenirCaseCourante() + resultatDe;
  if (emplacement > 99u)
    emplacement = 99u;

  for (unsigned int i = 0u;
       i < emplacement - m_joueurCourant->obtenirCaseCourante(); i++) {
    m_joueurCourant->ajouterDestination(emplacement - i);
  }
}

bool Jeu::verifierChemins() {
  unsigned int emplacement = m_joueurCourant->obtenirCaseCourante();

  Chemin *chemin = m_chemins.chercherBas(emplacement);

  if (chemin == nullptr) { // aucun chemin avec la case du bas à l'emplacement

    chemin = m_chemins.chercherHaut(emplacement); // on cherche en haut

    if (chemin != nullptr) { // un chemin avec la case du haut à l'emplacement
      if (chemin->obtenirType() == Chemin::Type::serpent) {
        // Si le chemin est un serpent, on descend
        m_joueurCourant->ajouterDestination(chemin->obtenirCaseBas());
        m_sonSerpent.play();
        return true;
      }
    }
  } else { // si il y a un chemin avec la case du haut à l'emplacement
    if (chemin->obtenirType() == Chemin::Type::echelle) {
      // si on a une échelle, on monte
      m_joueurCourant->ajouterDestination(chemin->obtenirCaseHaut());
      m_sonEchelle.play();
      return true;
    }
  }
  return false;
}

void Jeu::update() {
  switch (m_etat) {

  case Jeu::Etat::brassageDe:
    if (m_de.update()) { // si l'animation du dé est terminée
      jouerTour();
      m_etat = Etat::mouvementJoueur;
    }
    break;
  case Jeu::Etat::mouvementJoueur:

    if (m_joueurCourant->update()) { // si l'animation du joueur est terminee

      if (!verifierChemins()) { // si il n'y a pas de chemins
        m_etat = Etat::attenteJoueur;
        if (m_joueurCourant->obtenirCaseCourante() ==
            99u) { // le joueur a gagné
          m_etat = Etat::partieTermine;
        } else {
          m_joueurCourant = m_joueurCourant->obtenirSuivant();
        }
      }
    }

    break;
  }

  updateMessages();
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
    couleur2 = sf::Color(255, 255, 255, 255);
    break;
  case Jeu::Etat::partieTermine:
    message1 = "Partie terminée";
    couleur1 = sf::Color(255, 0, 0, 255);

    message2 = "Appuyez sur 'n' pour lancer une nouvelle partie";
    couleur2 = sf::Color(255, 255, 255, 255);
    break;
  case Jeu::Etat::mouvementJoueur:
    message1 = m_joueurCourant->obtenirNom();
    couleur1 = couleurASfColor(m_joueurCourant->obtenirCouleur());

    message2 = "avance de " + std::to_string(m_de.obtenirResultat()) + " cases";
    couleur2 = sf::Color(255, 255, 255, 255);
    break;
  case Jeu::Etat::brassageDe:
    message1 = "Roulement du dé";
    couleur1 = sf::Color(255, 255, 255, 255);

    message2 = "";
    couleur2 = sf::Color(0, 0, 0, 255);
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
}
