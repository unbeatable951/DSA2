class Solution {
public:
    int sortableIntegers(std::vector<int>& nums) {
        int n = nums.size();
        std::vector<int> sorted_nums = nums;
        std::sort(sorted_nums.begin(), sorted_nums.end());

        int total_sum = 0;

        // Iterate over all divisors of n
        for (int k = 1; k <= n; ++k) {
            if (n % k != 0) continue;

            bool possible = true;
            for (int i = 0; i < n; i += k) {
                // Extract the block from nums and the corresponding sorted block
                std::vector<int> block(nums.begin() + i, nums.begin() + i + k);
                std::vector<int> sorted_block(sorted_nums.begin() + i, sorted_nums.begin() + i + k);

                // Check if 'block' is a cyclic rotation of 'sorted_block'
                // Concatenate sorted_block with itself to check cyclic rotations
                std::vector<int> double_sorted(sorted_block.begin(), sorted_block.end());
                double_sorted.insert(double_sorted.end(), sorted_block.begin(), sorted_block.end());

                bool found = false;
                for (int j = 0; j <= k; ++j) {
                    bool match = true;
                    for (int m = 0; m < k; ++m) {
                        if (double_sorted[j + m] != block[m]) {
                            match = false;
                            break;
                        }
                    }
                    if (match) {
                        found = true;
                        break;
                    }
                }

                if (!found) {
                    possible = false;
                    break;
                }
            }

            if (possible) {
                total_sum += k;
            }
        }

        return total_sum;
    }
};