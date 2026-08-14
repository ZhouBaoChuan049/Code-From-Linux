#include"Log.hpp"
using namespace LogModule ;
int main()
{
    ENABLE_FILE_LOG_STRATEGY();
    LOG(LEVEL::DEBUG)<<"1111"<<"46446";
    return 0 ;
}