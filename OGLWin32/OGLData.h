#include <vector>
#include "Proxy.h"
#include "CSVColumn.h"
#include "Atrribute.h"
class OGLData
{
public:
    OGLData(std::vector<CSVColumn> data)
    {
        size = data.size();
        attrs = new Attribute[data.size()];

        for (size_t i = 0; i < data.size(); i++)
        {
            attrs[i] = Attribute(data[i]);
        }

    }
    ~OGLData(){ delete[] attrs; }
    size_t Size(){ return size; }
private:
    size_t size;
    Attribute * attrs;


};