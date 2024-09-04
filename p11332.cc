#include <vector>
#include <iterator>
#include <iostream>

int g(int n)
{
    int ret{};
    while (n > 0)
    {
        ret += n % 10;
        n /= 10;
    }
    if (ret > 10)
    {
        return g(ret);
    }
    return ret;
}
int main()
{
    int i{};
    while (std::cin >> i)
    {
        std::cout << g(i) << std::endl;
    }
    return 0;
}