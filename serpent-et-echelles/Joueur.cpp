#include "Joueur.hpp"

Joueur::Joueur()
    : m_caseActuelle(0), m_couleur(Couleur::nd), m_nom(""), m_suivant(nullptr) {
}

Joueur::Joueur(const Couleur &couleur, const std::string &nom)
    : m_caseActuelle(0), m_couleur(couleur), m_nom(nom), m_suivant(nullptr) {}

Joueur::~Joueur() {}

void Joueur::chargerSprite() {
  std::string path;

#ifdef _WIN32
  path = "assets\\textures\\joueur-" + couleurAString(m_couleur) + ".jpg";
#else
  path = "assets/textures/joueur-" + couleurAString(m_couleur) + ".jpg";
#endif // _WIN32

  if (!m_texture.loadFromFile(path)) {
    std::string erreur = "Impossible de charger la texture \"" + path + "\"";
    throw std::exception(erreur.c_str());
  }
}

void Joueur::determinerSuivant(Joueur *suivant) { m_suivant = suivant; }

Joueur *Joueur::obtenirSuivant() const { return m_suivant; }

Couleur Joueur::obtenirCouleur() const { return m_couleur; }

sf::Sprite Joueur::obtenirSprite() const { return m_sprite; }
