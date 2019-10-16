#include "Chemin.hpp"

/////////////////////////////////////////////////////// public

Chemin::Chemin()
    : m_caseBas(0), m_caseHaut(0), m_suivant(nullptr), m_type(Type::serpent) {}

Chemin::~Chemin() {}