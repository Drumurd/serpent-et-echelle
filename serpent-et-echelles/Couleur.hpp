#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

enum class Couleur {
  bleu = 0,
  jaune = 1,
  orange = 2,
  rose = 3,
  rouge = 4,
  vert = 5,
  nd = -1
};

Couleur intACouleur(int noCouleur);

sf::Color couleurASfColor(const Couleur &couleur);

std::string couleurAString(const Couleur &couleur);

std::ostream &operator<<(std::ostream &os, const Couleur &couleur);