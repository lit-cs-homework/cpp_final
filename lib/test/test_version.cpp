
#include "../nterm.h"

#include <iostream>
#include <cassert>

int main() {
    // test is static
    auto s = nterm::getVersion();
    assert((void*)s == (void*)nterm::getVersion());
}
