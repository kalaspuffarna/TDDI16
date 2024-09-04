#include <iostream>
#include <string>

int main()
{
    char c{};
    std::string out{};
    bool first{true};
    while (std::cin >> std::noskipws >> c)
    {
        if (c == '"')
        {
            if (first)
            {
                out.push_back('`');
                out.push_back('`');
            }
            else
            {
                out.push_back('\'');
                out.push_back('\'');
            }
            first = !first;
            continue;
        }
        out.push_back(c);
    }
    std::cout << out;
}