#include <iostream>
#include <sstream>
#include <string>
#include <map>
using namespace std;
int main(){
    map<int, pair<string, string>> dsSinhVien;
    string dong;
    while(getline(cin, dong)){
        if(dong.empty()) continue;
        if(dong.substr(0,6)=="Insert"){
            int vt1 = dong.find("("), vt2 = dong.find(")");
            string noiDung = dong.substr(vt1+1, vt2-vt1-1);
            stringstream ss(noiDung);
            string token;
            int maSV;
            string tenSV, lopHoc;
            getline(ss, token, ',');
            maSV = stoi(token);
            getline(ss, tenSV, ',');
            getline(ss, lopHoc, ',');
            dsSinhVien[maSV] = make_pair(tenSV, lopHoc);
        }
        else if(dong.substr(0,6)=="Delete"){
            int vt1 = dong.find("("), vt2 = dong.find(")");
            string noiDung = dong.substr(vt1+1, vt2-vt1-1);
            int maSV = stoi(noiDung);
            dsSinhVien.erase(maSV);
        }
        else if(dong.substr(0,5)=="Infor"){
            int vt1 = dong.find("("), vt2 = dong.find(")");
            string noiDung = dong.substr(vt1+1, vt2-vt1-1);
            int maSV = stoi(noiDung);
            if(dsSinhVien.find(maSV) != dsSinhVien.end())
                cout << dsSinhVien[maSV].first << "," << dsSinhVien[maSV].second << endl;
            else
                cout << "NA,NA" << endl;
        }
    }
    return 0;
