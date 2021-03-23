#ifndef _TabCases2DTas_H
#define _TabCases2DTas_H
#include "Case.h"
class TabCases2DTas
{
public:
	TabCases2DTas(unsigned char dimLignes, unsigned char dimColonnes);
	~TabCases2DTas();
	unsigned char getDimLignes() const;
	unsigned char getDimCol() const;
	Case& get(unsigned char ligne, unsigned char col) const;
	Case *getPtr(unsigned char ligne, unsigned char col) const;

	void print() const;
private:
	unsigned char dimLignes;
	unsigned char dimColonnes;
	Case *tab;
};


#endif
