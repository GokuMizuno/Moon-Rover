#include <catch2/catch_test_macros.hpp>
#include "../Moon Rovers/Map.h"

Map map(2,2);
std::vector<int>out = {1,1};
map.Set(out, 'N');
std::vector<int> v = map.Get();

TEST_CASE( "Testing the Map TUI", "[map]" )
{
    REQUIRE(v.size() > 0);
    REQUIRE(v.at(1) == 'N');
}