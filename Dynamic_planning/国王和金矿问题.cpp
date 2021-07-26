/*
描述：有一个国家发现了max_n座金矿，参与挖矿工人的总数是max_people人。
每座金矿的黄金储量不同为一维数组gold[]，
需要参与挖掘的工人数也不同为一维数组peopleNeed[]。
每座金矿要么全挖，要么不挖，不能派出一半人挖取一半金矿。
要想得到尽可能多的黄金，应该选择挖取哪几座金矿？
功能：
(1) 要求max_n、max_people、gold和peopleNeed均为可输入的；
(2) 编写DP函数，求解答案F；
(3) 编写main主函数，完成输入，调用DP函数和显示答案结果。
样例输入1：
5
92 22 87 46 90
100
77 22 29 50 99
样例输出1：
133
*/
#include<iostream>
#include<algorithm>
using namespace std;
int main()
{
	int max_n;
	cin>>max_n;
	int *gold=new int [max_n];
	for(int i=0;i<max_n;i++){
		cin>>gold[i];
	}
	int max_people;
	cin>>max_people;
	int **dp=new int*[max_n+1];
	for(int i=0;i<=max_n;i++){
		dp[i]=new int [max_people];
	}
	for(int i=0;i<=max_people;i++){
		dp[0][i]=0;
	}
	int *peopleNeed=new int[max_n];
	for(int i=0;i<max_n;i++){
		cin>>peopleNeed[i];
	}
	for(int i=1;i<=max_n;i++){
		for(int j=0;j<=max_people;j++){
			if(peopleNeed[i-1]<=j)
				//挖n堆等于max(挖第n堆加上第n-1堆的价值,不挖第n堆只挖前n-1堆)
				dp[i][j]=max(dp[i-1][j],dp[i-1][j-peopleNeed[i-1]]+gold[i-1]);
			else
				dp[i][j]=dp[i-1][j];
		}
	}
	cout<<dp[max_n][max_people]<<endl;
	return 0;
}
//状态转移方程 
//dp[i][j]代表i堆金子j个人能挖到的最大价值 
//peopelNeed[pi]代表第i堆金子需要的人 
//gold[gi]代表第i堆金子的价值 
//dp[i][j]=max(dp[i-1][j],dp[i-1][j-peopelNeed[pi]]) +gold[gi]
