#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <iterator>

int main()
{
    int m{}, n{}, tmp{};
    std::map<std::string, int> map{};
    std::cin >> m >> n;
    std::vector<int> result{};
    while (m--)
    {
        std::string tmp_s;
        int tmp_i;
        std::cin >> tmp_s >> tmp_i;
        map[tmp_s] = tmp_i;
    }
    std::vector<std::string> v(std::istream_iterator<std::string>(std::cin),
                               std::istream_iterator<std::string>());
    for (std::string s : v)
    {
        if (s == ".")
        {
            result.push_back(tmp);
            tmp = 0;
        }
        else if(map.find(s) != map.end())
        {
            tmp += map[s];
        }
    }
    for(int i : result) std::cout << i << std::endl;
    return 0;
}