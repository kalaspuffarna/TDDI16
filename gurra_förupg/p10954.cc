#include <iostream>
#include <set>

using namespace std;

int calc(multiset<int> & nums)
{
    int res{};
    while(nums.size() != 1){
    int val1{*nums.begin()};
    nums.erase(nums.begin());
    int val2{*nums.begin()};
    nums.erase(nums.begin());
    nums.insert(val1 + val2);
    res += val1 + val2;
    }
    return res;
}

int main()
{
    int n;
    while(cin >> n && n != 0)
    {
        multiset<int> nums{};
        for(int i{}; i < n; i++)
        {
            int j{};
            cin >> j;
            nums.insert(j);   
        }
        cout << calc(nums) << endl;
    }
}

 
