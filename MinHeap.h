#ifndef MINHEAP_SORT_H
#define MINHEAP_SORT 1
#include <iostream>
#include <cstdlib>

template<class Type>
class MinHeap
{
public:
    //默认构造函数
    MinHeap(  ):m_array( NULL ),m_size( 0 ),m_lenght( 0 ) {}
    //分配length长度的数组
    MinHeap( int length );
    //析构函数
    virtual ~MinHeap(  )
        { delete [  ] m_array;}
    //插入一个数据项
    bool insert( Type item );
    //判断是否为空
    bool empty(  );
    //获得最大的数据，但不删除
    Type fetchMax(  );
    //删除最大的数据也就是数组的第一个数据项
    void deleteMax(  );
    //显示堆的内容
    void display(  );
    //把一个类型T的数组转化成一个堆
    void array_heapSort(Type* array ,int size);//Type -> int*
    //对堆进行堆排序
    //precondition:堆已经存在
    void heapSort(  );



private:
    //下调，把[star,end]区间的二叉树进行堆化
    void locate_down(int start,int end );
    //上调，把[star,end]区间的二叉树进行堆化
    void locate_up(int start,int end ) ;

private:
    Type* m_array;      //指向一个数组的指针
    int m_size;       //已经存放了数据的个数
    int m_lenght;    //分配的空间的长度

};
#endif
