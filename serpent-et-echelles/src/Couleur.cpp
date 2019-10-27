#include "Couleur.hpp"

Couleur intACouleur(unsigned int noCouleur) {
  switch (noCouleur) {
  case 0u:
    return Couleur::bleu;
  case 1u:
    return Couleur::jaune;
  case 2u:
    return Couleur::orange;
  case 3u:
    return Couleur::rose;
  case 4u:
    return Couleur::rouge;
  case 5u:
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
    return sf::Color(255, 255, 0, 255);
  case Couleur::orange:
    return sf::Color(255, 125, 0, 255);
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

std::string couleurAString(const Couleur &couleur) {
  switch (couleur) {
  case Couleur::bleu:
    return "bleu";
    break;
  case Couleur::jaune:
    return "jaune";
    break;
  case Couleur::orange:
    return "orange";
    break;
  case Couleur::rose:
    return "rose";
    break;
  case Couleur::rouge:
    return "rouge";
    break;
  case Couleur::vert:
    return "vert";
    break;
  default:
    return "couleur non definie";
    break;
  }
}

std::ostream &operator<<(std::ostream &os, const Couleur &couleur) {
  os << couleurAString(couleur);
  return os;
}