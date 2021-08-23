
// 我们可以把匹配看成类似处对象一样，左边一个集合是所有男孩，右边一个集合是所有女孩，我们需要求最多可以凑成几对情侣。

// 下图分别是男孩和女孩，连线代表男孩喜欢的女孩（这里的女孩都比较好，只要男孩喜欢她，她就会同意在一起）。
// ① 首先看 A 男孩，A 男孩喜欢 F、H，且 F 单身。耶，A 和 F在一起了！

// ② 再看看 B 男孩，B 男孩喜欢 F、G，可 F 已经有男朋友了，但 G 没有男朋友。耶，B 和 G 在一起了！

// ③ 再看看 C 男孩，C 男孩只喜欢 G 女孩，可 G 已经有男朋友了，C 男孩就去找到 G 的男朋友 B，问 B 能不能换个女朋友？？？
//（B 是一个渣男，只要他还能和其他的喜欢的女生在一起，他就愿意去和现对象分手），
//于是，B 看了看自己除了 喜欢G，还喜欢 F ，可 F 也已经有男朋友了，B 找到了 F的男朋友 A，问 A 能不能换个女朋友（A也是渣男），
//A 发现自己除了 F 还喜欢 H ，很开心的与 F 分手，并与 H 在一起， 
//于是，B 开心的和 F 在一起了，并与 G 分手（he tui渣男） ，因为 C 男孩的坚持，C 如愿以偿的和 G 在一起了！！！

// ④ D 男孩可能要好好学习，不想谈恋爱，没有对象，E 女孩因为没有人喜欢，也没有对象。

// 所以说 ，凑成 3 对情侣(A 和 H、B 和 F、 C 和 G)，最大匹配数为3.

#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
const int N = 510,M = 1e5+10;
int n1,n2,m;
int h[N], e[M], ne[M], idx; //邻接表
int match[N];
bool st[N];

void add(int a,int b)
{
   e[idx] = b, ne[idx] = h[a], h[a] = idx++; 	
} 
 
bool find(int x)
{
	for(int i = h[x]; i!=-1; i=ne[i]) // 遍历 x 男孩喜欢所有的女孩 
	{
	  	int j = e[i];
	  	if(!st[j]) // 如果st[j] = true 就不考虑这个女孩 
	  	{
	  	   st[j] = true; // 标记 j 这个女孩，作用是如果这个女孩有男朋友，我们去找她男朋友有没有可能和别的女孩在一起时，就不需要考虑他现对象 j 了 
		   if(match[j] == 0 || find(match[j]))// 女孩还没有对象或女孩的男朋友可以和其他喜欢的女生在一起 
		   {
		   	 match[j] = x; //匹配成功 
		   	 return true;
		   } 	
		}
	} 
	return false;
}

int main()
{
	cin >> n1 >> n2 >> m;
	memset(h,-1,sizeof(h));
	while(m--)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		add(a,b); //只存一条男生到女生的边就够用啦 
	}
	int res = 0; // 当前匹配的数量
	for(int i=1; i<=n1; i++) // 遍历每个男生
	{
		memset(st,false,sizeof(st)); //代表女孩还没有考虑过，每个女孩只考虑一次
		if(find(i)) res++;  // 男生匹配到了 
	} 
	cout << res;
}
