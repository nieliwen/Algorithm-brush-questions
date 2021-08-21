#include<bits/stdc++.h>
using namespace std; 
/*
对于每模式串 t 的每个元素 t j，都存在一个实数 k ，
使得模式串 t 开头的 k 个字符（t 0 t 1…t k-1）
依次与 t j 前面的 k（t j-k t j-k+1…t j-1，这里第一个字符 t j-k 最多从 t 1 开始，所以 k < j）个字符相同。
如果这样的 k 有多个，则取最大的一个。模式串 t 中每个位置 j 的字符都有这种信息，采用 next 数组表示，即 next[ j ]=MAX{ k }。
next数组保存着当前字符串下标长度的最大前后缀相等  
next[i]保存着模式串下次匹配的位置。
例如
abcabd
next[0]=-1第一个默认为-1 ，如果第一个就失败则文本串直接下一个元素 
next[1]=0假设匹配到第二个元素就失败，那么还是要从头开始匹配。 
next[2]=0 a!=b,所以如果匹配到c失败，下次还是要从一开始的a匹配 
next[3]=0 a!=c ab!=bc 所以匹配到第二个a失败还是要从一开始的a匹配 
next[4]=1 因为在b（第二个b）前面有开头的a和d前面的a相等，所以下次匹配的时候直接从b开始匹配。 
next[5]=2 因为在 d前面有开头的ab和d前面的ab相等，所以下次品牌直接从c开始匹配。   
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
      else k = next[k];//回退 
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
		else j=next[j];               //j回退
	}
	cout<<"i="<<i<<endl;
	cout<<"j="<<j<<endl;
	cout<<"t.size()="<<t.size()<<endl;
	cout<<"s.size()="<<s.size()<<endl;
	//匹配成功，返回子串的位置
	if(j>=t.size()){
		return (i-t.size());
	}
	//没找到
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
