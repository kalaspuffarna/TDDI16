#include <iostream>
#include <vector>
#include <algorithm>

struct Node
{
    int marbles;
    std::vector<int> children;
};

int calc(int node_number, std::vector<Node> const &tree, int &tot_moves)
{
    if(tree.size() == 2) return 0;
    int excess{tree[node_number].marbles - 1};
    for (auto child : tree[node_number].children) excess += calc(child, tree, tot_moves);
    tot_moves += std::abs(excess);
    return excess;
}

int find_root(std::vector<Node> const & vn, int n)
{
    std::vector<std::pair<int, bool>> res{};
    res.resize(n+1);
    for(int i{1}; i <= n ; i++) res[i] = std::pair<int, bool>(i,true);
    for(auto node : vn)
    {
        for(int i : node.children)
        {
            res[i].second = false;
        }
    }
    for(auto i : res)
    {
        if(i.second == true) return i.first;
    }
    return 0;
}

int main()
{
    int n{}, tot_moves{}, tmp{};
    std::vector<Node> tree;
    std::vector<int> res{};

    while (std::cin >> n)
    {
        if (n == 0)
            break;
        tree.clear();
        tree.resize(n + 1);
        for (int i{1}; i <= n; i++)
        {
            int node{}, marbles{}, d{};
            std::cin >> node >> marbles >> d;
            tree[node].marbles = marbles;
            tree[node].children.resize(d);
            for (int j{}; j < d; ++j)
            {
                std::cin >> tree[node].children[j];
            }
        }
        tot_moves = 0;
        calc(find_root(tree, n), tree, tot_moves);
        std::cout << tot_moves << std::endl;
    }
    return 0;
}