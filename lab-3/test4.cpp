//#include <iostream>
//#include <vector>
//#include <iterator>
//#include <fstream>
//#include <string>
//
//#include "BinarySearchTree.h"
//
//using namespace std;
//
//class FrequencyTable
//{
//public:
//	FrequencyTable() {};
//
//	void printTable() {
//		//TODO- Skriv ut tabelen på rätt sätt? 
//		for (BinarySearchTree<FrequencyRow>::BiIterator it = tree.begin(); it != tree.end(); ++it)
//		{
//			cout << *it << endl;
//		}
//			
//	};
//	
//	void insert(string keyWord) {
//		//Check that the word dont exist
//		//if it dose increment the counter
//		//else add it to de tree.
//		if (tree.contains(keyWord) != nullptr) tree.contains(keyWord)->increment();
//		else tree.insert(FrequencyRow(keyWord));
//	};
//
//private:
//	class FrequencyRow
//	{
//	public:
//		FrequencyRow(string b, int c = 1) : key{ b }, counter{ c } { };
//		
//		//increment the counter
//		void increment() {
//			counter++;
//		}
//		bool operator<(const FrequencyRow& c) const
//		{
//			return (key.compare(c.key) < 0);
//		}
//		bool operator>(const FrequencyRow& c) const
//		{
//			return (key.compare(c.key) > 0);
//		}
//		
//		friend ostream& operator<<(ostream& os, FrequencyRow& raw) //Ska det vara en friend? 
//		{
//			//TODO formatet
//			return os << setw(15) << raw.key << setw(5)<< raw.counter;
//		}
//	private:
//		string key;
//		int counter;
//	};
//
//	BinarySearchTree<FrequencyRow> tree;
//};
//
//
//
////test program 4: FrequenceTable
//int main()
//{
//	FrequencyTable t;
//	ifstream file("c:/Users/thoma/Desktop/Uni/TND004 - Datastruktur/Data-Structure/lab-3/other files/words.txt");
//
//	if (!file)
//	{
//		cout << "couldn't open file words.txt" << endl;
//		return 1;
//	}
//
//	vector<string> v1 = { istream_iterator<string>{file}, istream_iterator<string>{} };
//	file.close();
//
//	for (auto j : v1)
//		t.insert(j);
//
//	/**************************************/
//	cout << "\nphase 1: table\n\n";
//	/**************************************/
//	t.printTable();
//
//	cout << "\nfinished testing" << endl;
//
//	
//	system("pause");
//	return 0;
//}
//
