#include <map>

template <typename T>
class Randomizer
{
public:
    static T determineRandom(const std::map<T, int> weights)
    {
        int sum = 0;
        std::pair<T, int> lookup[weights.size()];
        int count = 0;
        for (std::pair<T, int> pair : weights)
        {
            sum += pair.second;
            lookup[count] = std::pair<T, int>{pair.first, sum};
            count++;
        }
        int r = rand() % sum;

        for (size_t i = 0; i < weights.size(); i++)
        {
            if (r < lookup[i].second)
            {
                std::cout << r << " " << lookup[i].first << std::endl;
                return lookup[i].first;
            }
        }

        // Error
        throw std::exception();
    }
};