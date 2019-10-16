#pragma once

#include <SFML/Graphics.hpp>

#include "Joueur.hpp"

class Liste_Joueur {

public:
  Liste_Joueur();
  ~Liste_Joueur();

  void afficher(sf::RenderWindow *window);

  void ajouter(Joueur *joueur);
  void liberer();

private:
  Joueur *m_premier;
};
