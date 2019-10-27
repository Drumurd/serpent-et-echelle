#include "Liste_Chemin.hpp"

/////////////////////////////////////////////////////// public

Liste_Chemin::Liste_Chemin() : m_premier(nullptr) {}

Liste_Chemin::~Liste_Chemin() { liberer(); }

void Liste_Chemin::afficher(sf::RenderWindow *window) {
  Chemin *courant = m_premier;
  while (courant != nullptr) {
    courant->afficher(window);
    courant = courant->obtenirSuivant();
  }
}

void Liste_Chemin::ajouter(Chemin *chemin) {
  chemin->determinerSuivant(m_premier);
  m_premier = chemin;
}

void Liste_Chemin::liberer() {
  Chemin *courant = m_premier;
  while (courant != nullptr) {
    Chemin *aSupprimer = courant;
    courant = courant->obtenirSuivant();
    delete aSupprimer;
  }
}

Chemin *Liste_Chemin::chercherBas(const unsigned int caseAChercher) {
  Chemin *courant = m_premier;
  while (courant != nullptr) {
    if (courant->obtenirCaseBas() == caseAChercher)
      break;
    courant = courant->obtenirSuivant();
  }

  // retourne nullptr si rien n'est trouvé
  return courant;
}
Chemin *Liste_Chemin::chercherHaut(const unsigned int caseAChercher) {
  Chemin *courant = m_premier;
  while (courant != nullptr) {
    if (courant->obtenirCaseHaut() == caseAChercher)
      break;
    courant = courant->obtenirSuivant();
  }

  // retourne nullptr si rien n'est trouvé
  return courant;
}
