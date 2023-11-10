#include "pch.h"

#include <string>
#include <tuple>
#include <vector>
#include <fstream>
#include <iostream>

#include "../PAT_Parcial_Reposicion/Node.h"
#include "../PAT_Parcial_Reposicion/Ejercicio02.h"

using ::testing::TestWithParam;
using ::testing::ValuesIn;
using ::std::tuple;
using ::std::string;
using ::std::vector;

namespace PRTests {
	class E02Tests : public TestWithParam<tuple<string, int, string>> {
	protected:
		Ejercicio02* e03;
		string list;
		int k;
		string expectedList;

		void SetUp() override {
			e03 = new Ejercicio02();
			std::tie(list, k, expectedList) = GetParam();
		}

		void TearDown() override {
			delete e03;
			e03 = nullptr;
		}

	public:
		static vector<tuple<string, int, string>> GetParams() {
			vector<tuple<string, int, string>> params;

			std::ifstream paramsFile("e02.csv");
			string line;

			while (std::getline(paramsFile, line)) {
				std::stringstream strStream(line);

				string list;
				std::getline(strStream, list, ',');

				string sk;
				std::getline(strStream, sk, ',');
				int k = std::stoi(sk);

				string e;
				std::getline(strStream, e, ',');

				params.push_back(tuple<string, int, string>(list, k, e));
			}

			return params;
		}
	};

	Node<char>* buildList(string& n) {
		Node<char>* head = nullptr;
		Node<char>** it = &head;

		for (char c : n) {
			*it = new Node<char>{ c };
			it = &((*it)->next);
		}

		return head;
	}

	string buildFromList(Node<char>* head) {
		string r = "";
		r.reserve(100);

		while (head) {
			r += (head->value);
			head = head->next;
		}

		return r;
	}

	TEST_P(E02Tests, E02Rotando) {
		Node<char>* l1 = buildList(list);

		Node<char>* head = e03->reverseKGroup(l1, k);
		Node<char>* expectedHead = buildList(expectedList);

		string expected = buildFromList(expectedHead);
		string actual = buildFromList(head);

		int i = 0;
		while (head && expectedHead) {
			EXPECT_EQ(expectedHead->value, head->value) << "Error en la posicion [" << i << "] de la lista"
				<< ". Se esperaba [" << expectedHead->value << "], pero se encontro [" << head->value
				<< "]\nResultado esperado: [" << expected << "]\nResultado obtenido: [" << actual << "]";

			++i;
			head = head->next;
			expectedHead = expectedHead->next;
		}

		EXPECT_TRUE(head == nullptr && expectedHead == nullptr) << "La cantidad de nodos no es la esperada."
			<< "]\nResultado esperado: [" << expected << "]\nResultado obtenido: [" << actual << "]";
	}

	INSTANTIATE_TEST_CASE_P(E02Rotando, E02Tests, ValuesIn(E02Tests::GetParams()));
}