#include "pch.h"

#include <string>
#include <tuple>
#include <vector>
#include <fstream>
#include <iostream>

#include "../PAT_Parcial_Reposicion/Node.h"
#include "../PAT_Parcial_Reposicion/Ejercicio03.h"

using ::testing::TestWithParam;
using ::testing::ValuesIn;
using ::std::tuple;
using ::std::string;
using ::std::vector;

namespace PRTests {
	class E03Tests : public TestWithParam<tuple<int, vector<int>>> {
	protected:
		Ejercicio03* e03;
		vector<int> list;
		int pos;

		void SetUp() override {
			e03 = new Ejercicio03();
			std::tie(pos, list) = GetParam();
		}

		void TearDown() override {
			delete e03;
			e03 = nullptr;
		}

	public:
		static vector<tuple<int, vector<int>>> GetParams() {
			vector<tuple<int, vector<int>>> params;

			std::ifstream paramsFile("e03.csv");
			string line;

			while (std::getline(paramsFile, line)) {
				std::stringstream strStream(line);

				string spos;
				std::getline(strStream, spos, ',');
				int pos = std::stoi(spos);

				vector<int> list;
				string s;
				while (std::getline(strStream, s, ',')) {
					list.push_back(std::stoi(s));
				}

				params.push_back(tuple<int, vector<int>>(pos, list));
			}

			return params;
		}
	};

	TEST_P(E03Tests, E03Ciclo) {
		vector<Node<int>*> nodes;

		Node<int>* l1 = nullptr;
		Node<int>** it = &l1;

		for (int i : list) {
			*it = new Node<int>{ i };
			nodes.push_back(*it);
			it = &((*it)->next);
		}

		Node<int>* expectedNode = pos >= 0 ? nodes[pos] : nullptr;

		*it = expectedNode;

		ASSERT_DURATION_LE(1500,
			Node<int>*result = e03->detectCycle(l1);

		EXPECT_EQ(expectedNode, result) << "El nodo encontrado no coincide con el nodo del resultado.\n"
			<< "Se esperaba [" << (expectedNode ? std::to_string(expectedNode->value) : "nullptr") 
			<< "] de la posicion de la lista [" << pos
			<< "], pero se encontro [" << (result ? std::to_string(result->value) : "nullptr") << "].";)

		
	}

	INSTANTIATE_TEST_CASE_P(E03Ciclo, E03Tests, ValuesIn(E03Tests::GetParams()));
}