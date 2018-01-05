#ifndef EXTERNSORT_H
#define EXTERNSORT_H

#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <cassert>



using namespace std;

#define MIN -1
#define MAX 1000000000
typedef int* LoserTree;
typedef int* External;


class ExternSort
{
	public:
	    /***************************************************************/
		//inputFile:输入文件名;
	    //outFile:输出文件名;
		//count:每次在内存中排序的整数个数;
		ExternSort(const char* inputFile, const char* outFile, int count);
        /**************************************************************/



        /*************************************************************/
		virtual ~ExternSort(){
			delete[] mInFile;
			delete[] mOutFile;
		}
        /**************************************************************/



        /**************************************************************/
        //排序函数，调用sort()函数对文件数据进行排序;
		void sort();
        /**************************************************************/



		protected:
        /**************************************************************/
			/*****************************************
			*读取文件数据,f为输入流;
			*将读取的数据存入数组a[]中，
			*n 为一次读取的个数；
			******************************************/
			int readData(FILE* f, int a[], int n){
				int i = 0;
				while(i < n && (fscanf(f,"%d", &a[i]) != EOF))
					i++;
				cout<<"read: "<< i <<" interger" << endl;
				return i;
			}

             /*****************************************
             *数组中的数据写到文件中，用MAX标志文件的结束;
             *f为输出文件流
             *a[] 为数据来源的指针
             *n 为一次写入文件的数据个数;
             ******************************************/
			void writeData(FILE* f, int a[], int n){
				for(int i = 0; i < n; ++i){
					fprintf(f, "%d ", a[i]);
				}
				fprintf(f, "%d", MAX);//在最后写上一个最大值；
			}
        /*************************************************************/



        /*************************************************************/
			//产生临时文件，返回文件名数组的指针;
			char* tempFilename(int index){
				char* tempFile = new char[100];
				sprintf(tempFile, "temp\\temp%d.txt", index);
				return tempFile;
			}
        /**************************************************************/



        /**************************************************************/
            //采用快速排序是用到的比较指针;
			/*static int cmpInt(const void* a, const void* b){
				return *(int*)a - *(int*)b;
			}
            */
        /***************************************************************/



        /**************************************************************/
			//临时文件在内存排序;double exeTime = (end - start)/(double)CLOCKS_PER_SEC;
			int memorySort();

			void Adjust(int leaf);

			//构造败者树;
			void CreateLoserTree();
        /***************************************************************/


			/******************************************
			*利用败者树把k个输入归并段并到输出端中    *
			*b中前k个变量存放k个输入段中当前记录的元素*
			*归并临时文件							  *
			******************************************/
			void kMerge();

	private:
		int mCount; //array length;
	    char* mInFile; //input file path;
		char* mOutFile; //output file path;
		int k; // 归并数，只能在内排序之后才能确定，所以下面的ls and b 都只能定义为指针；
		LoserTree ls;//define pointer, after dramtical creat array;
		External b; //define pointer, within the member of function, used array;

	   double *memTime;

};


#endif // EXTERNSORT_H
