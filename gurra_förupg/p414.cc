#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int count_hole(std::vector<int> &v){
    v.erase(v.begin());
    int min(*std::min_element(v.begin(), v.end()));
    int sum{};
    for (auto i : v){

        sum += i - min;
    }
    return sum;
}

int main(){
    int i{};
    std::string line{};
    std::vector<int> result{};
    while (std::cin >> i){
        if (i != 0){
            result.clear();
            for (i; i >= 0; i--){
                std::getline(std::cin, line);
                result.push_back(line.size() - std::count(line.begin(), line.end(), 'X'));
            }
            std::cout << count_hole(result) << std::endl;
        }
    }
    return 0;
}
