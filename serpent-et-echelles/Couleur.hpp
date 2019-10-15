#pragma once

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

std::ostream& operator<<(std::ostream& os, const Couleur& couleur);