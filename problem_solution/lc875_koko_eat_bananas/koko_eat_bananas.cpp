// Clarification:
//  - each time only eat one pile
//  - like eating slowly
//  - find minimum integer K so Koko can eat all banas within H hours
//  - Example: piles = [3, 6, 7, 11], H = 8
//             k = 11, (4 hour); 
//             k = 10, 9, 8, 7(5 hour);
//             k = 6 (6 hour);
//             k = 5 (7 hour)
// Algorithm:
//  - start k from the max value of piles and reduce it until the minimum k found that can still finish banans within H hours
//  - notice that If k satisfies the condition, no need to check k+1, k+2, ... (reduce the search space). Otherwise, we don't need to check k-1, k-2,... since they won't satisfy the condition. Based on this property, we can use binary search idea

// #include <algorithm> // std::max_element
// #include <vector> // std::vector

// time complexity: O(NlogW) + O(N)
class Solution {
public:
    int minEatingSpeed(vector<int>& piles, int H) {
        if (piles.empty() || (H < piles.size())) {
            return -1;
        }
        
        int lo = 1; // minmum is 1 not zero since eat at least 1 banana
        // int hi = *max_element(piles.begin(), piles.end()); //max element of the piles. Require * since max_element returns an iterator; time complexity O(N)
        int hi = getMaxPile(piles);
        // int hi = FIXED_VALUE
        int mid;
       
        // test case: [2, 3]
        // lo: 0, hi: 1, mid: 0,
        // if can eat all, hi -> 0, lo == hi end while loop
        // if not, lo -> 1, lo == hi end while oop
        // time complexity: O(logW)
        while (lo < hi) { //??
            mid = lo + (hi - lo)/2;
            
            if (canEatAll(piles, H, mid)) {
                hi = mid;
            }
            else {
                lo = mid + 1;
            }
        }
        
        // lo == hi after while loop
        return lo;
    }

private:
    // time complexity: O(N)
    bool canEatAll(vector<int>& piles, int H, int k) {
        int actualHour = 0;
        
        
        // for (vector<int>::iterator it = piles.begin(); it != piles.end(); ++it) {*it}
        // for(std::size_t i = 0; i < piles.size(); ++i) {piles[i]}
        for(int pile:piles) {
            actualHour += pile/k + (pile%k == 0 ? 0 : 1); // round to the larger integer value 
        }
        
        return actualHour <= H;
    }
    
    int getMaxPile(vector<int>& piles) {
        int maxPile = piles[0];
        for (int pile : piles) {
            maxPile = max(pile, maxPile);
        }
        return maxPile;
    }
    
    int max(int a, int b) {
        return (a < b) ? b : a;
    }
};