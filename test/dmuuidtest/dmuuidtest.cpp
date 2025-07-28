
#include "dmuuid.h"
#include "dmformat.h"

#include "gtest.h"
#include <map>

TEST(dmuuid, dmuuid_100w) {
    CUUID UUID;

    std::map<std::string, int> map;

    for (int i = 0; i < 1000000; i++)
    {
        auto id = UUID.generate();
        auto& count = map[id.str()];
        count++;
        if (count > 1)
        {
            ASSERT_TRUE(0);
        }
    }
    fmt::print("Done\n");
}
