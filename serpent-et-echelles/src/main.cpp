#include "Jeu.hpp"

int main(int argc, char **argv) {

  Jeu *SerpentEtEchelle = new Jeu();

  try {
    SerpentEtEchelle->demarrer();
  } catch (const std::exception &exc) {
    std::cerr << exc.what();
  }

  return 0;
}