#include<iostream>
#include<algorithm>
using namespace std;
#include<vector> 
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int p_len=prices.size();
        if(p_len<=1) return 0;
        vector<vector<vector<int> > > dp(p_len,vector<vector<int> >(3,vector<int>(2)));
        dp[0][0][0]=0;
        dp[0][1][0]=0;
        dp[0][1][1]=-1*prices[0];
        dp[0][2][0]=0;
        dp[0][2][1]=-1*prices[0];
        for(int i=1;i<p_len;i++){
            dp[i][2][0] = max(dp[i - 1][2][0], dp[i - 1][2][1] + prices[i]);
            dp[i][2][1] = max(dp[i - 1][2][1], dp[i - 1][1][0] - prices[i]);
            dp[i][1][0] = max(dp[i - 1][1][0], dp[i - 1][1][1] + prices[i]);
            dp[i][1][1] = max(dp[i - 1][1][1], dp[i - 1][0][0] - prices[i]);
        }
        return dp[p_len-1][2][0];
    }
};

/*
dp[i][1][0]=max(dp[i-1][1][0],dp[i-1][1][1]+p[i])
dp[i][1][1]=max(dp[i-1][1][1],dp[i-1][0][0]-p[i])
dp[i][2][0]=max(dp[i-1][2][0],dp[i-1][2][1]+p[i])
dp[i][2][1]=max(dp[i-1][2][1],dp[i-1][1][0]-p[i])
*/
