#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <fstream>
#include <iomanip>
using namespace std;

#define TRESHOLD 1

vector<double> split(const string& str, const string& delim)
{
    vector<double> tokens;
    size_t prev = 0, pos = 0;
    do
    {
        pos = str.find(delim, prev);
        if (pos == string::npos) pos = str.length();
        string token = str.substr(prev, pos-prev);
        if (!token.empty()) tokens.push_back(stod(token));
        prev = pos + delim.length();
    }
    while (pos < str.length() && prev < str.length());
    return tokens;
}

// gps distance in meters using earth radius

#define d2r (M_PI / 180.0)
double distance(double lat1, double long1, double lat2, double long2) {
    double dlong = (long2 - long1) * d2r;
    double dlat = (lat2 - lat1) * d2r;
    double a = pow(sin(dlat/2.0), 2) + cos(lat1*d2r) * cos(lat2*d2r) * pow(sin(dlong/2.0), 2);
    double c = 2 * atan2(sqrt(a), sqrt(1-a));
    double d = 3956 * c; 
    return d;
}

vector< vector<double> > dataset;

int main() {

  ifstream fs("merged.csv");
  string line;
  getline(fs, line);

  while(!fs.eof()) {
    getline(fs, line);
    vector<double> l = split(line, ",");
    if(l.size() == 0) break;
    if(l[1] == 0 && l[2] == 0) continue;
    dataset.push_back(l);
  }

  fs.close();
  ofstream os("mean_std_data");
  os << setprecision (17);

  double oldx = 0.3333;
  double oldy = 0.3333;

  for(size_t i = 0; i < dataset.size(); ++i) {
    
    if(i % 100 == 0) cout << i << "/" << dataset.size() << endl;
    
    if(dataset[i][1] == oldx && dataset[i][2] == oldy) continue;
    oldx = dataset[i][1];
    oldy = dataset[i][2];
    
    double var = 0;
    double mean = 0;
    vector< vector<double> > near;
    
    double noldx = 0.3333;
    double noldy = 0.3333;
    
    for(size_t j = 0; j < dataset.size(); ++j) {
      if(i != j) {
        if(dataset[j][1] == noldx && dataset[j][2] == noldy) continue;
        noldx = dataset[j][1];
        noldy = dataset[j][2];
        
        double d = distance(dataset[i][1], dataset[i][2], dataset[j][1], dataset[j][2]);
        if(d < TRESHOLD) {
          mean += dataset[j][5]*dataset[j][5];
          near.push_back(dataset[j]);
        }
      }
    }
    cerr << near.size() << endl;
    if(near.size() == 0) continue;
    
    mean /= near.size();
    for(size_t j = 0; j < near.size(); ++j) {
      var += (dataset[j][5]*dataset[j][5] - mean) * (dataset[j][5]*dataset[j][5] - mean);
    }
    var /= near.size();
   
   // lat, long, z-axis, mean of z-axis, standard deviation of z-axis
   os <<  dataset[i][1] << "," << dataset[i][2] << "," << dataset[i][5]*dataset[i][5] << "," << mean<<","<< var << endl;

  }
  os.close();
}
