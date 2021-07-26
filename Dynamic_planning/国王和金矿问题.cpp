/*
��������һ�����ҷ�����max_n����󣬲����ڿ��˵�������max_people�ˡ�
ÿ�����Ļƽ�����ͬΪһά����gold[]��
��Ҫ�����ھ�Ĺ�����Ҳ��ͬΪһά����peopleNeed[]��
ÿ�����Ҫôȫ�ڣ�Ҫô���ڣ������ɳ�һ������ȡһ����
Ҫ��õ������ܶ�Ļƽ�Ӧ��ѡ����ȡ�ļ������
���ܣ�
(1) Ҫ��max_n��max_people��gold��peopleNeed��Ϊ������ģ�
(2) ��дDP����������F��
(3) ��дmain��������������룬����DP��������ʾ�𰸽����
��������1��
5
92 22 87 46 90
100
77 22 29 50 99
�������1��
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
				//��n�ѵ���max(�ڵ�n�Ѽ��ϵ�n-1�ѵļ�ֵ,���ڵ�n��ֻ��ǰn-1��)
				dp[i][j]=max(dp[i-1][j],dp[i-1][j-peopleNeed[i-1]]+gold[i-1]);
			else
				dp[i][j]=dp[i-1][j];
		}
	}
	cout<<dp[max_n][max_people]<<endl;
	return 0;
}
//״̬ת�Ʒ��� 
//dp[i][j]����i�ѽ���j�������ڵ�������ֵ 
//peopelNeed[pi]�����i�ѽ�����Ҫ���� 
//gold[gi]�����i�ѽ��ӵļ�ֵ 
//dp[i][j]=max(dp[i-1][j],dp[i-1][j-peopelNeed[pi]]) +gold[gi]
