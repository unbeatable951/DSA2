// The API isBadVersion is defined for you.
// bool isBadVersion(int version);

// The API isBadVersion is defined for you.
// bool isBadVersion(int version);

class Solution {
public:
    int firstBadVersion(int n) {
        int left = 1;
        int right = n;
        
        while (left < right) {
            // Prevent potential integer overflow compared to (left + right) / 2
            int mid = left + (right - left) / 2;
            
            if (isBadVersion(mid)) {
                // mid could be the first bad version, search the left half (including mid)
                right = mid;
            } else {
                // mid is good, so the first bad version must be after mid
                left = mid + 1;
            }
        }
        
        return left;
    }
};