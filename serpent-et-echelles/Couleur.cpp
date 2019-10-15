#include "Couleur.hpp"

Couleur intACouleur(int noCouleur) {
  switch (noCouleur) {
  case 0:
    return Couleur::bleu;
  case 1:
    return Couleur::jaune;
  case 2:
    return Couleur::orange;
  case 3:
    return Couleur::rose;
  case 4:
    return Couleur::rouge;
  case 5:
    return Couleur::vert;
  default:
    return Couleur::nd;
  }
}

sf::Color couleurASfColor(const Couleur &couleur) {
  switch (couleur) {
  case Couleur::bleu:
    return sf::Color(0, 0, 255, 255);
  case Couleur::jaune:
    return sf::Color(0, 255, 255, 255);
  case Couleur::orange:
    return sf::Color(255, 128, 0, 255);
  case Couleur::rose:
    return sf::Color(255, 0, 255, 255);
  case Couleur::rouge:
    return sf::Color(255, 0, 0, 255);
  case Couleur::vert:
    return sf::Color(0, 255, 0, 255);
  default:
    return sf::Color();
  }
}

std::ostream &operator<<(std::ostream &os, const Couleur &couleur) {
  switch (couleur) {
  case Couleur::bleu:
    os << "bleu";
    break;
  case Couleur::jaune:
    os << "jaune";
    break;
  case Couleur::orange:
    os << "orange";
    break;
  case Couleur::rose:
    os << "rose";
    break;
  case Couleur::rouge:
    os << "rouge";
    break;
  case Couleur::vert:
    os << "vert";
    break;
  case Couleur::nd:
    os << "couleur non définie";
    break;
  }
  return os;
}