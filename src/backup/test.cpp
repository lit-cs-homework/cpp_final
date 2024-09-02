
#include "../../include/backup.h"

using T = int;

int main() {
    auto bk = Backup::Cwd();

    if(bk.hasData()) {
        T x = bk.load<T>();
        std::cout << x << std::endl;
    } else {
      // ...
      T x = 1;
      bk.save(x);
    }

}
