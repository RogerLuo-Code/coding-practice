// Clarification: 
//  - sorted, integer 
//  - k closest mean? Absolution error value as distance 
//  - array length, and element range
// Go through examples
// Solution: 
//  - Input/Output: vector<int>, int k, int x; vector<int>
//  - Assumption: k, x, and array lenght are reasonable, k < arr.length 
//  - Algorithm: 
//  - Corner case: 
// Coding:
// Test:

class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        if (arr.empty() || k <= 0 || k > arr.size())
        {
            return vector<int>(k);
        }
        
        int left = 0;
        int right = arr.size() - k;
        
        while (left < right)
        {
            int mid = left + (right - left)/2;
            
            // if ((arr[mid + k] - x) > (x - arr[mid]))
            // {
            //     right = mid;
            // }
            if ((arr[mid + k] - x) < (x - arr[mid]))
            {
                left = mid + 1;
            }
            else
            {
                right = mid;
            }
        }
        
        return vector<int>(arr.begin() + left, arr.begin() + left + k);
        
    }
};