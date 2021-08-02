class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        int p_len=prices.size();
        if(p_len<=1) return 0;
        vector<vector<vector<int>>> dp(p_len,vector<vector<int>>(k+1,vector<int>(2)));
        for(int i=0;i<=k;i++){
            dp[0][i][0]=0;
            dp[0][i][1]=-prices[0];
        }
        for(int i=1;i<p_len;i++){
            for(int j=k;j>0;j--){
                dp[i][j][0]=max(dp[i-1][j][0],dp[i-1][j][1]+prices[i]);
                dp[i][j][1]=max(dp[i-1][j][1],dp[i-1][j-1][0]-prices[i]);
            }
        }
        return dp[p_len-1][k][0];

    }
};
/*
dp[i][k][0]=max(dp[i-1][k][0],dp[i-1][k][1]+price[i])
dp[i][k][1]=max(dp[i-1][k][1],dp[i-1][k-1][0]-price[i])
*/
