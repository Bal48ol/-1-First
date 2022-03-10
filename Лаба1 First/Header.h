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

// ���������� ������� � ����������
// ��������� � ������������ (.h) ����

// �������� ��� ������ ������ ����������, ������������� FIRST � FOLLOW
ostream& operator << (ostream& stream, const set<string>& terminals);

class Grammar {
private:
	map<string, vector<vector<string>>> grammar; // ������� ��� �������� ����������: ���� - ����������, �������� - ��������� ������ ������ ������, ������ �� ������� - ��������� ����� (����������/������������)
	map<string, set<string>> FIRSTForG; // ������� ��� �������� �������� FIRST ��� ���� ���������� � ������������ ����������: ���� - ��������/����������, �������� - ��������� ����������
	map<string, set<string>> FOLLOWForG; // ������� ��� �������� �������� FOLLOW ��� ���� ������������ ����������: ���� - ����������, �������� - ��������� ����������
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