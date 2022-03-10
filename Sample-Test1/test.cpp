#include "pch.h"
#include "C:\Users\Yakov\source\repos\Ырср1 First\Ырср1 First\ex1-2_template.cpp"

TEST(ReadGrammar, example) {
	std::string test_str = "E -> T E'\n";
	test_str += "E' -> + T E'\n";
	test_str += "E' -> - T E'\n";
	test_str += "E' -> e\n";
	test_str += "T->F T'\n";
	test_str += "T' -> * F T'\n";
	test_str += "T' -> / F T'\n";
	test_str += "T' -> e\n";
	test_str += "F -> ( E )\n";
	test_str += "F->id";
	std::stringstream ss(test_str);
	Grammar gr;
	bool exceptionTest = false;
	try {
		gr.loadGrammar(ss);
	}
	catch (const std::exception&) {
		exceptionTest = true;
	}
	EXPECT_TRUE(!exceptionTest);
}