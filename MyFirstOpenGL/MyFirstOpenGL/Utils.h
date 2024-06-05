#pragma once
#include <random>
#include <glm.hpp>

class Utils
{
public:
    static float RandomRange(float min, float max) 
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> dis(min, max);
        return dis(gen);
    }


    static int RandomRange(int min, int max) 
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dis(min, max);
        return dis(gen);
    }

    static glm::vec3 GetUniquePosition(std::vector<glm::vec3>& positions)
    {
        int index = RandomRange(0, positions.size() - 1);
        glm::vec3 pos = positions[index]; //saves pos before deleting
        positions.erase(positions.begin() + index);
        return pos;
    }


};

