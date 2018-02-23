#include "writer.h"

unordered_map<string, string> writer::GetPosition(ifstream &obj)
{
	unordered_map<string, string> map;
	string key, value;
	string tmp, temp;
	while (getline(obj, tmp))
	{
		int cntformap = 0;
		stringstream ss(tmp);
		while (getline(ss, temp, ' '))
		{
			if (cntformap == 0) {
				key = temp;
				cntformap++;
			}
			else {
				value = temp;//store key value pair
			}
		}
		map.insert(make_pair(key, value));
		//return key value pair
	}
	return map;
}

void writer::Start() {
	while (true) {
		multithread::fileQueueMTX.lock(); //make this exclusive lock shared writer 
										  //boost::unique_lock< boost::shared_mutex > lock(multithread::_access);
		if (multithread::file_queue2.size() != 0) { //check if the queue have filename remaining
			filename = multithread::file_queue2.front();
			//OK till here as we get the filename from the required queue now we want to read the file again
			ifstream FILE;
			//Store the postion in a int/vector for a particular Reader thread
			//Pass the int/vector to cache to check whether already available
			multithread::OpenFile(FILE, dataPath, filename, true);
			/*vector<int> newposition =*/
			unordered_map<string, string>map = GetPosition(FILE); //return key value pair
			FILE.close();
			//lru cache
			lru_cache<string, string> *lru = new lru_cache<string, string>(3);
			//lru check for key value to save a bad write
			//iterate through map
			unordered_map<string, string>::iterator itr;
			fstream file;
			file.open(dataPath + "itemfile.txt");
			if (file.is_open()) {
				for (itr = map.begin(); itr != map.end(); itr++)
				{
					string sLine;
					int line_no = 0;
					while (line_no != stoi(itr->first)/*newpos.key/*newposition.at(i)*/ && getline(file, sLine)) { //getline() check??
						++line_no;
					}
					if (line_no == stoi(itr->first)/*key*/) {
						//Handle dirty Write
						if (lru->Exists(itr->first))
						{
							lru->Put(itr->first, itr->second);
						}
						else
						{
							file.seekp(file.tellp());
							file << itr->second << endl;
						}
					}
					else {
						std::cout << "Cannot find the line for Write or Replace" << endl;
					}

				}
			}

			//check condition from cache with flag then read from item file it not 
			//and write to Reader*.out file
			multithread::consoleOutMTX.lock();
			cout << "reader #" << id + 1 << " reading " << filename << endl;
			multithread::consoleOutMTX.unlock();
			multithread::file_queue2.pop_front();
		}
		else {//if not, unlock the mutex and return the function
			  //boost::unique_lock< boost::shared_mutex > unlock(multithread::_access);
			multithread::fileQueueMTX.unlock();
			multithread::currentreaderWorking--;
			return;
		}
		multithread::fileQueueMTX.unlock();
		//	boost::unique_lock< boost::shared_mutex > unlock(multithread::_access);

	}
}
