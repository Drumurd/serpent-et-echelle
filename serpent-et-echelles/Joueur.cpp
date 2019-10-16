#include "Joueur.hpp"

/////////////////////////////////////////////////////// public

Joueur::Joueur()
    : m_caseActuelle(0), m_couleur(Couleur::nd), m_nom(""), m_offset(0, 0),
      m_suivant(nullptr) {}

Joueur::Joueur(const Couleur &couleur, const std::string &nom)
    : m_caseActuelle(0), m_couleur(couleur), m_nom(nom), m_offset(0, 0),
      m_suivant(nullptr) {
  chargerSprite();
  determinerOffset();
  placerDansCase(0);
}

Joueur::~Joueur() {}

void Joueur::placerDansCase(const unsigned int &numeroCase) {
  sf::Vector2f coordonees;

  unsigned int x = NumeroCaseALigne(numeroCase);
  unsigned int y = NumeroCaseAColone(numeroCase);

  coordonees.x = x * LARGEUR_CASE;
  coordonees.y = y * HAUTEUR_CASE;

  coordonees += m_offset;

  placerACoordonees(coordonees);
}

void Joueur::placerACoordonees(const sf::Vector2f &position) {
  m_sprite.setPosition(position);
}

void Joueur::determinerSuivant(Joueur *suivant) { m_suivant = suivant; }

Joueur *Joueur::obtenirSuivant() const { return m_suivant; }

Couleur Joueur::obtenirCouleur() const { return m_couleur; }

sf::Sprite Joueur::obtenirSprite() const { return m_sprite; }

std::string Joueur::obtenirNom() const { return m_nom; }

void Joueur::afficher(sf::RenderWindow *window) { window->draw(m_sprite); }

/////////////////////////////////////////////////////// private

void Joueur::chargerSprite() {
  std::string path;

#ifdef _WIN32
  path = "assets\\textures\\joueur-" + couleurAString(m_couleur) + ".jpg";
#else  // linux, mac, unix, etc...
  path = "assets/textures/joueur-" + couleurAString(m_couleur) + ".jpg";
#endif // _WIN32

  if (!m_texture.loadFromFile(path)) {
    std::string erreur = "Impossible de charger la texture \"" + path + "\"";
    throw std::exception(erreur.c_str());
  }

  m_sprite = sf::Sprite(m_texture);
}

void Joueur::determinerOffset() {
  switch (m_couleur) {
  case Couleur::bleu:
    m_offset = sf::Vector2f(8.0f, 22.0f);
    break;
  case Couleur::jaune:
    m_offset = sf::Vector2f(32.0f, 22.0f);
    break;
  case Couleur::orange:
    m_offset = sf::Vector2f(56.0f, 22.0f);
    break;
  case Couleur::rose:
    m_offset = sf::Vector2f(8.0f, 45.0f);
    break;
  case Couleur::rouge:
    m_offset = sf::Vector2f(32.0f, 45.0f);
    break;
  case Couleur::vert:
    m_offset = sf::Vector2f(56.0f, 45.0f);
    break;
  default:
    m_offset = sf::Vector2f(0.0f, 0.0f);
    break;
  }
}
