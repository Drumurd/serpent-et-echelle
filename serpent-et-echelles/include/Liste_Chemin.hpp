#pragma once

#include "Chemin.hpp"
#include <SFML/Graphics.hpp>

class Liste_Chemin {

public:
  Liste_Chemin();
  ~Liste_Chemin();

  void afficher(sf::RenderWindow *window);
  void ajouter(Chemin *chemin);
  void liberer();

  Chemin *chercherBas(const unsigned int caseAChercher);
  Chemin *chercherHaut(const unsigned int caseAChercher);

private:
  Chemin *m_premier;
};
