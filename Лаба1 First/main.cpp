#include "Header.h"

int main() {

	ifstream stream = ifstream("grammar.txt");
	Grammar G = Grammar();
	G.loadGrammar(stream);
	

	// тест FIRST
	cout << "test FIRST" << endl;
	vector<string> alpha;
	alpha.push_back("E");
	cout << G.FIRST(alpha);
	alpha.clear();

	alpha.push_back("E'");
	cout << G.FIRST(alpha);
	alpha.clear();

	alpha.push_back("T");
	cout << G.FIRST(alpha);
	alpha.clear();

	alpha.push_back("T'");
	cout << G.FIRST(alpha);
	alpha.clear();

	alpha.push_back("F");
	cout << G.FIRST(alpha);
	alpha.clear();

	alpha.push_back(")");
	cout << G.FIRST(alpha);
	alpha.clear();

	alpha.push_back("id");
	cout << G.FIRST(alpha) << endl;
	alpha.clear();

	// тест FOLLOW
	cout << "test FOLLOW" << endl;
	cout << G.FOLLOW(string("E"));
	cout << G.FOLLOW(string("E'"));
	cout << G.FOLLOW(string("T"));
	cout << G.FOLLOW(string("T'"));
	cout << G.FOLLOW(string("F"));

	return 0;
}