#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int countDaysTogether(string arriveAlice, string leaveAlice, string arriveBob, string leaveBob) {
        int aStart = dateToDayOfYear(arriveAlice);
        int aEnd = dateToDayOfYear(leaveAlice);
        int bStart = dateToDayOfYear(arriveBob);
        int bEnd = dateToDayOfYear(leaveBob);
        
        // Find the overlapping period
        int overlapStart = max(aStart, bStart);
        int overlapEnd = min(aEnd, bEnd);
        
        // If there is an overlap, return the number of days, otherwise return 0
        return max(0, overlapEnd - overlapStart + 1);
    }

private:
    int dateToDayOfYear(const string& date) {
        vector<int> daysInMonth = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        
        int month = stoi(date.substr(0, 2));
        int day = stoi(date.substr(3, 2));
        
        int dayOfYear = day;
        for (int i = 0; i < month - 1; ++i) {
            dayOfYear += daysInMonth[i];
        }
        
        return dayOfYear;
    }
};