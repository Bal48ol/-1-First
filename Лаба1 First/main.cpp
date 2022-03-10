#include "Header.h"

int main() {
	ifstream stream = ifstream("grammar.txt");
	Grammar G = Grammar();
	G.loadGrammar(stream);
	return 0;
}