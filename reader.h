#include "IMultithreadReadWrite.h"

class reader : public IMultiThreadReadWrite
{
	
	vector<int> GetPosition(ifstream &obj);
	void ProduceReaderOut(string &filename, string &value, bool check);
public:
	virtual void Start();
	reader(string d, string k, int i, string readername) {
		id = i;
		dataPath = d;
		keyword = k;
		_th = thread(&reader::reader::Start, this); //passing the thread filename here so we can read it again 
	}
	~reader() {
		if (_th.joinable()) {
			_th.join();
		}
	}
	void join() {
		_th.join();
	}

private:
	int id;
	thread _th;
	ifstream file;
	string dataPath;
	string filename;
	string keyword;
};