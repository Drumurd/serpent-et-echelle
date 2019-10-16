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

  Joueur *obtenirPremier() const;

private:
  Joueur *m_premier;
};
