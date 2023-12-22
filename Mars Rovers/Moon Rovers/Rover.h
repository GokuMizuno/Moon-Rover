#pragma once
#include <iostream>
#include <vector>
#include "Map.h"

class Rover
{
private:
	//position of rover in coordinates of map
	int rX, rY;
	std::vector<int> rPosition = { rX, rY };

	//direction the rover is facing
	char rRotation;
	char rDirection[4] = { 'N', 'E', 'S', 'W' };

public:
	Rover(int x, int y, char r) : rX{x}, rY{y}, rRotation{r}
	{
		//init the rover
	}

	std::vector<int> GetPosition()
	{
		//std::cout << rPosition[0] << " " << rPosition[1] << std::endl;
		return rPosition;
	}

	char GetRotation()
	{
		//std::cout << rRotation << std::endl;
		return rRotation;
	}

	void SetPosition(string instructions)
	{
		for (int i = 0; i < instructions.size() ; i++)
		{
			if (instructions[i] == 'M')
			{
				if (rRotation == 'W' || rRotation == 'E')
				{
					rX += (rRotation == 'W') ? -1 : 1;
				}

				else
				{
					rY += (rRotation == 'S') ? -1 : 1;
				}
			}

			else
			{
				SetRotation(instructions[i]);
			}
		}

		rPosition[0] = rX;
		rPosition[1] = rY;
	} 

	char SetRotation(char rotation)
	{
		int rotate_rover = (rotation == 'L') ? -1 : 1;

		for (int i = 0; i < sizeof(rDirection); i++)
		{
			if (rRotation == rDirection[i])
			{
				i += (rotate_rover);
				//handling whenever turn is negative (N -> W) and greater than array size whenever (W -> N)
				i = (i < 0) ? (sizeof(rDirection) - 1) : i;
				i = (i == sizeof(rDirection)) ? 0 : i;

				rRotation = rDirection[i];
				break;
			}
		}
		
		return rRotation;
	}

	std::string CollisionCheck(int X, int Y)
	{
		std::string message = "";
		if ((rX == X)&&(rY == Y))
			message = "Collision detected, stopping.";
		return message;
	}
};
