/* Game of Life */
/* Author: Farran Rebbeck 
 * Simple challenge after cpp course */

#include <map>      //data storage type is a map of maps
#include <iostream> //console output
#include <cstdlib>  //rand 
#include <unistd.h> //usleep

/* GameBoard class
 * 
 * Holds the objects and the rule sets for the game
 * also calculates iterations of the game.
 */
class GameBoard
{
	public: 
		// Constructor
		GameBoard() 
		{
			height = 40;
			width = 80;
		}
		// Constructor with custom width and height
		GameBoard(int x, int y) 
		{
			height = x;
			width = y;
		}	
		// Destructor
		~GameBoard() {}

		// Spawn/Create a life point
		void spawnThing(int x, int y) { boardSq[x][y] = true; }

		// Access board point
		bool getPoint(int x, int y) { return boardSq[x][y]; }

		// Output script, print the game board to screen
		const void print()
		{
			for (int y = 0; y < height; ++y)
			{
				for (int x = 0; x < width; ++x)
				{
					// If we have a spawned square, output a *
					if (boardSq[x][y])
					{
						std::cout << "*";
					} else { // If not output a space
						std::cout << " ";
					}
				}
				std::cout << std::endl;
			}
			std::cout << std::endl;
		}

		// Increase time by using operator overload +=
		const GameBoard &operator+=(int t)
		{
			boardSq = playNext(t).boardSq;
			return *this;
		}

		// Play the "next" round, calculate the next iteration GameBoard
		GameBoard playNext(int t)
		{
			// New board for the next stage, will be passed back
			GameBoard evolve;
			for (int y = 0; y < height; ++y) 
			{
				for (int x = 0; x < width; ++x)
				{
					int cN = countNeighbors(x,y);
					// Rules
					// If < 2 neighbors, die (do nothing)
					// If 2 neighbors, lives on / spawn
					if ( (cN == 2) && (boardSq[x][y] == true) ) evolve.spawnThing(x,y);
					// If 3 neighbors, spawn
					if (cN == 3) evolve.spawnThing(x,y);
					// If > 3 neighbors, die (do nothing)
				}
			}
			return evolve;
		}

		// Count the neighbor spawn and return a counter value
		int countNeighbors(int qx, int qy)
		{
			int nCount = 0;
			for (int y = ((qy<=1)?0:(qy-2)); y <= (qy+2); ++y)
			{
				for (int x = ((qx<=1)?0:(qx-2)); x < (qx+2); ++x)
				{
					// Is the current point a neighboring point?
					// calculate the distances between points in x and y
					int distx = ((x-qx)<0)?(qx-x):(x-qx);
					int disty = ((y-qy)<0)?(qy-y):(y-qy);
					// If the current square is populated and nearby by one square
					// count it as a populated neighbor.
					if ( (boardSq[x][y] == true) &&
					     (distx <= 1) &&
					     (disty <= 1) &&
					     !( (distx == 0) && (disty == 0) ) )
					{
						++nCount;
					}
				}
			}
			return nCount;
		}

	private:
		std::map<int,std::map<int,bool> > boardSq;
		int width;
		int height;
};

int main()
{
	// Instanciate GameBoard
	GameBoard Life;

	// Clear the screen
	system("clear");

	// Create some spawn for intial round
	int a;
	for (a = 0; a < 2400; ++a)
		Life.spawnThing( ((std::rand()%80) ),
				 (std::rand()%40) );

	// Print the initial round
	Life.print();

	// Main program loop
	while(1)
	{
		Life += 1;
		system("clear");
		Life.print();
		usleep(10000);
	}
	return 0;
}
