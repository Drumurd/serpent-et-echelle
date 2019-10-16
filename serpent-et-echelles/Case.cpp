#pragma once

unsigned int NumeroCaseAColone(const unsigned int &numeroCase) {
  // on arrondit à la dixaine la plus basse
  unsigned int numeroColonne = numeroCase - (numeroCase % 10);

  // on un chiffre entre 1 et 9 correspondant à la hauteur de la case
  numeroColonne /= 10;

  // on inverse le resultat pour avoir la même direction que le tableau de cases
  return 9 - numeroColonne;
}

unsigned int NumeroCaseALigne(const unsigned int &numeroCase) {

  // on arrondit à la dixaine la plus basse
  unsigned int numeroColonne = numeroCase - (numeroCase % 10);

  // on un chiffre entre 1 et 9 correspondant à la hauteur de la case
  numeroColonne /= 10;

  unsigned int numeroLigne = numeroCase - (10 * numeroColonne);

  // si la colonne est pair, on inverse le sens de la ligne
  if (numeroColonne % 2) {
    numeroLigne = 9 - numeroLigne;
  }
  return numeroLigne;
}