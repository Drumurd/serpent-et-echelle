#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

enum class Couleur { bleu, jaune, orange, rose, rouge, vert, nd };

Couleur intACouleur(unsigned int noCouleur);

sf::Color couleurASfColor(const Couleur &couleur);

std::string couleurAString(const Couleur &couleur);

std::ostream &operator<<(std::ostream &os, const Couleur &couleur);