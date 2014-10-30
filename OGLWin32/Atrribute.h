#pragma once
#include <map>
#include "CSVColumn.h"
#include <iterator>
class Attribute
{
public:
    Attribute(const CSVColumn& col);
    Attribute(){}
    float GetMean(){ return 0; }
    float GetMode(){ return 0; }
    float GetVariance(){ return 0; }
    float GetStdDev(){ return 0; }
    float GetMedian(){ return 0; }
    float GetMax(){ return 0; }
    float GetMin(){ return 0; }
    std::string GetName(){ return name; }
private:
    size_t totalEntities;
    size_t totalUnique;
    float min;
    float max;


    std::string name; 

    void PopulateMaps(const CSVColumn& col);

    std::map<float, size_t> occuranceMap;
    std::map<float, std::string> defined;



};