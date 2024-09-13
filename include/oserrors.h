


#include <system_error>

namespace oserr
{

struct Code {
    operator int();
    Code(int e);
private:
    int error;
};


std::string msg(Code);

Code cur();


// after error occurs
void raise(Code lastError = cur(),
        const char* const additional = NULL);



} // namespace oserr

