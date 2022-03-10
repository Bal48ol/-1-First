#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <utility>
#include <string>
#include "Header.h"

using namespace std;

// ����������� ������� ������
// �������� � .cpp �����
Grammar::Grammar() {
	// ����������� - ���������� � ������ �������� �������
	// ��������� ��� ������������� ��������� ���������� �������, � ����� ������ - ������
	return;
}

Grammar::~Grammar() {
	// ���������� - ���������� � ������ ����������� �������
	// ��������� ��� ����������� ������������ ��������, � ����� ������ - ������
	return;
}

void Grammar::loadGrammar(const std::istream &stream) {
	// ��������� ��� ������ 1.1
	// 1. ��������� ���������� � ���������� �� � grammar
	// 2. ���� ������� �� �������, �� ����������� ����������
	
	// ��� ������ ����� ������ ����� ����������� ����������� getline((std::basic_istream<char, std::char_traits<char>> &)stream, line);
	string line;
	while (getline((std::basic_istream<char, std::char_traits<char>> &)stream, line)) {
		auto p = line.find(" -> ");
		auto left = line.substr(0, p);
		auto right = line.substr(p + 4);
		vector<string> tmp;
		while (right.length())
		{
			int space = right.find(' ');
			if (space != string::npos) {
				tmp.push_back(right.substr(0, space));
				right = right.substr(space + 1);
			}
			else {
				tmp.push_back(right);
				right = "";
			}
		}
		grammar[left].push_back(tmp);
	}

	initFIRSTWithTerminalsAndEpsilon();
	initFIRSTWithNonTerminals();
	calculateFOLLOW();
}

ostream & operator << (ostream & stream, const Grammar &g) {
	// ��������� ��� ������ 1.1

	return stream;
}

void Grammar::initFIRSTWithTerminalsAndEpsilon() {
	// ��������� ��� ������ 1.2
	// ���� ������, �� ����������� ����������
	for (auto i : grammar)
	{
	
		notterminals.push_back(i.first);
		set<string> a;

		for (auto i : grammar[i.first])
		{
			for (auto j : i)
			{
				if (j == "e")
				{
					a.insert("e");
					goto label;
				}
			}
		}
	label:
		FIRSTForG[i.first] = a;
	}

	for (auto i : grammar)
	{
		for (auto j : i.second)
		{
			for (auto k : j)
			{
				//cout << k << " ";
				if (!FIRSTForG.count(k) && k != "e")
				{
					set<string> a;
					a.insert(k);
					FIRSTForG[k] = a;
				}
			}
			//cout << endl;
		}
	}
	//���������� �����������
	for (auto i : FIRSTForG)
	{
		bool test = true;
		for (auto j : notterminals)
		{
			if (j == i.first)
				test = false;
		}
		if (test)
		{
			terminals.push_back(i.first);
		}
	}
}

void Grammar::printFIRST(ostream &stream) {
	// ��������� ��� ������ 1.2
	for (auto i : FIRSTForG)
	{

		if (!i.second.empty())
		{
			cout << i.first << " = ";
			for (auto j : i.second)
			{
				cout << "[" << j << "] ";
			}
			cout << endl;
		}
		else{
			cout << "[" << "e" << "] ";
		}
	}
}

set<string> Grammar::FIRST(string& str)
{
	set<string> result;
	if (str == "e")
	{
		result.insert("e");
		return result;
	}

	for (auto i : FIRSTForG[str])
	{
		result.insert(i);
	}
	return result;
}

set<string> Grammar::FIRST(const vector<string>& str) {
	set<string> result;

	// ��������� ��� ������ 1.3
	if (str.size() == 1 && str[0] == "e")
	{
		result.insert("e");
		return result;
	}
	if (str.size() == 1)
	{
		for (auto i : FIRSTForG[str[0]])
		{
			result.insert(i);
		}
		return result;
	}
	
	for (auto i : str)
	{
		set<string> testF = FIRST(i);
		for (auto i : testF)
		{
			if (i != "e")
			{
				result.insert(i);
			}
		}
		if (!testF.count("e") && testF.size() > 0)
			return result;
	}
	result.insert("e");

	return result;
}

void Grammar::initFIRSTWithNonTerminals() {
	// ��������� ��� ������ 1.4
	// ���� ������, �� ����������� ����������
	while (true) {
		bool fl = false;

		for (auto i : grammar)
		{
			int oldlen = FIRSTForG[i.first].size();
			for (auto j : i.second)
			{
				for (auto k : FIRST(j[0]))
				{
					FIRSTForG[i.first].insert(k);
				}
			}
			if (oldlen < FIRSTForG[i.first].size())
			{
				fl = true;
			}
		}
		if (!fl) break;
	}
}

bool Grammar::isTerminal(string& N)
{
	bool test = false;
	for (auto i : terminals)
	{
		if (i == N)
		{
			test = true;
			break;
		}
	}
	return test;
}

bool Grammar::isnoTerminal(string& N)
{
	bool test = false;
	for (auto i : notterminals)
	{
		if (i == N)
		{
			test = true;
			break;
		}
	}
	return test;
}

void Grammar::initFOLLOW() {
	// ��������� ��� ������ 2.1
	// ���� ������, �� ����������� ����������
	auto a = "E";
	FOLLOWForG[a].insert("$");
}

void Grammar::calculateFOLLOW() {
	initFOLLOW();

	// ��������� ��� ������ 2.2
	// ���� ������, �� ����������� ����������
	initFOLLOW();
	map<string, int> oldlen;
	map<string, int> newlen;
	while (true) {
		for (auto N : grammar)
			oldlen[N.first] = FOLLOWForG[N.first].size();
		bool fl = false;
		for (auto N : grammar)
		{

			for (auto pravila : N.second)
			{
				for (auto element = pravila.begin(); element != pravila.end(); ++element)
				{
					//� �� �������� �� ���?
					bool test = isnoTerminal(*element);
					//������ ��� ��� ����������, ������� ��� ����� �����
					int i = 1;
					while (test && element + i != pravila.end())
					{
						bool flag = false;
						for (auto i : FIRST(*(element + 1)))
						{
							if (i != "e") {
								FOLLOWForG[*element].insert(i);
							}
							else
							{
								flag = true;
							}
						}
						if (flag)
						{
							i++;
						}
						else
						{
							break;
						}
					}
					if (test && element + i == pravila.end())
					{
						for (auto i : FOLLOWForG[N.first])
							FOLLOWForG[*element].insert(i);
					}
				}
			}

			for (auto N : grammar) newlen[N.first] = FOLLOWForG[N.first].size();

			for (auto i : oldlen)
			{
				if (oldlen[i.first] < newlen[i.first])
				{
					fl = true;
					break;
				}
			}

		}
		if (!fl) break;
	}
}

set<string> Grammar::FOLLOW(const string& N) {
	set<string> result;

	// ��������� ��� ������ 2.3
	for (auto i : FOLLOWForG[N])
	{
		result.insert(i);
	}

	return result;
}

ostream & operator << (ostream &stream, const set<string> &terminals) {
	set<string>::iterator p = terminals.begin();
	stream << "[";
	while (p != terminals.end()) {
		stream << p->c_str();
		p++;
		if (p != terminals.end()) stream << " ";
	}
	stream << "]" << endl;

	return stream;
}