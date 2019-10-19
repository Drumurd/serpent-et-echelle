#include "De.hpp"

/////////////////////////////////////////////////////// public

De::De() {
  m_randomEngine = std::mt19937(m_randomDevice());
  m_distribution = std::uniform_int_distribution<>(1u, 6u);

  chargerTextures();
  initialiserSprite();
}

De::~De() {}

void De::afficher(sf::RenderWindow *window) { window->draw(m_sprite); }

// retourne true à la fin de l'animation
bool De::update() {
  static unsigned int fois = 0u;

  if (fois % 5 == 0)
    brasser();
  fois++;

  if (fois == 90u) {
    fois = 0u;
    return true;
  }
  return false;
}

unsigned int De::obtenirResultat() const { return m_dernierResultat; }

/////////////////////////////////////////////////////// private

void De::chargerTextures() {
  for (unsigned int i = 0u; i < 6u; i++) {
    std::string path;

#ifdef _WIN32 // windows
    path = "assets\\textures\\" + std::to_string(i + 1) + ".jpg";
#else // linux, mac, unix, etc...
    path = "assets/textures/" + std::to_string(i + 1) + ".jpg";
#endif

    if (!m_textures[i].loadFromFile(path)) {
      std::string erreur = "Impossible de charger la texture \"" + path + "\"";
      throw std::runtime_error(erreur.c_str());
    }
  }
}

void De::initialiserSprite() {
  m_sprite = sf::Sprite(m_textures[0]);

  m_sprite.setPosition(707.f, 707.f);
}

void De::brasser() {
  m_dernierResultat = m_distribution(m_randomEngine);

  m_sprite.setTexture(m_textures[m_dernierResultat - 1u]);
}