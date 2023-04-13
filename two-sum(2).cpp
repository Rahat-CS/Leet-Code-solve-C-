
#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>
#include<unordered_map>
#include <unordered_set>
#define assertm(exp, msg) assert(((void)msg, exp))


class Solution {
public:
   std:: vector<int> twoSum(std::vector<int>& nums, int target){
   std::unordered_map<int,int> map;
    for(int index=0;index<nums.size();index++)
    {
        if(map.find(target-nums[index]) != map.end())
        {
            return {index, map[target-nums[index]]};
        }
        map[nums[index]] = index;
    }
    return{};
    }
};

int main()
{
    Solution solution;

    std::vector<int> nums { 2,7,11,15 };
    int target =9;
    std:: vector <int> result = solution.twoSum(nums, target);
    assertm(result.size() ==2, "Result size is not 2");
    assertm(result[0]==0, "Result [0]is not 0.");
    assertm(result[1]==1, "Result[1} is not 1.");

    std::cout<<"All test has been passed"<<std:: endl;
}
