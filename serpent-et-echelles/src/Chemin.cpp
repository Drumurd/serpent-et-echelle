#include "Chemin.hpp"

/////////////////////////////////////////////////////// public

Chemin::Chemin()
    : m_caseBas(0), m_caseHaut(0), m_type(Type::serpent), m_suivant(nullptr) {}

Chemin::Chemin(unsigned int caseHaut, unsigned int caseBas, Type type)
    : m_caseBas(caseBas), m_caseHaut(caseHaut), m_offset(40.f, 40.f),
      m_type(type), m_suivant(nullptr) {
  chargerSprite();
  placerSurCases();
}

Chemin::~Chemin() {}

void Chemin::determinerSuivant(Chemin *suivant) { m_suivant = suivant; }

Chemin *Chemin::obtenirSuivant() const { return m_suivant; }

unsigned int Chemin::obtenirCaseHaut() const { return m_caseHaut; }
unsigned int Chemin::obtenirCaseBas() const { return m_caseBas; }

Chemin::Type Chemin::obtenirType() const { return m_type; }

void Chemin::afficher(sf::RenderWindow *window) { window->draw(m_sprite); }

void Chemin::placerSurCases() {
  sf::Vector2f positionHaut;
  sf::Vector2f positionBas;

  float c, rotation;

  sf::Vector2f scale;

  calculerPosition(positionHaut, positionBas);
  rotation = calculerRotation(positionHaut, positionBas, c);
  scale = calculerScale(c, rotation);

  m_sprite.setRotation(rotation);
  m_sprite.setPosition(positionHaut);
  m_sprite.setScale(scale);
}

void Chemin::calculerPosition(sf::Vector2f &positionHaut,
                              sf::Vector2f &positionBas) {

  positionHaut.x = (NumeroCaseALigne(m_caseHaut) * LARGEUR_CASE) + m_offset.x;
  positionHaut.y = (NumeroCaseAColone(m_caseHaut) * HAUTEUR_CASE) + m_offset.y;

  positionBas.x = (NumeroCaseALigne(m_caseBas) * LARGEUR_CASE) + m_offset.x;
  positionBas.y = (NumeroCaseAColone(m_caseBas) * HAUTEUR_CASE) + m_offset.y;
}

float Chemin::calculerRotation(const sf::Vector2f &positionHaut,
                               const sf::Vector2f &positionBas, float &c) {
  float a, b;
  const float pi = 3.14159265358979f;

  // notre bel ami pythagore
  a = positionHaut.x - positionBas.x;
  b = positionBas.y - positionHaut.y;

  c = std::sqrt(std::pow(a, 2) + std::pow(b, 2));

  // moi je croyait ne pas avoir à réutiliser ça après le secondaire :(
  return std::asin(a / c) * 180.f / pi;
}

sf::Vector2f Chemin::calculerScale(const float &c, const float &rotation) {
  sf::Vector2f scale;

  switch (m_type) {
  case Chemin::Type::serpent:
    scale.x = 0.1f;
    scale.y = c / LONGEUR_SERPENT;
    break;
  case Chemin::Type::echelle:
    scale.x = 0.25f;
    scale.y = c / LONGEUR_ECHELLE;
    break;
  }

  // pour ne pas avoir de serpents la tête en bas
  if (rotation > 0.f) {
    scale.x *= -1.f;
  }

  return scale;
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
