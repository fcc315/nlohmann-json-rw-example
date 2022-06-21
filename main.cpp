#include "nlohmann/json.hpp"
#include <iostream>
#include <fstream>
using namespace std;


void PrettyJson(std::string filename)
{
	using nlohmann::json;
	std::ifstream iFile(filename);
	json j;
	try { iFile >> j; }
	catch (...) {
		std::cerr << "Load configuration file from json failed: " << filename << std::endl;
		iFile.close();
		return;
	}

	std::ofstream o(filename);
	o << std::setw(4) << j << std::endl;

	iFile.close();
}
void writeExample(string jsonFile)
{
    using nlohmann::json;
	std::fstream File;
	File.open(jsonFile, fstream::out);

    double val = 0.0;
	json j;
	j["param"]["val1"] = val;
	j["param"]["val2"] = val;
	j["param"]["val3"] = val;
	j["param"]["val4"] = val;


	j["result"]["rmse_mm"] = val ;
	j["result"]["rmse_pixel"] = val;

	json j_arr = json::array();
	j_arr.push_back(j);

    int cnt = 5;
	for (int i = 0; i < cnt; ++i) {
		//LOG(INFO) << frameFilenames_[i] << endl;
		json jj;
		jj["image"] = to_string(i)+".jpg";
		jj["resolution"] = { 100, 100 };
		jj["id"] = i;
		
		j_arr.push_back(jj);
	}

	File << j_arr;
	File.close();
	PrettyJson(jsonFile);
}

void readExample(string jsonFile)
{
    using nlohmann::json;
	ifstream iFile(jsonFile);
	json j;
	try { iFile >> j; }
	catch (...) {
		cerr << "Parse result json file failed: " << jsonFile << std::endl;
		iFile.close();
	}
	iFile.close();

    for (auto item : j) {
		if (item.contains("param")) {
			json jItem = item["param"];
			double val = jItem["val1"];
            cout << "param::val1 is: " << val << endl;
			val = jItem["val2"];
            cout << "param::val1 is: " << val << endl;
			val = jItem["val3"];
            cout << "param::val1 is: " << val << endl;
			val = jItem["val4"];
            cout << "param::val1 is: " << val << endl;
		}
		if (item.contains("result")) {
			json jItem = item["result"];
			double val = jItem["rmse_mm"];
            cout << "param::rmse_mm is: " << val << endl;
			val  = jItem["rmse_pixel"];
            cout << "param::rmse_pixel is: " << val << endl;
		}

		if (item.contains("image")) {
			std::string imgNameStr = item["image"];
			int id = item["id"];
			cout << "Image id:" << id << ": " << imgNameStr << endl;
        }
    }
}


int main()
{
    string jsonFile = "example.json";
    writeExample(jsonFile);
    readExample(jsonFile);

    return 0;
}