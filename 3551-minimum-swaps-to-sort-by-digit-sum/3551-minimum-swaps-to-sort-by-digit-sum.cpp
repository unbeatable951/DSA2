class Solution {
public:
    int digitSum(int n) {
        int sum = 0;

        while (n > 0) {
            sum += n % 10;
            n /= 10;
        }

        return sum;
    }

    int minSwaps(vector<int>& nums) {
        int n = nums.size();

        // Store each number with its original index.
        vector<pair<int, int>> arr;

        for (int i = 0; i < n; i++) {
            arr.push_back({nums[i], i});
        }

        // Sort by digit sum, then by number.
        sort(arr.begin(), arr.end(),
             [this](const pair<int, int>& a,
                    const pair<int, int>& b) {

                 int sumA = digitSum(a.first);
                 int sumB = digitSum(b.first);

                 if (sumA != sumB) {
                     return sumA < sumB;
                 }

                 return a.first < b.first;
             });

        vector<bool> visited(n, false);
        int swaps = 0;

        // Count cycles in the index mapping.
        for (int i = 0; i < n; i++) {
            if (visited[i] || arr[i].second == i) {
                continue;
            }

            int cycleSize = 0;
            int j = i;

            while (!visited[j]) {
                visited[j] = true;
                j = arr[j].second;
                cycleSize++;
            }

            if (cycleSize > 1) {
                swaps += cycleSize - 1;
            }
        }

        return swaps;
    }
};