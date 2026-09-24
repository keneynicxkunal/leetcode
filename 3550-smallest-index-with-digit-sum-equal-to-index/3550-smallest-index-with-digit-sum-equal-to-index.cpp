class Solution {
public:
    int sumDigits(int n) {
        int sum = 0;

        while (n > 0) {
            sum += n % 10;  // last digit
            n /= 10;        // last digit hatao
        }

        return sum;
    }

    int smallestIndex(vector<int>& nums) {
        for (int i = 0; i < nums.size(); i++) {

            int sum = sumDigits(nums[i]);

            if (sum == i) {
                return i;
            }
        }

        return -1;
    }
};