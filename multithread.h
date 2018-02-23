#pragma
#include <string>
#include <fstream>
#include <iostream>
#include <thread>
#include <mutex>
#include <deque>
#include <string>
using namespace std;
namespace multithread
{
	deque<string> file_queue; //contains filename that will be read
	deque<string> file_queue2; //contains filename that will be written
	int currentreaderWorking = 0; //shows how many readers are processing right now. This will prevent writers from early stop.
								  //boost::shared_mutex _access;
	mutex fileQueueMTX;
	mutex consoleOutMTX;
	int ReadIntoQueue(ifstream &obj, deque<string> &queue) /*purpose of deque unknown*/ {
		string tmp;
		while (getline(obj, tmp)) {
			queue.push_back(tmp); //push file name into the queue
		}
		return queue.size();
	}

	void OpenFile(ifstream &obj, string path, string filename, bool showMessage) {
		obj.open(path + filename);
		if (showMessage) {
			cout << "Opening " << filename << "...";
			if (obj.is_open()) {
				cout << "[Sucessful]" << endl;
			}
			else {
				cout << "[Fail]" << endl;
			}
		}
	}
};