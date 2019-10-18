#pragma once

#include <SFML/Graphics.hpp>
#include <random>
#include <string>

class De {
public:
  De();
  ~De();

  void afficher(sf::RenderWindow *window);
  bool update();

  unsigned int obtenirResultat() const;

private:
  std::random_device m_randomDevice;
  std::mt19937 m_randomEngine;
  std::uniform_int_distribution<> m_distribution;

  sf::Texture m_textures[6];
  sf::Sprite m_sprite;

  unsigned int m_dernierResultat;

  void chargerTextures();
  void initialiserSprite();

  void brasser();
};