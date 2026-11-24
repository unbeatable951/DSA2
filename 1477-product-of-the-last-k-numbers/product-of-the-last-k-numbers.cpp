class ProductOfNumbers {
    vector<int> nums;

public:
    ProductOfNumbers() {}

    void add(int num) {
        nums.push_back(num);
    }

    int getProduct(int k) {
        int product = 1;

        for (int i = nums.size() - k; i < nums.size(); i++) {
            product *= nums[i];
        }

        return product;
    }
};