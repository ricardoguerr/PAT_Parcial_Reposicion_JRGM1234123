#include "pch.h"

#include <string>
#include <tuple>
#include <vector>
#include <fstream>
#include <iostream>

#include "../PAT_Parcial_Reposicion/Node.h"
#include "../PAT_Parcial_Reposicion/Ejercicio01.h"

using ::testing::TestWithParam;
using ::testing::ValuesIn;
using ::std::tuple;
using ::std::string;
using ::std::vector;

namespace PRTests {
	class E01Tests : public TestWithParam<tuple<string, string, string>> {
	protected:
		Ejercicio01* e01;
		string n1;
		string n2;
		string expectedResult;

		void SetUp() override {
			e01 = new Ejercicio01();
			std::tie(n1, n2, expectedResult) = GetParam();
		}

		void TearDown() override {
			delete e01;
			e01 = nullptr;
		}

	public:
		static vector<tuple<string, string, string>> GetParams() {
			vector<tuple<string, string, string>> params;

			std::ifstream paramsFile("e01.csv");
			string line;

			while (std::getline(paramsFile, line)) {
				std::stringstream strStream(line);

				string n1;
				std::getline(strStream, n1, ',');

				string n2;
				std::getline(strStream, n2, ',');

				string e;
				std::getline(strStream, e, ',');

				params.push_back(tuple<string, string, string>(n1, n2, e));
			}

			return params;
		}
	};

	Node<int>* buildList(string& n) {
		Node<int>* head = nullptr;
		Node<int>** it = &head;

		for (char c : n) {
			*it = new Node<int>{ c - '0' };
			it = &((*it)->next);
		}

		return head;
	}

	string buildFromList(Node<int>* head) {
		string r = "";
		r.reserve(100);

		while (head) {
			r += (head->value + '0');
			head = head->next;
		}

		return r;
	}

	TEST_P(E01Tests, E01Sumando) {
		Node<int>* l1 = buildList(n1);
		Node<int>* l2 = buildList(n2);

		Node<int>* head = nullptr;

		ASSERT_DURATION_LE(100,
			head = e01->addTwoNumbers(l1, n1.length(), l2, n2.length()););

		Node<int>* expectedHead = buildList(expectedResult);

		string expectedNumber = buildFromList(expectedHead);
		string actualNumber = buildFromList(head);

		int i = 0;
		while (head && expectedHead) {
			EXPECT_EQ(expectedHead->value, head->value) << "Error en la posicion [" << i << "] de la lista"
				<< ". Se esperaba [" << expectedHead->value << "], pero se encontro [" << head->value
				<< "]\nResultado esperado: [" << expectedNumber << "]\nResultado obtenido: [" << actualNumber << "]";

			++i;
			head = head->next;
			expectedHead = expectedHead->next;
		}

		EXPECT_TRUE(head == nullptr && expectedHead == nullptr) << "La cantidad de nodos no es la esperada."
			<< "]\nResultado esperado: [" << expectedNumber << "]\nResultado obtenido: [" << actualNumber << "]";
	}

	INSTANTIATE_TEST_CASE_P(E01Sumando, E01Tests, ValuesIn(E01Tests::GetParams()));
}