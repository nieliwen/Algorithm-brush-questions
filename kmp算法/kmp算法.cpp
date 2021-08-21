#include<bits/stdc++.h>
using namespace std; 
/*
����ÿģʽ�� t ��ÿ��Ԫ�� t j��������һ��ʵ�� k ��
ʹ��ģʽ�� t ��ͷ�� k ���ַ���t 0 t 1��t k-1��
������ t j ǰ��� k��t j-k t j-k+1��t j-1�������һ���ַ� t j-k ���� t 1 ��ʼ������ k < j�����ַ���ͬ��
��������� k �ж������ȡ����һ����ģʽ�� t ��ÿ��λ�� j ���ַ�����������Ϣ������ next �����ʾ���� next[ j ]=MAX{ k }��
next���鱣���ŵ�ǰ�ַ����±곤�ȵ����ǰ��׺���  
next[i]������ģʽ���´�ƥ���λ�á�
����
abcabd
next[0]=-1��һ��Ĭ��Ϊ-1 �������һ����ʧ�����ı���ֱ����һ��Ԫ�� 
next[1]=0����ƥ�䵽�ڶ���Ԫ�ؾ�ʧ�ܣ���ô����Ҫ��ͷ��ʼƥ�䡣 
next[2]=0 a!=b,�������ƥ�䵽cʧ�ܣ��´λ���Ҫ��һ��ʼ��aƥ�� 
next[3]=0 a!=c ab!=bc ����ƥ�䵽�ڶ���aʧ�ܻ���Ҫ��һ��ʼ��aƥ�� 
next[4]=1 ��Ϊ��b���ڶ���b��ǰ���п�ͷ��a��dǰ���a��ȣ������´�ƥ���ʱ��ֱ�Ӵ�b��ʼƥ�䡣 
next[5]=2 ��Ϊ�� dǰ���п�ͷ��ab��dǰ���ab��ȣ������´�Ʒ��ֱ�Ӵ�c��ʼƥ�䡣   
*/ 
vector<int> Getnext(vector<int> next,string t)
{
   int j=0,k=-1;
   next[0]=-1;
   while(j<t.size()-1)
   {
      if(k == -1 || t[j] == t[k])
      {
         j++;k++;
         next[j] = k;
      }
      else k = next[k];//���� 
   }
   return next;
}

int KMP(string s,string t)
{
	int i=0,j=0;
	vector<int> next(t.size(),0);
	next=Getnext(next,t);
	
	for(int k=0;k<next.size();k++){
		cout<<next[k]<<" ";
	}
	cout<<endl;
	while(i<s.size()&&j<t.size())
	{
		cout<<"i="<<i<<endl;
		cout<<"j="<<j<<endl;
		if(j==-1 || s[i]==t[j])
		{
			 i++;
			 j++;
		}
		else j=next[j];               //j����
	}
	cout<<"i="<<i<<endl;
	cout<<"j="<<j<<endl;
	cout<<"t.size()="<<t.size()<<endl;
	cout<<"s.size()="<<s.size()<<endl;
	//ƥ��ɹ��������Ӵ���λ��
	if(j>=t.size()){
		return (i-t.size());
	}
	//û�ҵ�
	else{
		return (-1);
	}
}

int main()
{
	string s,t;
	cin>>s>>t;
	cout<<KMP(s,t)<<endl; 
}
