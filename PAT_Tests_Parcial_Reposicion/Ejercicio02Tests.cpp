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
using ::testing::Values;
using ::std::tuple;
using ::std::string;
using ::std::vector;

namespace PRTests {
	class E02RotationTests : public TestWithParam<tuple<string, int, string>> {
	protected:
		Ejercicio02* e02;
		string list;
		int k;
		string expectedList;

		void SetUp() override {
			e02 = new Ejercicio02();
			std::tie(list, k, expectedList) = GetParam();
		}

		void TearDown() override {
			delete e02;
			e02 = nullptr;
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

	class E02NodesTests : public TestWithParam<tuple<string, int, string>> {
	protected:
		Ejercicio02* e02;
		string list;
		int k;
		string expectedList;

		void SetUp() override {
			e02 = new Ejercicio02();
			std::tie(list, k, expectedList) = GetParam();
		}

		void TearDown() override {
			delete e02;
			e02 = nullptr;
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

	TEST_P(E02RotationTests, E02Rotando) {
		Node<char>* l1 = buildList(list);

		Node<char>* head = e02->reverseKGroup(l1, k);
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

	INSTANTIATE_TEST_CASE_P(E02Rotando, E02RotationTests, ValuesIn(E02RotationTests::GetParams()));

	Node<char>* buildListAndMap(string& list, Node<char>* map[]) {
		Node<char>* head = nullptr;
		Node<char>** it = &head;

		for (char c : list) {
			*it = new Node<char>{ c };
			map[c - 'a'] = *it;
			it = &((*it)->next);
		}

		return head;
	}

	TEST_P(E02NodesTests, E02Nodos) {
		Node<char>* map[26];
		Node<char>* l1 = buildListAndMap(list, map);

		Node<char>* head = e02->reverseKGroup(l1, k);
		Node<char>* expectedHead = buildList(expectedList);

		string expected = buildFromList(expectedHead);
		string actual = buildFromList(head);

		int i = 0;
		while (head && expectedHead) {
			EXPECT_EQ(expectedHead->value, head->value) << "Error en la posicion [" << i << "] de la lista"
				<< ". Se esperaba [" << expectedHead->value << "], pero se encontro [" << head->value
				<< "]\nResultado esperado: [" << expected << "]\nResultado obtenido: [" << actual << "]";

			EXPECT_EQ(map[expectedHead->value - 'a'], map[head->value - 'a']) << "Error en la posicion [" << i << "] de la lista."
				<< " El valor dentro del nodo es correcto, pero el nodo no es el esperado. La rotacion no se hizo sobre los nodos.";

			++i;
			head = head->next;
			expectedHead = expectedHead->next;
		}

		EXPECT_TRUE(head == nullptr && expectedHead == nullptr) << "La cantidad de nodos no es la esperada."
			<< "]\nResultado esperado: [" << expected << "]\nResultado obtenido: [" << actual << "]";
	}

	INSTANTIATE_TEST_CASE_P(E02Nodos, E02NodesTests,
		Values(
			tuple<string, int, string>("abcde", 1, "abcde"),
			tuple<string, int, string>("abcde", 2, "badce"),
			tuple<string, int, string>("pqrs", 4, "srqp"),
			tuple<string, int, string>("abcdefghijklm", 7, "gfedcbahijklm"),
			tuple<string, int, string>("abcdefghijklm", 13, "mlkjihgfedcba")
		));
}