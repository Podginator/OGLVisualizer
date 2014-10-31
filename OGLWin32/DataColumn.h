#pragma once
#include <string>
#include <vector>
#include <array>
#include <map>
class DataColumn
{
public:
    std::string Name() const{ return header; } 
    void Name(std::string name){ header = name;}
    virtual void Add(std::string cell) = 0;
    virtual std::map<std::string, float> GetDistribution() = 0;

    DataColumn(size_t size) :size(size), index(0){}
    size_t size;

    ~DataColumn()
    {
    }

protected:
    std::string header;
    std::size_t index;
    
};


class DataColumnString : public DataColumn
{
public:
    DataColumnString(size_t _size) :DataColumn(_size)
    {
        data = std::vector<std::string>(_size);
    }

    std::map<std::string, float> GetDistribution()
    {
        std::map<std::string, float> res; 

        for (size_t i = 0; i < size; i++)
        {
            if (res.count(data[i]) == 1)
            {
                res[data[i]]++;
            }
            else
            {
                res[data[i]] = 1;
            }
        }

        std::map<std::string, float>::iterator mapIt = res.begin();
        while (mapIt != res.end())
        {
            mapIt->second /= size;
            mapIt++;
        }

        return res;

    }

    void Add(std::string cell)
    {
        data[index++] = cell;
    }

private:
    std::vector<std::string> data;
};

class DataColumnFloat : public DataColumn
{
public:
    DataColumnFloat(size_t _size) :DataColumn(_size)
    {
        data = std::vector<float>(_size);
    }

    void Add(std::string cell)
    {
        data[index++] = std::stof(cell);
    }

    std::map<std::string, float> GetDistribution()
    {
        std::map<std::string, float> res;

        for (size_t i = 0; i < size; i++)
        {
            if (res.count(std::to_string(data[i])) == 1)
            {
                res[std::to_string(data[i])]++;
            }
            else
            {
                res[std::to_string(data[i])] = 1;
            }
        }

        std::map<std::string, float>::iterator mapIt = res.begin();
        while (mapIt != res.end())
        {
            mapIt->second /= size;

            mapIt++;
        }

        return res;

    }

private:
    std::vector<float> data;
};

class DataColumnInt : public DataColumn
{
public:
    DataColumnInt(size_t _size) :DataColumn(_size)
    {
        data = std::vector<int>(_size);
    }

    void Add(std::string cell)
    {
        data[index++] = std::stoi(cell);
    }

    std::map<std::string, float> GetDistribution()
    {
        std::map<std::string, float> res;

        for (size_t i = 0; i < size; i++)
        {
            if (res.count(std::to_string(data[i])) == 1)
            {
                res[std::to_string(data[i])]++;
            }
            else
            {
                res[std::to_string(data[i])] = 1;
            }
        }

        std::map<std::string, float>::iterator mapIt = res.begin();
        while (mapIt != res.end())
        {
            mapIt->second /= size;
            mapIt++;
        }

        return res;

    }

private:
    std::vector<int> data;
};