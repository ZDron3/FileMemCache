#include "IMultithreadReadWrite.h"


class writer : public IMultiThreadReadWrite {
		/*vector<int>*/ unordered_map<string, string> GetPosition(ifstream &obj);
	//void ProduceWriterOut(string &filename, string &datapath, string &value);
	public:
	virtual void Start();
	writer(int i, string d) {
		id = i;
		dataPath = d;
		_th = thread(&writer::Start, this);
	}
	~writer() {
		if (_th.joinable()) {
			_th.join();
		}
	}
	void join() {
		_th.join();
	}
private:
	int id;
	string dataPath;
	thread _th;
	string filename;
};
