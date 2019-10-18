#include "Joueur.hpp"

/////////////////////////////////////////////////////// public

Joueur::Joueur()
    : m_caseActuelle(0u), m_couleur(Couleur::nd), m_nom(""), m_offset(0.f, 0.f),
      m_suivant(nullptr) {}

Joueur::Joueur(const Couleur &couleur, const std::string &nom)
    : m_caseActuelle(0u), m_couleur(couleur), m_nom(nom), m_offset(0.f, 0.f),
      m_suivant(nullptr) {
  chargerSprite();
  determinerOffset();
  placerDansCase(0);
}

Joueur::~Joueur() {}

void Joueur::placerDansCase(unsigned int numeroCase) {
  sf::Vector2f coordonees;

  // on s'assure de ne pas dépasser le jeu
  if (numeroCase > 99u)
    numeroCase = 99u;

  unsigned int x = NumeroCaseALigne(numeroCase);
  unsigned int y = NumeroCaseAColone(numeroCase);

  coordonees.x = x * LARGEUR_CASE;
  coordonees.y = y * HAUTEUR_CASE;

  coordonees += m_offset;

  m_sprite.setPosition(coordonees);
  m_caseActuelle = numeroCase;
}

void Joueur::determinerSuivant(Joueur *suivant) { m_suivant = suivant; }

Joueur *Joueur::obtenirSuivant() const { return m_suivant; }

Couleur Joueur::obtenirCouleur() const { return m_couleur; }

sf::Sprite Joueur::obtenirSprite() const { return m_sprite; }

std::string Joueur::obtenirNom() const { return m_nom; }

unsigned int Joueur::obtenirCaseCourante() const { return m_caseActuelle; }

void Joueur::afficher(sf::RenderWindow *window) { window->draw(m_sprite); }

void Joueur::update() {}

/////////////////////////////////////////////////////// private

void Joueur::chargerSprite() {
  std::string path;

#ifdef _WIN32 // windows
  path = "assets\\textures\\joueur-" + couleurAString(m_couleur) + ".jpg";
#else // linux, mac, unix, etc...
  path = "assets/textures/joueur-" + couleurAString(m_couleur) + ".jpg";
#endif

  if (!m_texture.loadFromFile(path)) {
    std::string erreur = "Impossible de charger la texture \"" + path + "\"";
    throw std::runtime_error(erreur.c_str());
  }

  m_sprite = sf::Sprite(m_texture);
}

void Joueur::determinerOffset() {
  switch (m_couleur) {
  case Couleur::bleu:
    m_offset = sf::Vector2f(8.f, 22.f);
    break;
  case Couleur::jaune:
    m_offset = sf::Vector2f(32.f, 22.f);
    break;
  case Couleur::orange:
    m_offset = sf::Vector2f(56.f, 22.f);
    break;
  case Couleur::rose:
    m_offset = sf::Vector2f(8.f, 45.f);
    break;
  case Couleur::rouge:
    m_offset = sf::Vector2f(32.f, 45.f);
    break;
  case Couleur::vert:
    m_offset = sf::Vector2f(56.f, 45.f);
    break;
  default:
    m_offset = sf::Vector2f(0.f, 0.f);
    break;
  }
}
