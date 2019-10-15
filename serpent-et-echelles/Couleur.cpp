#include "Couleur.hpp"

Couleur intACouleur(int noCouleur) {
	switch (noCouleur) {
	case 0: return Couleur::bleu;
	case 1: return Couleur::jaune;
	case 2: return Couleur::orange;
	case 3: return Couleur::rose;
	case 4: return Couleur::rouge;
	case 5: return Couleur::vert;
	default: return Couleur::nd;
	}
}

std::ostream& operator<<(std::ostream& os, const Couleur& couleur) {
	switch (couleur)
	{
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