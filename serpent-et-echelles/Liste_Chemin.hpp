#pragma once

#include "Chemin.hpp"
#include <SFML/Graphics.hpp>

class Liste_Chemin {
private:
  Chemin *m_premier;

public:
  Liste_Chemin();
  ~Liste_Chemin();

  void afficher(sf::RenderWindow *window);
  void ajouter(Chemin chemin);
  void liberer();

  Chemin chercherBas(unsigned int caseAChercher);
  Chemin chercherHaut(unsigned int caseAChercher);
};
