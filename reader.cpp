#include "reader.h"

void reader::ProduceReaderOut(string& filename, string &value, bool check)
{
	ofstream file;
	if (value != "") {
		file.open(filename + "out.txt", ios::app);
		if (check)
		{
			file << value + " Cache " << endl;
		}
		else {
			file << value + " Disk " << endl;
		}
		file.close();
	}
}

vector<int> reader::GetPosition(ifstream &obj)
{
	string tmp;
	vector<int> position;
	while (getline(obj, tmp)) {
		position.push_back(stoi(tmp)); //push file name into the queue
	}
	return position;
}

void reader::Start() {
	//multithread::currentreaderWorking++;
	while (true) {
		multithread::fileQueueMTX.lock(); //make this lock shared reader 
										  //boost::shared_lock< boost::shared_mutex > lock(multithread::_access);
		if (multithread::file_queue.size() != 0) { //check if the queue have filename remaining
			filename = multithread::file_queue.front();
			//OK till here as we get the filename from the required queue now we want to read the file again
			ifstream FILE;
			//Store the postion in a int/vector for a particular Reader thread
			//Pass the int/vector to cache to check whether already available
			multithread::OpenFile(FILE, dataPath, filename, true);
			vector<int> newposition = GetPosition(FILE);
			FILE.close();
			//lru cache
			//Open item file and read from it
			lru_cache<string, string> *lru = new lru_cache<string, string>(3/*CacheSize from commandLine*/);
			ofstream file(filename + "out.txt", ios::trunc);
			for (int i = 0; i < newposition.size(); i++)
			{
				if (lru->Exists(to_string(newposition.at(i))))
				{
					string value = lru->Get(to_string(newposition.at(i)));
					ProduceReaderOut(filename, value, true);
				}
				else
				{
					ifstream FILE;
					string sLine;
					multithread::OpenFile(FILE, dataPath, "itemfile.txt", true);
					int line_no = 0;
					while (line_no != newposition.at(i) && getline(FILE, sLine)) {
						++line_no;
					}
					if (line_no == newposition.at(i)) {
						// sLine contains the x line in the file.
						getline(FILE, sLine);
					}
					else {
						std::cout << "Does not contain the number of lines int itemfile" << endl;
					}

					lru->Put(to_string(newposition.at(i)), sLine);
					ProduceReaderOut(filename, sLine, false);
					FILE.close();
				}
			}
			//check condition from cache with flag then read from item file it not 
			//and write to Reader*.out file
			multithread::consoleOutMTX.lock();
			cout << "reader #" << id + 1 << " reading " << filename << endl;
			multithread::consoleOutMTX.unlock();
			multithread::file_queue.pop_front();
		}
		else {//if not, unlock the mutex and return the function
			multithread::fileQueueMTX.unlock();
			//boost::shared_lock< boost::shared_mutex > unlock(multithread::_access);
			cout << "No Files to Read from" << endl;
			multithread::currentreaderWorking--;
			return;
		}
		multithread::fileQueueMTX.unlock();
		//boost::shared_lock< boost::shared_mutex > unlock(multithread::_access);
		/* process counting occurence of keyword */
		multithread::OpenFile(file, dataPath, filename, false);
		file.close();
		multithread::consoleOutMTX.lock();
		//	cout << "reader #" << id + 1 << " pushing " << count << " into count_queue" << endl;
		multithread::consoleOutMTX.unlock();

	}
}