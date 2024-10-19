#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <sstream>
#include <chrono>
using std::string;
using std::unordered_set;
using std::unordered_map;

int main()
{
    unordered_set<string> set{};
    unordered_set<string> res{};
    unordered_map<string, unordered_set<string>> map{};
    string tmp{};

    while(true)
    {
        std::cin >> tmp;
        set.insert(tmp);
        if(tmp == "#")break;
    }
    //auto begin = std::chrono::high_resolution_clock::now();

    




    // for(auto s : set)
    // {
    //     for(int i{}; i < s.size(); i++)
    //     {
    //         string tmp1{s.substr(i+1)};
    //         string tmp2{s.substr(0, i+1)};
    //         if (tmp1.empty())break;
    //         //std::cout << s << " : " << tmp1 << "  " << tmp2 << std::endl; 
    //         if(set.find(tmp1) != set.end() && set.find(tmp2) != set.end() && tmp1 != tmp2)
    //         {
    //             //std::cout << "inserting: " << s << std::endl;
    //             res.insert(s);

    //             break;
    //         }
    //     }
    // }
    //std::cout << "Time : " << std::chrono::high_resolution_clock::duration(std::chrono::high_resolution_clock::now() - begin).count() << std::endl;
    //std::cout << "------------------------------------" << std::endl;
    for(auto s : res) std::cout << s << std::endl;
}