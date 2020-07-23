/*
版权所有 睿集团 2020。保留所有权利。
仅供学习或RWST出现问题的时候重新编译。
请不要进行修改后私有化，否则我们会追究法律责任。
用户隐私协议见 "RWSTINSDIR\user\UPA.txt" 或在RWST里输入 "UPA"。
*/
#include<iostream>
#include<assert.h>
#include<fstream>
#include<windows.h>
#include<sys/stat.h>
using namespace std;
bool readTxt(string file){
    ifstream infile; 
    infile.open(file.data());
    assert(infile.is_open());
    string s;
    getline(infile,s);
    infile.close();
    if(s=="0"||s=="0\n"||s=="0\r")return true;
    else return false;
}
inline bool checkfiles (const std::string& name) {
  struct stat buffer;
  return (stat (name.c_str(), &buffer) == 0); 
}
bool startcheck(){
    if(checkfiles(".\\RWST.exe")!=1||
        checkfiles(".\\module\\used.txt")!=1||
        checkfiles(".\\bg")!=1||
		checkfiles(".\\welcome.exe")!=1)
			return false;
	else return true;
}
int main(){
    if(startcheck()==false){
		MessageBox(GetForegroundWindow(),"Oops!\nRWST lost some files or modules.\nPlease try to reinstall RWST to fix them.","ERROR",16);
		return 0;
	}
    if(readTxt(".\\module\\used.txt")==true){
        char* path=".\\module\\used.txt";
        ofstream fout(path);
	    if(fout){
		    fout<<"1";
		    fout.close();
	    }
        system("start .\\welcome.exe");
    }
    else system("start .\\RWST.exe");
    return 0;
}