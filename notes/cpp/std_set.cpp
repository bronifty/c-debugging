#include <algorithm>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <set>
#include <string_view>
 
template<typename T>
std::ostream& operator<<(std::ostream& out, const std::set<T>& set)
{
    if (set.empty())
        return out << "{}";
    out << "{ " << *set.begin();
    std::for_each(std::next(set.begin()), set.end(), [&out](const T& element)
    {
        out << ", " << element;
    });
    return out << " }";
}
 
int main()
{
    std::set<int> set{1, 5, 3};
    std::cout << set << '\n';
 
    set.insert(2);
    std::cout << set << '\n';
 
    set.erase(1);
    std::cout << set << "\n\n";
 
    std::set<int> keys{3, 4};
    for (int key : keys)
    {
        if (set.contains(key))
            std::cout << set << " does contain " << key << '\n';
        else
            std::cout << set << " doesn't contain " << key << '\n';
    }
    std::cout << '\n';
 
    std::string_view word = "element";
    std::set<char> characters(word.begin(), word.end());
    std::cout << "There are " << characters.size() << " unique characters in "
              << std::quoted(word) << ":\n" << characters << '\n';
}