class Solution {
public:
    int countDaysTogether(string arriveAlice, string leaveAlice, string arriveBob, string leaveBob) {
        // Days in each month for a non-leap year
        vector<int> daysInMonths = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        
        // Precompute cumulative days before each month
        vector<int> cumulativeDays(13, 0);
        for (int i = 0; i < 12; ++i) {
            cumulativeDays[i + 1] = cumulativeDays[i] + daysInMonths[i];
        }
        
        // Lambda function to convert "MM-DD" to day of the year (1 to 365)
        auto convertToDayOfYear = [&](const string& dateStr) {
            int month = stoi(dateStr.substr(0, 2));
            int day = stoi(dateStr.substr(3, 2));
            return cumulativeDays[month - 1] + day;
        };
        
        // Convert all four dates to day-of-year numbers
        int a1 = convertToDayOfYear(arriveAlice);
        int l1 = convertToDayOfYear(leaveAlice);
        int a2 = convertToDayOfYear(arriveBob);
        int l2 = convertToDayOfYear(leaveBob);
        
        // Find the overlap interval
        int overlapStart = max(a1, a2);
        int overlapEnd = min(l1, l2);
        
        // Calculate the number of overlapping days
        return max(0, overlapEnd - overlapStart + 1);
    }
};