#include <vector>
#include "Proxy.h"
#include "CSVColumn.h"
#include "Atrribute.h"
class OGLData
{
public:
    OGLData(std::vector<CSVColumn> data);
    ~OGLData(){ delete[] attrs; }
    size_t Size(){ return size; }
private:
    size_t size;
    Attribute * attrs;


};