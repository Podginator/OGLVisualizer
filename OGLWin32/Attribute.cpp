#include "Atrribute.h"

void Attribute::PopulateMaps(const DataColumn& col)
{
    /*for (size_t i = 0; i < col.size; ++i)
    {
        bool contains = false;
        std::map<float, std::string>::iterator mapIt = defined.begin();
        size_t key = 1;
        while (mapIt != defined.end())
        {
            if (mapIt->second == col[i])
            {
                occuranceMap[mapIt->first]++;
                contains = true;
                key++;
                break;
            }
            mapIt++;
            key++;
        }

        if (!contains)
        {
            if (col.GetType() == CSVColumn::Type::Numerical)
            {
                float mapped = std::stof(col[i]);
                occuranceMap[mapped] = 1;
                defined[mapped] = col[i];
                if (mapped > max)
                {
                    max = mapped;
                }
                if (mapped < min)
                {
                    min = mapped;
                }
            }
            else
            {
                occuranceMap[key] = 1;
                defined[key] = col[i];
                if (key > max)
                {
                    max = key;
                }
                if (key < min)
                {
                    min = key;
                }
            }
            totalUnique++;
        }
    }*/
}

Attribute::Attribute(const DataColumn& col)
{
    totalUnique = 0;
    name = col.Name();
    PopulateMaps(col);
    totalEntities = col.size;
}