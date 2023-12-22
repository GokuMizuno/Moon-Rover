#include <iostream>
#include <string>
#include <sstream>
#include <vector>
//#include <wx/wx.h>  //This is not working, and I don't know why.
#include "Map.h"
#include "Rover.h"

/*
*Function:  checkRoverCollision
*Description:  This checks to see if the final resting spots of both rovers is the same
*Input:  rover, and vector<int> of final position of other rover.
*Output:  empty string if no collision, error string otherwise.
*/
std::string checkRoverCollision(Rover rover, std::vector<int> finalPosition)
{
    std::string message = "";
    std::vector<int> pr1Loc = rover.GetPosition();
    if ((pr1Loc[0] == finalPosition[1])&&(pr1Loc[1] == finalPosition[1]))
        message = "Rover collision detected, stopping rover\n";
    return message;
}

/*
*Function:  checkPlateauCollision
*Description:  This checks to see if the rover ends up off the edge of the plateau
*Input:  rover, plateau height and width
*Output:  empty string if no issues, error string otherwise.
*/
std::string checkPlateauCollision(Rover rover, int height, int width)
{
    std::vector<int> parr(2,0);
    std::string message = "";
    parr = rover.GetPosition();
    if ((parr[0] > height)||(parr[1] > width))
        message = "Rover collision detected, stopping rover\n";
    return message;
}

/*
*Function:  doSanityCheckMoveRovers
*Description:  This pulls the input strings from the wx GUI, and breaks them down, and sanity checks them
*Input:  vector<string> containing plateau sizes, initial landing spots, and moves for both rovers.
*Output:  -1 if there is a problem, 0 otherwise.
*NOTE:  Due to the ld linker breaking, for the sake of time, I changed this to main, and broke the vector<string> into individual strings.
*  I am not sure how to fix this; please don't hold it against me.  Linux requires a manual wx ld linker entry in systemd, which I did, but yea...
*/
//int doSanityCheckMoveRovers(vector<string>initialConditions)
int main()
{
    // Toggle TUI_ON between true/false to turn on/off the TUI.
	bool TUI_ON = true;
	int height, width, X, Y;
	char dir;
	height = width = X = Y = 0;

	std::vector<int> finalPosition = {0,0};
	std::string message = "";

    /*Starting conditions which should have come from initialConditions*/
    std::string plateau_size = "5 5";
    std::string r1_start_pos = "1 2 N";
    std::string r1_moves = "LMLMLMLMM";
    std::string r2_start_pos = "3 3 E";
    std::string r2_moves = "MMRMMRMRRM";
	//std::string r2_moves = "MMMMMMMMMMMMMMMMMMMMMMMMMMM";
    std::string temp = "";
    
    /*This is checked in the vxWidgets side of things, but since that library isn't being seen by ldlib, I am duplicating it here.
    The rover1 and rover2 regions are sanity checked in the GUI, when it worked.
    */
    std::stringstream ss(plateau_size);
    int i = 0;
    while (ss.good() && i<2)
    {
        if (i == 0)
        {
            temp = "";
            ss >> temp;
            height = stoi(temp);
        }
        if (i == 1)
        {
            temp = "";
            ss >> temp;
            width = stoi(temp);
        }
        i++;
    }
    ss.str(std::string());
    ss.clear();

    // sanity and bounds testing
    if ((height <= 0)||(width <= 0))
	{
        throw std::invalid_argument("Platform is invalid, check your width or height\n");
		return -1;
	}

	/*creating map with number of coordinates desired
	In lieu of a GUI, which I can't seem to get to work,
	I have added this TUI, for your amusement.*/
	Map map(height, width);

#pragma region ROVER1
    ss << r1_start_pos;
    i = 0;
    while (ss.good() && i<3)
    {
        if (i == 0)
        {
            temp = "";
            ss >> temp;
            X = stoi(temp);
        }
        if (i == 1)
        {
            temp = "";
            ss >> temp;
            Y = stoi(temp);
        }
        if (i == 2)
        {
            temp = "";
            ss >> temp;
            dir = temp[0];
        }
        i++;
    }
    ss.str(std::string());
    ss.clear();

    try
    {    
        if ((X < 0)||(Y < 0))
            throw std::invalid_argument("Rover position is invalid\n");
        if ((X > height)||(Y > width))
            throw std::invalid_argument("Rover position greater than plateau\n");
        if ((toupper(dir) != 'N')&&(toupper(dir) !='E')&&(toupper(dir) != 'S')&&(toupper(dir) != 'W'))
            throw std::invalid_argument("Direction is bad\n");
    }
    catch (std::exception& e)
    {
        std::cerr << "exception: " << e.what() << std::endl;
        return -1;
    } 
	
	/*placing rover in starting point*/
	Rover rover(X, Y, dir);
	if (TUI_ON == true)
	{
		std::cout << "Initial Map:" << std::endl;
		map.Set(rover.GetPosition(), rover.GetRotation());
		std::cout << std::endl;
	}
	/*updating position of rover*/
	std::string instructions = r1_moves;
	rover.SetPosition(instructions);
	finalPosition = rover.GetPosition();
	rover.GetRotation();
	if (TUI_ON == true)
	{
		std::cout << "Final Map:" << std::endl;
		map.Set(rover.GetPosition(), rover.GetRotation());
		std::cout << std::endl;
	}

	message = checkPlateauCollision(rover, height, width);
	if (message != "")
	{
		std::cout << message << std::endl;
		return -1;
	}
	else
		std::cout << finalPosition.at(0) << " " << finalPosition.at(1) << " " << rover.GetRotation() << std::endl;

	instructions.clear();
#pragma endregion ROVER1

	/*Second rover*/
#pragma region ROVER2
    ss << r2_start_pos;
    i = 0;
    while (ss.good() && i<3)
    {
        if (i == 0)
        {
            temp = "";
            ss >> temp;
            X = stoi(temp);
        }
        if (i == 1)
        {
            temp = "";
            ss >> temp;
            Y = stoi(temp);
        }
        if (i == 2)
        {
            temp = "";
            ss >> temp;
            dir = temp[0];
        }
        i++;
    }
    ss.str(std::string());
    ss.clear();

    try
    {
        if ((X < 0)||(Y < 0))
            throw std::invalid_argument("Rover position is invalid\n");
        if ((X > height)||(Y > width))
            throw std::invalid_argument("Rover position greater than plateau\n");
        if ((toupper(dir) != 'N')&&(toupper(dir) !='E')&&(toupper(dir) != 'S')&&(toupper(dir) != 'W'))
            throw std::invalid_argument("Direction is bad\n");
    }
    catch (std::exception& e)
    {
        std::cerr << "exception: " << e.what() << std::endl;
        return -1;
    } 

	Rover rover2(X, Y, dir);
	if (TUI_ON == true)
	{
		std::cout << "Initial Map:" << std::endl;
		map.Set(rover2.GetPosition(), rover2.GetRotation());
		std::cout << std::endl;
	}
	instructions = r2_moves;
	rover2.SetPosition(instructions);
	if (TUI_ON == true)
	{
		std::cout << "Final Map:" << std::endl;
		map.Set(rover2.GetPosition(), rover2.GetRotation());
		std::cout << std::endl;
	}

	message = checkRoverCollision(rover2, finalPosition);
	if (message != "")
	{
		std::cout << message << std::endl;
		return -1;
	}

	message = checkPlateauCollision(rover2, height, width);
	if (message != "")
	{
		std::cout << message << std::endl;
		return -1;
	}
	else
	{
		finalPosition = rover2.GetPosition();
		std::cout << finalPosition.at(0) << " " << finalPosition.at(1) << " " << rover2.GetRotation() << std::endl;
	}

#pragma endregion ROVER2

	return 0;
}
