#include "Chemin.hpp"

/////////////////////////////////////////////////////// public

Chemin::Chemin()
    : m_caseBas(0), m_caseHaut(0), m_type(Type::serpent), m_suivant(nullptr) {}

Chemin::Chemin(unsigned int caseHaut, unsigned int caseBas, Type type)
    : m_caseBas(caseBas), m_caseHaut(caseHaut), m_type(type),
      m_suivant(nullptr) {}

Chemin::~Chemin() {}

void Chemin::determinerSuivant(Chemin *suivant) { m_suivant = suivant; }

Chemin *Chemin::obtenirSuivant() const { return m_suivant; }

unsigned int Chemin::obtenirCaseHaut() const { return m_caseHaut; }
unsigned int Chemin::obtenirCaseBas() const { return m_caseBas; }

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
