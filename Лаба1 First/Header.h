#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <utility>
#include <string>
#include "Header.h"

using namespace std;

// ОБЪЯВЛЕНИЯ КЛАССОВ И ОПЕРАТОРОВ
// перенести в заголовочный (.h) файл

// оператор для печати списка терминалов, возвращаемого FIRST и FOLLOW
ostream& operator << (ostream& stream, const set<string>& terminals);

class Grammar {
private:
	map<string, vector<vector<string>>> grammar; // словарь для хранения грамматики: ключ - нетерминал, значение - множество правых частей правил, каждая из которых - множество строк (терминалов/нетерминалов)
	map<string, set<string>> FIRSTForG; // словарь для хранения значений FIRST для всех терминалов и нетерминалов грамматики: ключ - терминал/нетерминал, значение - множество терминалов
	map<string, set<string>> FOLLOWForG; // словарь для хранения значений FOLLOW для всех нетерминалов грамматики: ключ - нетерминал, значение - множество терминалов
	void initFIRSTWithTerminalsAndEpsilon();
	void initFIRSTWithNonTerminals();
	void initFOLLOW();
	void calculateFOLLOW();

	vector <string> notterminals;
	vector <string> terminals;

public:
	Grammar();
	~Grammar();
	void loadGrammar(const std::istream& stream);
	void printFIRST(ostream& stream);
	set<string> FIRST(const vector<string>&);
	set<string> FIRST(string&);
	set<string> FOLLOW(const string&);

	bool isTerminal(string&);
	bool isnoTerminal(string&);

	friend ostream& operator << (ostream& stream, const Grammar& g);
};