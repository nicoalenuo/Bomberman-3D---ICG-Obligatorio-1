#include "global.h"

// dada una lista de bombas ordenadas de menor a mayor tiempo de explosión y una bomba, inserta la bomba en la lista de manera que 
// la nueva lista siga ordenada
void global::insertarBomba(list<bomba*> listBomba, bomba* bomb) {
	float tiempo = bomb->getTiempoBomba();
	auto iter = listBomba.begin();
	while (iter != listBomba.end() && (*iter)->getTiempoBomba() <= bomb->getTiempoBomba()) {
		++iter;
	}
	listBomba.insert(iter, bomb);
}