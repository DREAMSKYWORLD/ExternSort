/************************
*实现ExternSort.h中的类ExternSort
*************************/

#include "ExternSort.h"
#include "MinHeap.cpp"

ExternSort::ExternSort(const char* inputFile, const char* outFile, int count):k(0),ls(NULL),b(NULL) {
			mCount = count;
			/*******************************************************
			*mInFile = inputFile;	                               *
			*mOutFile = outputFile;                                *
			*error: invalid conversion const char*  to char*       *
			********************************************************/
			mInFile = new char[strlen(inputFile) + 1];//strlen求字符串长度;
			strcpy(mInFile,inputFile);//strcpy将后者复制给前者;
			mOutFile = new char[strlen(outFile) + 1];
			strcpy(mOutFile, outFile);
		}

		void ExternSort::sort(){
			clock_t start = clock();
			//将文件内容分块在内存中排序，并写入临时文件;
			k = memorySort();

            //clock_t second = clock();

			ls = new int[k];
			b = new int[k + 1];

			kMerge();//k路归并;
			delete[] ls;
			delete[] b;

			clock_t end = clock();

			double exeTime = (end - start)/(double)CLOCKS_PER_SEC;
			//double memoryTime = (second - start)/(double)CLOCKS_PER_SEC;

			cout<< "Sorting total time（排序总时间）: "<< exeTime <<"S"<<endl;
			//cout<< "Memory time" <<memoryTime <<endl;
		}


		int ExternSort::memorySort(){
				FILE* fin = fopen(mInFile, "rt");
				int n = 0;
				int fileCount = 0; //文件计数器,跟踪临时文件;
				int* array = new int[mCount];

				//在此对每个临时文件排序;
				while((n = readData(fin, array, mCount)) > 0){

					//qsort(array, n, sizeof(int), cmpInt);  //快速排序;
                    clock_t startsort = clock();
					MinHeap<int> mh;
					mh.array_heapSort(array, n);
					//cout<<sizeof(mh)<<endl;
                    clock_t endsort = clock();

                    double memTime= (endsort - startsort)/(double)CLOCKS_PER_SEC;
                    double sumTime;
                    sumTime+=memTime;
                    cout<< "OneTemp time: "<< memTime <<"S"<<endl;
                    cout<< "SumTemp time（建堆总时间）: "<< sumTime <<"S"<<endl;
                    //to write tempFile;
					char* filename = tempFilename(fileCount++);
					FILE* tempFile = fopen(filename, "w");
					delete filename;
					writeData(tempFile, array, n);
					fclose(tempFile);
				}
				delete[] array;
				fclose(fin);

				return fileCount;//changed:fileCount -> fileCount+1;error:there are no k+1 file;
			}


			void ExternSort::Adjust(int leaf){

				//沿从叶子节点b[s]到根节点ls[0]的路径调整败者树;
				int parent = (leaf + k) / 2; //败者树的父节点;
				int winner = leaf;//记录一路的胜者节点;

				while(parent > 0){
					//如果失败，则失败者位置s留下，s指向新的胜利者;
					if(b[winner] > b[ls[parent]]){
						int tmp = winner;
						winner = ls[parent];
						ls[parent] = tmp;
					}
					parent = parent / 2;
				}

				ls[0] = winner; //ls[0] 存放调整后最大的位置;
			}

			void ExternSort::CreateLoserTree(){
				b[k] = MIN;	//额外存储一个最小值;

				//先初始化为指向最小值，这样后面的调整才是正确的，
				for(int i = 0; i < k; i++){
					ls[i] = k;
				}

				//依次从b[k-1],b[k-2],....b[0]出发调整败者树;
				for(int i = k - 1; i >= 0; i--){
					Adjust(i);
				}
			}

            //Merge tempFile
			void ExternSort::kMerge(){
				FILE* fout = fopen(mOutFile, "wt");
				//farray 中存储的的是文件指针;
				FILE** farray = new FILE*[k];
				int i;
				for(i = 0; i < k; ++i){
					char* filename = tempFilename(i);
					farray[i] =  fopen(filename, "rt");
					free(filename);
				}

				//初始读取;
				for(i = 0; i < k; ++i){
					if(fscanf(farray[i], "%d", &b[i]) == EOF){//读每个文件的第一个数到data数组;
						cout<<"there is no "<< k <<" file to merge!"<<endl;
						return;
					}
				}

				CreateLoserTree();
				int q;
				while(b[ls[0]] != MAX){
					//q 用来存储b中最小的位置，同时也对应一路文件；
					q = ls[0];
					//output(q);
					fprintf(fout, "%d ", b[q]);
					//input(b[q],q]);
					fscanf(farray[q], "%d", &b[q]);
					Adjust(q);
				}

				//output(ls[0]);
				fprintf(fout, "%d ", b[ls[0]]);

				//清理工作;
				for(i = 0; i < k; ++i){
					fclose(farray[i]);
				}

				delete[] farray;
				fclose(fout);

			}

