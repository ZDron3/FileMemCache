#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include "reader.cpp"
#include "writer.cpp"

using namespace std;


string dataPath = "./data/";
int main(int argc, char** argv) {
	int N_reader, N_writer;
	string keyword;
	string dataPath = "./data/"; //hardcoded datapath
	ifstream FILE, FILE2;
	/*if (argc == 4)
	{*/
		multithread::OpenFile(FILE, dataPath, "Reader.txt" /*argv[2]*/, true); //OpenFile
		N_reader = multithread::ReadIntoQueue(FILE, multithread::file_queue);
		FILE.close();
		//=======================Writter========================
		multithread::OpenFile(FILE2, dataPath, "Writer.txt"/*argv[2]*/, true); //OpenFile
		N_writer = multithread::ReadIntoQueue(FILE2, multithread::file_queue2);
		FILE2.close();

		vector<reader*> readers;
		if (N_writer < 64) {
			for (int i = 0; i < N_reader; i++) {
				reader *ptr = new reader(dataPath, keyword, i, multithread::file_queue.at(i)); //passing the file string to read
				readers.push_back(ptr);
			}
		}
		else {
			cout << "Cannot create more than 64 threads for performance reason" << endl;
		}

		vector<writer*> writers;
		if (N_writer < 64) {
			for (int i = 0; i < N_writer; i++) {
				writer *ptr = new writer(i, dataPath);
				writers.push_back(ptr);
			}
		}
		else {
			cout << "Cannot create more than 64 threads for performance reason" << endl;
		}
		if (!readers.empty()) {
			for (int i = 0; i < N_reader; i++) {
				readers[i]->join();
			}
		}
		else
		{
			cout << "Not reader threads have been created" << endl;
		}
		if (!writers.empty()) {
			for (int i = 0; i < N_writer; i++) {
				writers[i]->join();
			}
		}
		else
		{
			cout << "Not writer threads have been created" << endl;
		}
		
}


