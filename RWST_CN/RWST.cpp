/*
版权所有 睿集团 2020。保留所有权利。
这是睿集团视窗操作系统命令行终端（RWST） [版本 2.1.2.00C32700202.1] 的源代码。
仅供学习或RWST出现问题的时候重新编译。
请不要进行修改后私有化，否则我们会追究法律责任。
用户隐私协议见 "RWSTINSDIR\user\UPA.txt" 或在RWST里输入 "UPA"。
*/
#include<windows.h>
#include<iostream>
#include<string>
#include<sstream>
#include<time.h>
#include<stdio.h>
#include<iomanip>
#include<cmath>
#include<TlHelp32.h>
#include<fstream>
#include<cassert>
#include<io.h>
#include<sys/stat.h>
//#include<unistd.h>
using namespace std;
SYSTEMTIME st;
string t00,c,c1,ctmp,task,rt,tmps0,tmps1,tmps2,tmps3,tmps4,tmps5,tmps01,tmps000;
char b[2049];
const char* path;
int s1,c2,cs,x,tmpi0;
bool y,nextyes=false;
VOID rwst(string);
void start(){
	b[0]='s';b[1]='t';b[2]='a';b[3]='r';b[4]='t';b[5]=' ';
}
void SpaceSize(CHAR  *RootPathName){
    DWORD SectorsPerCluster;
    DWORD BytesPerSector;
    DWORD NumberOfFreeClusters;
    DWORD TotalNumberOfClusters;	
	GetDiskFreeSpace(
		RootPathName,			
		&SectorsPerCluster,
		&BytesPerSector,
		&NumberOfFreeClusters,
		&TotalNumberOfClusters	
		);
	DWORD64 FreeSpaceSize  = (DWORD64)NumberOfFreeClusters * (DWORD64)BytesPerSector * (DWORD64)SectorsPerCluster;
	if(FreeSpaceSize == 0) return;
	DWORD GB = FreeSpaceSize / ((DWORD64)1024 * (DWORD64)1024 * (DWORD64)1024);
	FreeSpaceSize -= GB * ((DWORD64)1024 * (DWORD64)1024 * (DWORD64)1024);
	DWORD MB = FreeSpaceSize / ((DWORD64)1024 * (DWORD64)1024);
	FreeSpaceSize -= MB * ((DWORD64)1024 * (DWORD64)1024);
	DWORD KB = FreeSpaceSize / 1024;
	FreeSpaceSize -= KB * 1024;
	DWORD B = FreeSpaceSize;
	printf("%s 可用空间: %d GB  %d MB  %d KB  %d B\n", RootPathName, GB, MB, KB, B);
	DWORD64 TotalSpaceSize = (DWORD64)TotalNumberOfClusters * (DWORD64)BytesPerSector * (DWORD64)SectorsPerCluster;
	GB = TotalSpaceSize / ((DWORD64)1024 * (DWORD64)1024 * (DWORD64)1024);
	TotalSpaceSize -= GB * ((DWORD64)1024 * (DWORD64)1024 * (DWORD64)1024);
	MB = TotalSpaceSize / ((DWORD64)1024 * (DWORD64)1024);
	TotalSpaceSize -= MB * ((DWORD64)1024 * (DWORD64)1024);
	KB = TotalSpaceSize / 1024;
	TotalSpaceSize -= KB * 1024;
	B = TotalSpaceSize;
	printf("%s 总空间:   %d GB  %d MB  %d KB  %d B\n", RootPathName, GB, MB, KB, B);
}
void GetTime()
{
	SYSTEMTIME st;
	GetLocalTime( &st );
	printf("日期:  %d-%d-%d\n", st.wYear, st.wMonth, st.wDay);
	printf("时间:  %d:%d:%d\n", st.wHour, st.wMinute, st.wSecond);
	printf("已开机: %d分钟", GetTickCount()/1000/60);	
}
void PrintSpaceSize()
{
	CHAR DriverName[3] = "::";
	for(	
		DWORD dwDriver = GetLogicalDrives(), dw = 1;
		dwDriver != 0; 
		dwDriver /= 2, ++dw
		)
	{
		if(dwDriver % 2 == 1){
			switch(dw){
			case 2:
				DriverName[0] = 'B';
				SpaceSize(DriverName);
				break;
			case 3:
				DriverName[0] = 'C';
				SpaceSize(DriverName);
				break;
			case 4:
				DriverName[0] = 'D';
				SpaceSize(DriverName);
				break;
			case 5:
				DriverName[0] = 'E';
				SpaceSize(DriverName);
				break;
			case 6:
				DriverName[0] = 'F';
				SpaceSize(DriverName);
				break;
			case 7:
				DriverName[0] = 'G';
				SpaceSize(DriverName);
				break;
			case 8:
				DriverName[0] = 'H';
				SpaceSize(DriverName);
				break;
			case 9:
				DriverName[0] = 'I';
				SpaceSize(DriverName);
				break;
			case 10:
				DriverName[0] = 'J';
				SpaceSize(DriverName);
				break;
			}
		}
	}	
}
void SystemInfo(){
	SYSTEM_INFO SysInfo;
	GetSystemInfo(&SysInfo);
	printf("\n内存分页大小: 0x%.8X", SysInfo.dwPageSize);
	printf("\n可用内存起始: 0x%.8x", SysInfo.lpMinimumApplicationAddress);
	printf("\n可用内存结束: 0x%.8x", SysInfo.lpMaximumApplicationAddress);
	printf("\nCPU个数: %d", SysInfo.dwNumberOfProcessors);
	printf("\nCPU类型: ");
	switch (SysInfo.dwProcessorType){
	case PROCESSOR_INTEL_386:
		printf("386\n");
		break;
	case PROCESSOR_INTEL_486:
		printf("486\n");
		break;
	case PROCESSOR_INTEL_PENTIUM:
		printf("pentium, Cpu Model 0x%.2X, Stepping 0x%.2X\n",(BYTE)(SysInfo.wProcessorRevision>>8), (BYTE)SysInfo.wProcessorRevision);
		break;	
	case PROCESSOR_INTEL_IA64:
		printf("IA64\n");
		break;
	case PROCESSOR_AMD_X8664:
		printf("AMD x86 64\n");
		break;
	}
	printf("处理器架构: ");
	switch (SysInfo.wProcessorArchitecture){
	case PROCESSOR_ARCHITECTURE_INTEL:
		printf("intel");
		printf(" CPU vendor is %d\n",SysInfo.wProcessorLevel);
		break;
	case PROCESSOR_ARCHITECTURE_IA64:
		printf("64 bits intel\n");
		break;
	case PROCESSOR_ARCHITECTURE_AMD64:
		printf("64 bits AMD\n");
		break;
	case PROCESSOR_ARCHITECTURE_UNKNOWN:
		printf("UNKNOWN\n");
		break;
	}
}
void GetSystemDir()
{	
	CHAR UserName[MAX_PATH];
	DWORD dw = MAX_PATH;
	GetUserName(UserName, &dw);
	printf("用户名: %s\n", UserName);
	CHAR SystemDir[MAX_PATH];
	CHAR WindowDir[MAX_PATH];
	GetSystemDirectory(SystemDir, MAX_PATH);
	GetWindowsDirectory(WindowDir, MAX_PATH);
	printf("系统目录:%s\nWindows目录:%s", SystemDir, WindowDir);
}
void OS_Version(CHAR *szVersionInfo)
{
	OSVERSIONINFO OS;
	OS.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	if(!GetVersionEx(&OS)){
		printf("ERROR %d\n",GetLastError());
		return;
	}
	switch(OS.dwMajorVersion){
	case 5:
			switch(OS.dwMinorVersion){
			case 0:
				lstrcat(szVersionInfo,"2000");
				break;
			case 1:
				lstrcat(szVersionInfo,"XP");
				break;
			case 2:
				lstrcat(szVersionInfo,"Server 2003");
				break;
			}
		break;
	case 6:
			switch(OS.dwMinorVersion){
			case 0:
				lstrcat(szVersionInfo,"Vista");
				break;
			case 1:
				lstrcat(szVersionInfo,"7");
				break;
			}
		break;
	}
}
void AllSystemInfo(){
 	CHAR OS[24] = "Windows ";
	OS_Version(OS);
	printf("系统版本: %s\n",OS);	
	GetSystemDir();
	SystemInfo();
	PrintSpaceSize();
	GetTime();
    printf("\n");
}
void Print_Process(){
	HANDLE hProceessnap=CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
	if(hProceessnap==INVALID_HANDLE_VALUE)printf("灾难性故障！\n");
	else{
		PROCESSENTRY32 pe32;
		pe32.dwSize=sizeof(pe32);
		BOOL hProcess=Process32First(hProceessnap,&pe32);
		char buff[1024];
		while(hProcess){
			wsprintf(buff,"%s - 进程ID：%d",pe32.szExeFile,pe32.th32ParentProcessID);
			printf("%s\n",buff);
			memset(buff,0x00,1024);
			hProcess=Process32Next(hProceessnap,&pe32);
		}
	}
	CloseHandle(hProceessnap);
}
void baidu(){
	b[6]=char(34);b[7]=char(34);b[8]=' ';b[9]=char(34);b[10]='h';b[11]='t';b[12]='t';b[13]='p';b[14]='s';b[15]=':';b[16]='/';b[17]='/';
	b[18]='w';b[19]='w';b[20]='w';b[21]='.';b[22]='b';b[23]='a';b[24]='i';b[25]='d';b[26]='u';b[27]='.';b[28]='c';b[29]='o';b[30]='m';
	b[31]='/';b[32]='s';b[33]='?';b[34]='i';b[35]='e';b[36]='=';b[37]='U';b[38]='T';b[39]='F';b[40]='-';b[41]='8';b[42]='&';b[43]='w';
	b[44]='d';b[45]='=';
}
void bilibilis(){
	b[6]=char(34);b[7]=char(34);b[8]=' ';b[9]=char(34);b[10]='h';b[11]='t';b[12]='t';b[13]='p';b[14]='s';b[15]=':';b[16]='/';b[17]='/';
	b[18]='s';b[19]='e';b[20]='a';b[21]='r';b[22]='c';b[23]='h';b[24]='.';b[25]='b';b[26]='i';b[27]='l';b[28]='i';b[29]='b';b[30]='i';
	b[31]='l';b[32]='i';b[33]='.';b[34]='c';b[35]='o';b[36]='m';b[37]='/';b[38]='a';b[39]='l';b[40]='l';b[41]='?';b[42]='k';b[43]='e';
	b[44]='y';b[45]='w';b[46]='o';b[47]='r';b[48]='d';b[49]='=';
}
void bf(){
	for(int i=0;i<2048;i++)b[i]=char(0);
}
void UPA(string fileupa){
	ifstream infileupa; 
    infileupa.open(fileupa.data()); 
    assert(infileupa.is_open()); 
    string supa;
    while(getline(infileupa,supa))cout<<supa<<endl;
    infileupa.close();
}
bool isp(string tmps0){
	int lon0=tmps0.size();
	for(int i=0;i<tmps0.size();i++)
		if(tmps0[i]==' ')lon0--;
	if(lon0==0)return true;
	else return false;
}
string qdd(string tmpss0){
	string tmpss1="";
	for(int i=0;i<tmpss0.size();i++){
		if(tmpss0[i]!='.')tmpss1+=tmpss0[i];
		else break;
	}
	return tmpss1;
}
void runRWST(string tmpss1){
	string file3=".\\rwst\\"+tmpss1;
	ifstream infile3; 
    infile3.open(file3.data());
    assert(infile3.is_open());
    while(getline(infile3,tmps4)){
        rwst(tmps4);
    }
    infile3.close();
}
void readRWST(string file2){
    ifstream infile2; 
    infile2.open(file2.data()); 
    assert(infile2.is_open());
    while(getline(infile2,tmps3)){
        if(qdd(tmps3)==t00){
			c=qdd(tmps3);c+=".txt";
			infile2.close();
			runRWST(c);
			return;
		}
    }
    infile2.close();
	cout<<"错误：没有找到相应的代码或命令。"<<endl;
	cout<<"请检查你的输入然后重新尝试。"<<endl;
}
void readDir(string file1){
	bf();
	c=char(34);c+=".\\extensions\\";
    ifstream infile1; 
    infile1.open(file1.data()); 
    assert(infile1.is_open());
    while(getline(infile1,tmps2)){
        if(qdd(tmps2)==t00){
			c+=tmps2;c+=char(34);c+=" s";
			for(int i=0;i<c.size();i++)b[i]=c[i];
			system(b);
			infile1.close();
			return;
		}
    }
    infile1.close();
	readRWST(".\\module\\rwstdir.txt");
}
void readTxt(string file){
    ifstream infile; 
    infile.open(file.data()); 
    assert(infile.is_open());
	tmpi0=0;
    while(getline(infile,tmps1)){
		if(nextyes==true){
			nextyes=false;
			rwst(tmps1);
			infile.close();
			return;
		}
        else if((tmpi0==0||tmpi0%3==0)&&(t00==tmps1))nextyes=true;
		tmpi0++;
    }
    infile.close();
	readDir(".\\module\\dir.txt");
}
bool usedwechat(){
	string file5=".\\module\\usedwechat.txt";
	ifstream infile5; 
    infile5.open(file5.data()); 
    assert(infile5.is_open()); 
    getline(infile5,tmps5);
    if(tmps5=="0\n"||tmps5=="0\r"||tmps5=="0")return true;
	else return false;
    infile5.close();
}
string qsyh(string tmpy){
	if(tmpy[0]==char(34)&&tmpy[tmpy.size()-1]==char(34))
		tmpy=tmpy.substr(1,tmpy.size()-2);
	return tmpy;
}
string readWechat(string file01){
	ifstream infile01; 
    infile01.open(file01.data()); 
    assert(infile01.is_open()); 
    getline(infile01,tmps01);
	infile01.close();
	return tmps01;
}
inline bool checkfiles (const std::string& name) {
  struct stat buffer;
  return (stat (name.c_str(), &buffer) == 0); 
}
bool startcheck(){
	if(checkfiles(".\\module\\dir.txt")!=1||
		checkfiles(".\\module\\rwstdir.txt")!=1||
		checkfiles(".\\module\\setcode.txt")!=1||
		checkfiles(".\\module\\usedwechat.txt")!=1||
		checkfiles(".\\module\\wechat.txt")!=1||
		checkfiles(".\\user\\UPA.txt")!=1||
		checkfiles(".\\aria2\\aria2c.exe")!=1||
		checkfiles(".\\extensions")!=1||
		checkfiles(".\\rwst")!=1||
		checkfiles(".\\RwstCode.txt")!=1)
			return false;
	else return true;
}
void rwst(string t){
	int s=t.size();
	if(t.substr(0,6)!="reset "&&
		t.substr(0,8)!="restart "&&
		t.substr(0,5)!="kill "&&
		t.substr(0,5)!="port "&&
		t.substr(0,5)!="task "&&
		t.substr(0,5)!="tree "&&
		t.substr(0,7)!="python "&&
		t.substr(0,4)!="g++ "&&
		t.substr(0,5)!="redis"&&
		t.substr(0,7)!="telnet "&&
		t.substr(0,4)!="cmd "&&
		t.substr(0,11)!="powershell "&&
		t.substr(0,8)!="notepad "&&
		t.substr(0,5)!="wmic "&&
		t.substr(0,5)!="calc "&&
		t.substr(0,4)!="pip "&&
		t.substr(0,12)!="pyinstaller "&&
		t.substr(0,9)!="download "&&
		t.substr(0,10)!="kill::pid "&&
		t.substr(0,6)!="print "&&
		t.substr(0,6)!="title "&&
		t.substr(0,6)!="start "&&
		t.substr(0,6)!="baidu "&&
		t.substr(0,7)!="google "&&
		t.substr(0,9)!="bilibili "&&
		t.substr(0,16)!="bilibili::space "&&
		t.substr(0,16)!="bilibili::video "&&
		t.substr(0,11)!="translate::"){
			for(int i=0;i<s;i++)if(t[i]>='A'&&t[i]<='Z')t[i]+=('a'-'A');
	}
	if(s>2048){
		cout<<"错误：你的代码过长。"<<endl;
		cout<<"RWST不能执行你的代码因为它超过了能执行命令的最大长度。"<<endl;
	} 
	else if(t=="cmd")system("cmd");
	else if(t.substr(0,4)=="cmd "){
		bf();
		for(int i=3;i<s;i++)b[i-4]=t[i];
		system(b);
	}
	else if(t=="powershell")system("powershell"); 
	else if(t=="wmic")system("wmic"); 
	else if(t=="exit"){
		cs--;
		if(cs==0){
			system("cls");
			exit(0);
		}
	}
	else if(t=="nmap")system("nmap");
	else if(t=="help"){
		cout<<"关于RWST："<<endl;
		cout<<"睿集团视窗操作系统命令行终端 [版本 2.1.2.00C32700202.1] 64位。"<<endl;
		cout<<"睿集团官方邮箱：ray_group@126.com"<<endl;
		cout<<"作者邮箱：tsangjr@163.com"<<endl;
		cout<<"Git-Hub：https://github.com/Ray917"<<endl;
		cout<<"官网URL：https://github.com/Ray917/RWST"<<endl;
	}
	else if(t=="copyright")cout<<"版权所有 睿集团 2020。保留所有权利。"<<endl;
	else if(t=="cls")system("cls"); 
	else if(t.substr(0,5)=="kill "){
		bf();
		b[0]='T';b[1]='A';b[2]='S';b[3]='K';b[4]='K';b[5]='I';b[6]='L';b[7]='L';b[8]=' ';b[9]='/';b[10]='F';b[11]=' ';b[12]='/';b[13]='I';b[14]='M';b[15]=' ';
		for(int i=5;i<=s;i++)b[i+11]=t[i];
		system(b);
	}
	else if(t.substr(0,10)=="kill::pid "){
		bf();
		c="TASKKILL /pid ";c+=t.substr(10,t.size()-10);c+=" /t /f";
		for(int i=0;i<c.size();i++)b[i]=c[i];
		system(b);
	}
	else if(t.substr(0,5)=="port "){
		bf();
		c="netstat   -ano|findstr ";c+=t.substr(5,t.size()-5);
		for(int i=0;i<c.size();i++)b[i]=c[i];
		system(b);
	}
	else if(t.substr(0,5)=="task "){
		bf();
		c="tasklist|findstr ";c+=t.substr(5,t.size()-5);
		for(int i=0;i<c.size();i++)b[i]=c[i];
		system(b);
	}
	else if(t=="netstat")system("netstat");
	else if(t=="tasklist")system("tasklist");
	else if(t=="system::info"||t=="system"){
		AllSystemInfo();
		cout<<"由cleanDos提供技术支持。"<<endl;
	}
	else if(t=="upa")UPA(".\\user\\UPA.txt");
	else if(t=="regedit")system("regedit");
	else if(t=="system::process")Print_Process();
	else if(t=="system::s/n"||t=="system::sn")system("wmic bios get serialnumber");
	else if(t=="system::bios")system("wmic bios get releasedate");
	else if(t=="system::allinfo")system("systeminfo");
	else if(t=="system::ipconfig"||t=="ipconfig")system("ipconfig");
	else if(t=="g++")system("g++");
	else if(t=="time")system("time");
	else if(t=="clock"||t=="date"){
		GetLocalTime(&st);
		cout<<st.wYear<<"-"<<st.wMonth<<"-"<<st.wDay<<" "<<st.wHour<<":"<<st.wMinute<<":"<<st.wSecond<<"."<<st.wMilliseconds<<endl;
		if(st.wDayOfWeek==0)cout<<"周日";
		else if(st.wDayOfWeek==1)cout<<"周一"; 
		else if(st.wDayOfWeek==5)cout<<"周五"; 
		else if(st.wDayOfWeek==6)cout<<"周六"; 
		else if(st.wDayOfWeek==2)cout<<"周二"; 
		else if(st.wDayOfWeek==3)cout<<"周三"; 
		else if(st.wDayOfWeek==4)cout<<"周四"; 
		cout<<endl<<"RWST已经运行了"<<(double)clock()/CLOCKS_PER_SEC<<"秒。"<<endl;
	}
	else if(t=="pip")system("pip");
	else if(t=="telnet")system("telnet");
	else if(t=="python")system("python"); 
	else if(t=="where python")system("where python");
	else if(t.substr(0,7)=="python "||
		t.substr(0,4)=="pip "||
		t.substr(0,12)=="pyinstaller "||
		t.substr(0,11)=="powershell "||
		t.substr(0,5)=="wmic "||
		t.substr(0,5)=="ping "||
		t.substr(0,5)=="nmap "||
		t.substr(0,7)=="telnet "||
		t.substr(0,5)=="redis"||
		t.substr(0,4)=="g++ "||
		t.substr(0,6)=="color "||
		t.substr(0,6)=="title "||
		t.substr(0,8)=="timeout "||
		t.substr(0,5)=="tree "){
			bf();
			for(int i=0;i<s;i++)b[i]=t[i];
			system(b);
	} 
	else if(t=="pyinstaller")system("pyinstaller");
	else if(t=="rwst"){
		cout<<"睿集团视窗操作系统命令行终端 [版本 2.1.2.00C32700202.1] 64位。"<<endl;
		cout<<"版权所有 睿集团 2020。保留所有权利。"<<endl;
		cs++;
	}
	else if(t.substr(0,6)=="sleep "){
		stringstream sss;
		sss<<t.substr(6,s-6);
		sss>>s1;
		Sleep(s1);
	}
	else if(t=="notepad")system("notepad");
	else if(t.substr(0,8)=="notepad "){
		bf();
		c="notepad ";c+=char(34);
		c+=t.substr(8,s-8);c+=char(34);
		for(int i=0;i<c.size();i++)b[i]=c[i];
		system(b);
	}
	else if(t=="shutdown")system("shutdown -s -t 0");
	else if(t=="shutdown::asu")system("shutdown -r -o -t 0");
	else if(t=="shutdown::hybrid")system("shutdown -s -hybrid -t 0");
	else if(t=="shutdown::break")system("shutdown -h");
	else if(t=="shutdown::reset"||t=="shutdown::restart")system("shutdown -r -t 0");
	else if(t=="shutdown::slidetoshutdown"||t=="slidetoshutdown")system("slidetoshutdown"); 
	else if(t.substr(0,8)=="restart "){
		bf();
		c="TASKKILL /F /IM ";c1=" & start ";task=t.substr(8,s-8);
		for(int i=0;i<16;i++)b[i]=c[i];
		for(int i=0;i<s-8;i++)b[i+16]=task[i];
		for(int i=0;i<9;i++)b[i+16+(s-8)]=c1[i];
		for(int i=0;i<s-8;i++)b[i+16+(s-8)+9]=task[i];
		system(b);
	} 
	else if(t.substr(0,6)=="reset "){
		bf();
		c="TASKKILL /F /IM ";c1=" & start ";task=t.substr(6,s-6);
		for(int i=0;i<16;i++)b[i]=c[i];
		for(int i=0;i<s-6;i++)b[i+16]=task[i];
		for(int i=0;i<9;i++)b[i+16+(s-6)]=c1[i];
		for(int i=0;i<s-6;i++)b[i+16+(s-6)+9]=task[i];
		system(b);
	}
	else if(t.substr(0,6)=="print ")cout<<t.substr(6,t.size()-6)<<endl;
	else if(t=="wlan"||t=="wlan::info")system("netsh wlan show profiles"); 
	else if(t=="wlan::profiles"){
		bf();
		c=c1="";
		c1="netsh wlan show profile name=";
		c1+=char(34);
		cout<<"WLAN名称：";
		getline(cin,c);
		c1+=c;
		c1+=char(34);
		c1+=" key=clear";
		s1=c1.size();
		for(int i=0;i<s1;i++)b[i]=c1[i];
		system(b);
	} 
	else if(t=="translate")system("start https://translate.google.cn/"); 
	else if(t.substr(0,17)=="translate::zh-cn "||t.substr(0,17)=="translate::zh-CN "){
		bf();
		c="start     https://translate.google.cn/#view=home&op=translate&sl=auto&tl=zh-CN&text=";
		c[6]=c[7]=c[9]=char(34);
		t[s]=char(34);
		for(int i=17;i<s+1;i++)c+=t[i];
		s1=c.size();
		for(int i=0;i<s1;i++)b[i]=c[i];
		system(b);
	} 
	else if(t.substr(0,14)=="translate::en "){
		bf();
		c="start     https://translate.google.cn/#view=home&op=translate&sl=auto&tl=en&text=";
		c[6]=c[7]=c[9]=char(34);
		t[s]=char(34);
		for(int i=14;i<s+1;i++)c+=t[i];
		s1=c.size();
		for(int i=0;i<s1;i++)b[i]=c[i];
		system(b);
		}
	else if(t.substr(0,7)=="wechat "){
		if(usedwechat()==true){
			cout<<"请输入微信的程序路径：";
			getline(cin,c1);c1=qsyh(c1);
			path=".\\module\\wechat.txt";
			ofstream fout(path);
			if(fout){
				fout<<c1;
				fout.close();
			}
			else{
				MessageBox(GetForegroundWindow(),"RWST丢失了一些文件和模块。\n请尝试重新安装RWST来解决它们。","错误",16);
				cout<<"失败！"<<endl;
				return;
			}
			path=".\\module\\usedwechat.txt";
			ofstream fout1(path);
			if(fout1){
				fout1<<"1";
				fout1.close();
			}
			else{
				MessageBox(GetForegroundWindow(),"RWST丢失了一些文件和模块。\n请尝试重新安装RWST来解决它们。","错误",16);
				cout<<"失败！"<<endl;
				return;
			}
		}
		c1="";bf();
		for(int i=7;i<=s-1;i++){
			if(!isdigit(t[i])){
				cout<<"错误：这不是一个数字。"<<endl;
				cout<<"请检查你的输入然后重新尝试。"<<endl;
				y=1;
				break;
			}
			else c1+=t[i];
		}
		if(y==0){
			stringstream ss;
			ss<<c1;
			ss>>c2;
			c=readWechat(".\\module\\wechat.txt");
			if(c[c.size()-1]=='\r'||c[c.size()-1]=='\n')c=c.substr(0,c.size()-1);
			c1="start ";c1+=char(34);c1+=char(34);c1+=" ";c1+=char(34);c1+=c;c1+=char(34);
			for(int i=0;i<c1.size();i++)b[i]=c1[i];
			for(int i=0;i<c2;i++)system(b);
		}
		else y=0;
	}
	else if(t=="bilibili")system("start https://www.bilibili.com/");
	else if(t=="bilibili::login")system("start https://passport.bilibili.com/login");
	else if(t=="bilibili::search")system("start https://search.bilibili.com/");
	else if(t.substr(0,9)=="bilibili "){
		bf();
		start();
		bilibilis();
		t[s]=char(34);
		for(int i=9;i<s+1;i++)b[i+41]=t[i];
		system(b);
	}
	else if(t.substr(0,16)=="bilibili::space "){
		bf();
		c="start     https://space.bilibili.com/";
		c[6]=c[7]=c[9]=char(34);
		c+=t.substr(16,s-16);
		c+=char(34);
		for(int i=0;i<c.size();i++)b[i]=c[i];
		system(b);
	}
	else if(t.substr(0,16)=="bilibili::video "){
		bf();
		c="start     https://www.bilibili.com/video/";
		c[6]=c[7]=c[9]=char(34);
		c+=t.substr(16,s-16);
		c+=char(34);
		for(int i=0;i<c.size();i++)b[i]=c[i];
		system(b);
	}
	else if(t=="baidu")system("start https://www.baidu.com/");
	else if(t.substr(0,6)=="baidu "){
		bf();
		start();
		baidu();
		t[s]=char(34);
		for(int i=6;i<s+1;i++)b[i+40]=t[i];
		system(b);
	}
	else if(t=="google")system("start https://www.google.com/");
	else if(t.substr(0,7)=="google "){
		bf();
		c="start     https://www.google.com/search?q=";
		c[6]=c[7]=c[9]=char(34);
		c+=t.substr(7,s);
		c+=char(34);
		for(int i=0;i<c.size();i++)b[i]=c[i];
		system(b);
	}
	else if(t=="dxdiag")system("dxdiag");
	else if(t.substr(0,9)=="download "){
		bf();
		c=t.substr(9,t.size()-9);
		ctmp=".\\aria2\\aria2c.exe ";ctmp+=char(34);ctmp+=c;ctmp+=char(34);
		for(int i=0;i<ctmp.size();i++)b[i]=ctmp[i];
		x=system(b);
		if(x==0){
			cout<<"\n下载成功！"<<endl;
			system("start .");
		}
		else cout<<"下载失败！"<<endl;
	}
	else if(t=="setcode"){
		cout<<"1/2 | 你的代码：";getline(cin,c);
		cout<<"2/2 | RWST代码：";getline(cin,c1);
		path=".\\module\\setcode.txt";
		ofstream fout2(path,ios::app);
		if(fout2){
			fout2<<c<<endl<<c1<<endl<<endl;
			fout2.close();
			cout<<"全部完成！"<<endl;
		}
		else{
			MessageBox(GetForegroundWindow(),"RWST丢失了一些文件和模块。\n请尝试重新安装RWST来解决它们。","错误",16);
			cout<<"失败！"<<endl;
		}
	}
	else if(t=="start::folder"||t=="start::explorer"||t=="start::file"){
		bf();
		start();
		b[8]=' ';
		b[6]=b[7]=b[9]=b[10]=char(34);
		system(b);
	}
	else if(t=="start::browser"||t=="start::url"){
		bf();
		start();
		b[8]=' ';b[10]='h';b[11]=b[12]='t';b[13]='p';b[14]=':';b[15]=b[16]='/';
		b[6]=b[7]=b[9]=b[17]=char(34);
		system(b);
	}
	else if(t.substr(0,6)=="start "){
		bf();
		start();
		b[6]=b[7]=b[9]=char(34);b[8]=' ';
		t[s]=char(34);
		for(int i=6;i<=s;i++)b[i+4]=t[i];
		system(b);
	}
	else if(t=="diskpart")system("start diskpart");
	else if(t=="guid")system("start https://www.guidgen.com/");
	else if(t=="rwstinsdir")system("start .");
	else if(t=="rwsturl")system("start https://github.com/Ray917/RWST");
	else if(t=="download::latest rwst")system("start https://github.com/Ray917/RWST/releases/latest");
	else if(t=="calc")system("calc");
	else if(t.substr(0,5)=="calc "){
		bf();
		c="powershell ";
		c+=t.substr(5,s-5);
		for(int i=0;i<c.size();i++)b[i]=c[i];
		system(b);
	}
	else if(t==""||t=="\n"||t=="\r"||isp(t)==true);
	else readTxt(".\\module\\setcode.txt");
}
int main(int argc,char *argv[]){
	if(startcheck()==false){
		MessageBox(GetForegroundWindow(),"RWST丢失了一些文件和模块。\n请尝试重新安装RWST来解决它们。","错误",16);
		system("cls");
		return 0;
	}
	if(argc==2){
		string ssst=argv[1];
		rwst(ssst);
		cout<<endl;
		return 0;
	}
	system("@echo off");
	system("chcp 936");
	system("title RWST");
	system("cls");
	cout<<"睿集团视窗操作系统命令行终端 [版本 2.1.2.00C32700202.1] 64位。"<<endl;
	cout<<"版权所有 睿集团 2020。保留所有权利。"<<endl;
	cs++;
	while(1){
		cout<<endl<<">> ";
		getline(cin,t00);
		rwst(t00);
	}
	system("cls");
	return 0;
}