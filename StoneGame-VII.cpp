/* Problem - Stone Game VII
 * Link - https://leetcode.com/problems/stone-game-vii
 *
 *
 * Intuiton :
 * Both Alice & Bob have two choices at every step,
 * either to choose the first or the last stone from
 * array. Let just traverse all the possible paths
 * and keep saving the results, so that we can use
 * them later in the future.
 *
 *
 *
 * Algorithm :
 *
 * Let represent Alice score by A and Bob's by B we
 * want to minimize the value of A-B. Initially this
 * value is 0, when alice scored some points (say x)
 * this will be added to the difference that we want
 * to find, so now the difference is x, when Bob
 * scored some points (say y) these points will be
 * deducted from the difference and hence the
 * difference will now be x-y.
 *
 * Now Alice have two choices let his score by choosing
 * the first stone be 'f' and by choosing the last be
 * 'e' Alice will choose the maximum of(f,e) as playing
 * optimally.
 *
 * On the other hand Bob wants to minimize the difference
 * and thus will choose the minimum of the two scores
 * that he will be getting by choosing the first/last
 * stone of the array.
 *
 * Therefore we will have three states - starting point of
 * the current array, ending point of the array and a flag
 * representing whether it's Alice turn or Bob's.
 *
 * Saving the result in a memoization table will make the code
 * efficient enough.
 *
 *
 * Complexity Analysis :
 * Time Complexity -  O(N*N) where N is the number of stones
 * Space Complexity - O(N*N) where N is the number of stones
 */

 // C++ Code

 class Solution {
 public:

    int sum[1001],dp[1001][1001][2];

    int solve(vector<int>&stones, int n, int start, int end, int flag) {

		// we have finished the array so the score is 0
        if(start >= end)
            return 0;

		// we have already calculate the answer so just return it
        if(dp[start][end][flag] != -1)
            return dp[start][end][flag];

		// total is the sum of current array of stones
		// first is the score by choosing the first stone
		// second is the score by choosing the last stone
        int total = 0, first = 0, second = 0;

        if(flag) {

            if(start == 0)
                total = sum[end];
            else
                total = sum[end] - sum[start-1];

            first  = solve(stones, n, start+1, end, flag^1) + (total - stones[start]);
            second = solve(stones, n, start, end-1, flag^1) + (total - stones[end]);

            // Alice will maximize the difference
            return dp[start][end][flag] = max(first, second);
        }

        else {

            if(start == 0)
                total = sum[end];
            else
                total = sum[end] - sum[start-1];

            first  = solve(stones, n, start+1, end, flag^1) - (total - stones[start]);
            second = solve(stones, n, start, end-1, flag^1) - (total - stones[end]);

			// Bob will minimize the difference
            return dp[start][end][flag] = min(first, second);
        }
    }

    int stoneGameVII(vector<int>& stones) {

        int i, n = stones.size();
        memset(dp, -1, sizeof(dp));

        sum[0] = stones[0];
        for(i = 1; i < n; i++)
            sum[i] = sum[i-1] + stones[i];

        return solve(stones, n, 0, n-1, 1);
    }
};