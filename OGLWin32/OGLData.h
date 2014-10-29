#include <vector>
#include "Proxy.h"
#include "CSVColumn.h"
class OGLData
{
public:
    OGLData(std::vector<CSVColumn> data);

private:
    size_t sectionCount;
    size_t elements; 


};