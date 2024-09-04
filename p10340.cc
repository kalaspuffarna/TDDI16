#include <string>
#include <iostream>

bool is_subseq(std::string const & a,std::string const& b){
    if(a.size() > b.size()) return false;
    int i=0;
    for(int j=0;j<b.length() && i<a.size();j++){
        if(b[j] == a[i]) i++;
    }
    return i==a.size();
}

int main(){
    std::string pattern,str;
    while(std::cin >> pattern){
        std::cin >> str;
        std::cout << (is_subseq(pattern,str) ? "Yes" : "No") << std::endl;
    }
}