//
// Created by Harlan on 2016/12/6.
//

#include "stdafx.h"
#include <iostream>
using namespace std;

int MaxSum(int m,int n,int *a);

int main()
{
    int a[] = {0,2,3,-7,6,4,-5};//数组脚标从1开始
    for(int i=1; i<=6; i++)
    {
        cout<<a[i]<<" ";
    }

    cout<<endl;
    cout<<"数组a的最大连续子段和为:"<<MaxSum(3,6,a)<<endl;
}

int MaxSum(int m,int n,int *a)
{
    if(n<m || m<1)
        return 0;
    int *b = new int[n+1];
    int *c = new int[n+1];

    b[0] = 0;//b数组记录第i行的最大i子段和
    c[1] = 0;//c数组记录第i-1行的最大i-1子段和

    for(int i=1; i<=m; i++)
    {
        b[i] = b[i-1] + a[i];
        c[i-1] = b[i];
        int max = b[i];

        //n-m+i限制避免多余运算，当i=m时，j最大为n，可据此递推所有情形
        for(int j=i+1; j<=i+n-m;j++)
        {
            b[j] = b[j-1]>c[j-1]?b[j-1]+a[j]:c[j-1]+a[j];
            c[j-1] = max;//预先保存第j-1行的最大j-1子段和

            if(max<b[j])
            {
                max = b[j];
            }
        }
        c[i+n-m] = max;
    }

    int sum = 0;
    for(int j=m; j<=n; j++)
    {
        if(sum<b[j])
        {
            sum = b[j];
        }
    }
    return sum;
}