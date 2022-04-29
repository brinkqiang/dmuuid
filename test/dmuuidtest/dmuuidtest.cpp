
#include "dmuuid.h"
#include "dmformat.h"

int main(int argc, char* argv[]) {
    CUUID UUID;

    for (int i = 0; i < 10; i++)
    {
        auto id = UUID.generate();
        fmt::print("index:{} uuid:{}\n", i, id.str());
    }
    return 0;
}
