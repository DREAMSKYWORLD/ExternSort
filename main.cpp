//测试排序
#include <time.h>
#include <assert.h>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <stdio.h>
#include "ExternSort.h"

using namespace std;

char u[200] = {"unsortData%d.txt"}; //原始文件;
char s[200] = {"sortData%d.txt"}; //已排序文件;
char e[200] = {"extractData%d.txt"};//输出文件
char *unsortFile = u;
char *sortFile = s;

void extractData(int a[], int N,char* str1,char*str2);
void RandNum(int N,char* str);
int GetnT(int &numberToSort);

int main(int argc, char *argv[])
{
    int numberToSort; //在内存中一次排序的数量;
    GetnT(numberToSort);

    /***************************************
    *（1M26万数据，一次录入一万就好
    *10M就10万，100M用100万，500M也用100万）
    ***************************************/

    int x=0;
    cout<<"请输入要生成数据的大小（单位为M）"<<endl;
    cin>>x;
    sprintf(u,"unsortData%d.txt",x);
    sprintf(s,"sortData%d.txt",x);

    RandNum(x,u);

    ExternSort extSort(unsortFile, sortFile, numberToSort);
    extSort.sort();
    system("pause");

    cout<<x<<"M数据排序完成，请输入要输出的数据量（单位：个）"<<endl;
    int exdataSize;   //输出排序好的前K(500、1000、2000、10000)项
    cin>>exdataSize;
    sprintf(e,"extractData%d.txt",exdataSize);
    int* Amiya = new int[exdataSize];
    extractData(Amiya,exdataSize,s,e);
    return 0;
}

/*********************************************
*生成随机的不重复的测试数据
*********************************************/

void extractData(int a[], int M,char* str1,char* str2)//从生成的TXT里提取数据
{
    FILE* f = fopen(str1, "rt");
    int i = 0;
    while(i < M && (fscanf(f,"%d", &a[i]) != EOF))
        i++;
    cout<<"Extract: "<< i <<" interger" << endl;
    FILE* fp = fopen(str2, "wt");
    for(int i = 0; i < M; ++i)
    {
        fprintf(fp, "%d ", a[i]);
    }
    return;
}
int GetnT(int &numberToSort)
{

    cout<<"请输入在内存中一次排序的数量（单位为万）"<<"默认为一万"<<endl;
    char c;
    int nT=1;
    cin.get(c);

    if(c!='\n')
    {
        cin.unget();
        cin>>nT;
    }
    else if(c=='\n')
    {
        nT=1;
    }
    numberToSort = nT*10000; //在内存中一次排序的数量;
    cout<<numberToSort<<endl;
    return numberToSort;
}

const int size = 262144;//262144*4=1048576
void RandNum(int N,char* str)
{
    clock_t startTime,endTime;
    startTime = clock();
    vector <int> num;
    int n;
    ofstream outfile;
    outfile.open(str);
    for (n = 1; n <= N*size; n++)
        num.push_back(n);
    srand((unsigned)time(NULL));
    int i, j;
    for (n = 0; n < N*size; n++)//洗牌算法
    {
        i = (rand() * RAND_MAX + rand()) % (size*N);
        j = (rand() * RAND_MAX + rand()) % (size*N);
        swap(num[i], num[j]);
    }
    for (n = 0; n < N*size; n++)
        outfile << num[n]<<' ';
    outfile.close();
    cout<<"生成数据 "<<N*size<<" 个，字节总数 "<<N*size*sizeof(int)<<endl;
    cout<<"即数据大小为： "<<N<<"M （"<<N*1048576<<"）"<<endl;
    cout <<"生成数据完成"<< endl;

    endTime = clock();

    cout <<"生成数据所用时间: "<<(double)(endTime - startTime)/CLOCKS_PER_SEC<<"s"<< endl;
    system("pause");
    return;
}
