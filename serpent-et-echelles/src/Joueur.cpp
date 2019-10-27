#include "Joueur.hpp"

/////////////////////////////////////////////////////// public

Joueur::Joueur()
    : m_caseActuelle(0u), m_pileDestinations(), m_profondeurPile(0u),
      m_couleur(Couleur::nd), m_nom(), m_offset(0.f, 0.f), m_suivant(nullptr) {}

Joueur::Joueur(const Couleur &couleur, const std::string &nom)
    : m_caseActuelle(0u), m_pileDestinations(), m_profondeurPile(0u),
      m_couleur(couleur), m_nom(nom), m_offset(0.f, 0.f), m_suivant(nullptr) {
  chargerSprite();
  determinerOffset();
  placerDansCase(0u);
}

Joueur::~Joueur() {}

void Joueur::placerDansCase(unsigned int numeroCase) {
  sf::Vector2f coordonees;

  // on s'assure de ne pas dépasser le jeu
  if (numeroCase > 99u)
    numeroCase = 99u;
  if (numeroCase < 0u)
    numeroCase = 0u;

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

void Joueur::ajouterDestination(const unsigned int noCase) {
  if (m_profondeurPile == 7u) {
    throw std::runtime_error("Buffer overflow");
  }
  m_pileDestinations[m_profondeurPile] = noCase;
  m_profondeurPile++;
}

void Joueur::afficher(sf::RenderWindow *window) { window->draw(m_sprite); }

// retourne true si l'animation est terminée
bool Joueur::update() {
  if (m_profondeurPile == 0u) {
    return true;
  }

  sf::Vector2f positionActuelle;
  sf::Vector2f destination;

  static sf::Vector2f distance;

  positionActuelle.x = m_sprite.getGlobalBounds().left;
  positionActuelle.y = m_sprite.getGlobalBounds().top;

  destination.x = (NumeroCaseALigne(m_pileDestinations[m_profondeurPile - 1u]) *
                   LARGEUR_CASE) +
                  m_offset.x;
  destination.y =
      (NumeroCaseAColone(m_pileDestinations[m_profondeurPile - 1u]) *
       HAUTEUR_CASE) +
      m_offset.y;

  if (distance == sf::Vector2f(0.f, 0.f)) // si la distance a été réinitialisée
    distance = destination - positionActuelle;

  positionActuelle += distance * VITESSE_JOUEUR;

  m_sprite.setPosition(positionActuelle);

  if (destination == positionActuelle) {
    distance = sf::Vector2f(0.f, 0.f); // reinitialiser la distance
    m_profondeurPile--;
    m_caseActuelle = m_pileDestinations[m_profondeurPile];
  }
  return false;
}

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
