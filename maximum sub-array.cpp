#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>
#include <unordered_set>


// uncomment to disable assert()
// #define NDEBUG

// Use (void) to silence unused warnings.
#define assertm(exp, msg) assert(((void)msg, exp))
class Solution{
public:
    int maxSubArray(vector<int>& nums)
    {
       int sum  = nums[0];
       int res =nums[0];
       for (int i=1;i<nums.size();i++){
        sum = max(nums[i], sum+nums[i]);
       if(sum>res)
        res=sum;
       }
       return res;
    }
                    };
                    int main()
{
    Solution solution;

    std::vector<int> case1 = { 1, 2, 3, 1 };
    assertm(solution.containsDuplicate(case1) == true, (void("Case 1 failed")));
    std::cout << solution.containsDuplicate(case1) << std::endl;        // Should print 1

    std::vector<int> case2 = { 1, 2, 3, 4 };
    assertm(solution.containsDuplicate(case2) == false, (void("Case 2 failed")));
    std::cout << solution.containsDuplicate(case2) << std::endl;        // Should print 0

    std::vector<int> case3 = { 1, 1, 1, 3, 3, 4, 3, 2, 4, 2 };
    assertm(solution.containsDuplicate(case3) == true, (void("Case 3 failed")));
    std::cout << solution.containsDuplicate(case3) << std::endl;        // Should print 1

    std::cin.get();
}

