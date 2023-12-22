#include <catch2/catch_test_macros.hpp>
#include "../Moon Rovers/Rover.h"
Rover rover(1,1, 'N');
std::vector<int> v(2,0);
std::string moves = "MRM";

TEST_CASE( "Testing rover", "[rover]" )
{
    //catch2 recommends REQUIRE over assert.
    REQUIRE(rover.GetRotation() == 'N');
    v = rover.GetPosition();
    REQUIRE(v.at(0) == 1);
    REQUIRE(v.at(1) == 1);

    //Move the rover and rotate it.
    rover.SetPosition(moves);
    v.clear();
    v = rover.GetPosition();
    REQUIRE(v.at(0) != 0);
    REQUIRE(rover.GetRotation() == 'S');
}