// Clarification: 
//  - only one duplicate number
//  - the duplicate number can appear two or more times 
//  - array is not sorted
// Solution:
//  - Input/Output: vector<int>; int
//  - Algorithm:
//      - brutal force: two for-loops 
//      - sort and use binary search to find the first duplicate target (O(nlogn) + O(logn))

class Solution {
public:
    int findDuplicate1(vector<int>& nums) {
        // Method: use binary search for space [1, n]
        //           count the number of elements <= mid, if number > mid, indicates duplicates [1, mid]. Otherwise, duplicates in [mid+1, n]
        // Time complexity: O(nlogn); Space complexity: O(1)
        int left = 1;
        int right = nums.size() - 1;
        int mid;
        int count = 0;
        
        while (left < right) {
            mid = left + (right - left)/2;
            count = 0;
            for(int num:nums) {
                count += num <= mid;
            }
            
            count > mid ? right = mid : left = mid + 1;
        }
        
        return left;
    }

    int findDuplicate2(vector<int>& nums) {
        // Method : sort array first and then find duplicates based on the difference between value and index
        // Time complexity: O(nlogn) + O(logn) = O(nlogn); Space complexity: O(1)
        // sort array
        sort(nums.begin(), nums.end()); 
        
        int left = 0;
        int right = nums.size() - 1;
        int mid;
        int diff;
        int target = 0 - nums[0]; // target is the difference bewteen first value and its index
        
        // Use binary search to find the last target in a ascending order 
        // [e, s]
        while (left < right - 1) {
            mid = left + (right - left)/2;
            diff = mid - nums[mid];
            
            if (target == diff) {
                left = mid;
            }
            else if (target > diff) {
                left = mid + 1; 
            }
            else {
                right = mid - 1; // not mid - 1, since it may accidently exclude the final solution
            }
        }
        
        // two elements left after while loop left == right - 1
        return nums[right];  
    }

    int findDuplicate3(vector<int>& nums) {
        // Method: store each element in a set and check whether encounter duplicates when interating over the array
        // Time complexity: O(n); Space complexity: O(n)
        set<int> seen;
        
        for (int num:nums) {
            if (seen.count(num)) {
                return num;
            }
            else
            {
                seen.insert(num);
            }
        }
        
        return -1;
    }

};