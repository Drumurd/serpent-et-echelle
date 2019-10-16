#include "Chemin.hpp"

/////////////////////////////////////////////////////// public

Chemin::Chemin()
    : m_caseBas(0), m_caseHaut(0), m_type(Type::serpent), m_suivant(nullptr) {}

Chemin::Chemin(unsigned int caseHaut, unsigned int caseBas, Type type)
    : m_caseBas(caseBas), m_caseHaut(caseHaut), m_type(type),
      m_suivant(nullptr) {
  chargerSprite();
  placerSurCases();
}

Chemin::~Chemin() {}

void Chemin::determinerSuivant(Chemin *suivant) { m_suivant = suivant; }

Chemin *Chemin::obtenirSuivant() const { return m_suivant; }

unsigned int Chemin::obtenirCaseHaut() const { return m_caseHaut; }
unsigned int Chemin::obtenirCaseBas() const { return m_caseBas; }

void Chemin::afficher(sf::RenderWindow *window) { window->draw(m_sprite); }

void Chemin::placerSurCases() {
  sf::Vector2f positionHaut;
  sf::Vector2f positionBas;

  sf::Vector2f distanceCases;
  sf::Vector2f scale;

  m_offsetCaseHaut = sf::Vector2f(40.0f, 40.0f);

  m_offsetCaseBas = sf::Vector2f(40.0f, 40.0f);

  positionHaut.x =
      (NumeroCaseALigne(m_caseHaut) * LARGEUR_CASE) + m_offsetCaseHaut.x;
  positionHaut.y =
      (NumeroCaseAColone(m_caseHaut) * HAUTEUR_CASE) + m_offsetCaseHaut.y;

  positionBas.x =
      (NumeroCaseALigne(m_caseBas) * LARGEUR_CASE) + m_offsetCaseBas.x;
  positionBas.y =
      (NumeroCaseAColone(m_caseBas) * HAUTEUR_CASE) + m_offsetCaseBas.y;

  assert(positionBas.y > positionHaut.y);

  distanceCases = positionBas - positionHaut;

  switch (m_type) {
  case Chemin::Type::serpent:
    scale.x = 0.1f;
    scale.y = distanceCases.y / LONGEUR_SERPENT;
    break;
  case Chemin::Type::echelle:
    scale.x = 0.25f;
    scale.y = distanceCases.y / LONGEUR_ECHELLE;
    break;
  }

  m_sprite.setPosition(positionHaut);
  m_sprite.setScale(scale);
}

/////////////////////////////////////////////////////// private

void Chemin::chargerSprite() {
  std::string path;

  switch (m_type) {
  case Chemin::Type::serpent:

#ifdef _WIN32
    path = "assets\\textures\\serpent.jpg";
#else  // linux, mac, unix, etc...
    path = "assets/textures/serpent.jpg";
#endif // _WIN32

    break;
  case Chemin::Type::echelle:

#ifdef _WIN32
    path = "assets\\textures\\echelle.jpg";
#else  // linux, mac, unix, etc...
    path = "assets/textures/echelle.jpg";
#endif // _WIN32

    break;
  default:
    throw std::runtime_error("If you see this message, I seriously f***ed up");
    break;
  }

  if (!m_texture.loadFromFile(path)) {
    std::string erreur = "Impossible de charger la texture \"" + path + "\"";
    throw std::runtime_error(erreur.c_str());
  }

  m_sprite = sf::Sprite(m_texture);
}
