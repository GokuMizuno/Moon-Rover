#include <catch2/catch_test_macros.hpp>
#include "../Moon Rovers/main.cpp"
#include "../Moon Rovers/Rover.h"

int v = main();
Rover rover(1, 1, 'N');
std::string message = "";

TEST_CASE( "Testing function on main", "[main.cpp]")
{
    //main exits normally
    REQUIRE(v == 0);

    //rovers collide
    message = checkRoverCollision(rover, 1, 1);
    REQUIRE(message != "");
    //rovers do not collide
    message = checkRoverCollision(rover, 0, 0);
    REQUIRE(message == "");

    //rover on plateau
    message = checkPlateauCollision(rover, 10, 10);
    REQUIRE(message == "");

    //rover falls off plateau
    rover.SetPosition("MMMMMMMMMMMMMMMMM");
    message = checkPlateauCollision(rover, 3, 3);
    REQUIRE(message != "");
}