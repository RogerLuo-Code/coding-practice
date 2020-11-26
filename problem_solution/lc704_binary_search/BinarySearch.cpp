#include <iostream>
#include <vector>
using namespace std;

class BinarySearch {
public:
    int search(vector<int>& nums, int target) {
        if (nums.empty()) return -1;
        
        int left = 0;
        int right = nums.size() - 1;
        int mid;
        
        while (left <= right)
        {
            mid = left + (right -left)/2;
            
            if (nums[mid] == target) return mid;
            else if (target < nums[mid]) right = mid - 1;    
            else left = mid + 1;
        }
        return -1;
    }
};

int main()
{
    BinarySearch bs; 
    vector<int> nums = {10, 15, 21, 32, -3, 5};
    int target = 21;
    int index;
    index = bs.search(nums, target);
    cout << "Index of target: " << index << endl;
    return 0;
}