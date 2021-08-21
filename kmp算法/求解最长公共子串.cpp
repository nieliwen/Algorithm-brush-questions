#include<bits/stdc++.h>
using namespace std; 
/*
����ÿģʽ�� t ��ÿ��Ԫ�� t j��������һ��ʵ�� k ��
ʹ��ģʽ�� t ��ͷ�� k ���ַ���t 0 t 1��t k-1��
������ t j ǰ��� k��t j-k t j-k+1��t j-1�������һ���ַ� t j-k ���� t 1 ��ʼ������ k < j�����ַ���ͬ��
��������� k �ж������ȡ����һ����ģʽ�� t ��ÿ��λ�� j ���ַ�����������Ϣ������ next �����ʾ���� next[ j ]=MAX{ k }��
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
	int tl=t.size();

	while( i<s.size() && j<tl)
	{
		
		if(j==-1 || s[i]==t[j])
		{
			 i++;
			 j++;
		}
		else 
        {
            j=next[j];               //j����
        }
	}
	//ƥ��ɹ��������Ӵ���λ��
	if( j>=tl ){
        //cout<<(j>=6)<<endl;

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
	while(cin>>s>>t){
        if(t.size()>s.size()){
            string temp=t;
            t=s;
            s=temp;
        }
        //cout<<"s="<<s<<" t="<<" "<<t<<endl;
        int mx=0;
        int start=0;
        int sub_len=0;
        for(int i=0;i<t.size();i++){
            for(int l=1;l<=t.size()-i;l++){
                //cout<<t.substr(i,l)<<endl;
                 if(KMP(s,t.substr(i,l))!=-1){
                     //cout<<t.substr(i,l)<<endl;
                     if(l>mx){
                         mx=l;
                         start=i;
                         sub_len=l;
                     }
                 }
            }
        }
        cout<<t.substr(start,sub_len)<<endl;
    }	 
}
