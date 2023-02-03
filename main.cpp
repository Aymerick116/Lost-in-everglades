/*
 contributors:
              Fernandez, Kevin
              Osse, Aymerick
              Haire, Joseph
              Reid, Andrelene

    Lost in the Everglades is an RPG (Role-Playing-Game) between a player and the computer.

    A group of tourists has been lost in the Everglades and a ranger must rescue them before time runs out.

    The Everglades are represented by a 5x5 matrix. The ranger (R) starts the rescue at the upper-left corner
    of the park, the group of tourists (T) are lost at the lower-right corner. The ranger has 12 gongs of time
    to find and rescue the tourists before they perish.

    Input: 
           1. Ask user for option to play game, see the rules, or quit game.
           2. Ask user to move the ranger through grid cells by entering the row and collumn numbers
           3. If a danger is encountered, ask user to fight or hide

    Processing: 
           1. Run menu and display options
           2. Call the function corresponding to the menu option
           3. Creat a grid to show the Rangers(R) and Tourists(T) location
           4. Create a grid that contains 10 dangers randomly placed within
           5. Move Ranger within the space of the grid
           6. Encounter danger within grid
           7. If chosen to fight, randomly decide if the Ranger wins or loses
           8. Count down how many gongs are left after every move and/or action taken
           9. Determine if Ranger reaches Tourists before out of gongs

    Output:
           1. Display menu and options
           2. Display the rules function if rules option is chosen
           3. Display game if start game option is chosen 
           4. Display game grid
           5. Display user prompts


*/


#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <random>
using namespace std;

//function prototypes
void startGame();
void seeRules();
void printMap(char map[][5]);
void createDangers(char map[][5]);

int main() 
{
    //variables
    int gongs = 12;
    int gridRange = 1;
    int RowInput, ColInput;
    int option;
    const int ROWS = 5, COLS = 5;
    int x = 0, y = 0;
    //char map[ROWS][COLS];
    //char monsterMap[ROWS][COLS];

    //intro
    cout << "Welcome to The Ranger Game!\n\n";

    do 
    {
        cout << "Please choose an option:\n"
            << "Option 1: Rules\n"
            << "Option 2: Start game\n"
            << "Option 3: Quit\n"
            << "\nOption: ";
        cin >> option;
        cout << endl;

        switch (option) 
        {
            case 1:            
                seeRules();     //displays rules of game
                break;

            case 2:            
                startGame();    //starts game
                break;  

            case 3:             //user chose to quit
                cout << "\nGoodbye...";
                break;
            default:
                cout << "Sorry invalid input. Please pick an option 1-3...\n\n";
        }
    } while (option != 3);      //do while option isn't quit

    return 0;
}

void seeRules() // details and rules of the game
{
    
    cout << "Welcome to Lost in everglades!" << endl;
    cout << endl;
    cout << "Description..." << endl;
    cout << "----------------------------------------------------------------------------------------------------------------" << endl;
    cout << "Lost in the Everglades in an RPG (Role-Playing-Game) between a player and the computer.\n A group of tourists have been lost in the Everglades and a ranger must rescue them before time runs out.The Everglades are represented by a 5x5 matrix. The ranger (R) starts the rescue at the upper-left corner of the park, the group of tourists (T) are lost at the lower-right corner.\n The ranger has 12 gongs of time to find and rescue the tourists before they perish. During the journey, the ranger might find dangers (hungry alligator, swarm of giant mosquitoes, venomous spider, or python). When the ranger finds a danger, they can choose to fight them, or hide and wait for them to leave." << endl;
    cout << endl;

    cout << "Rules..." << endl
        << "------------------------------------------------------------------------------------------------------------------" << endl;

    cout << "If Ranger Waits:\n"
        << "    * Moves to desired cell \n"
        << "    * Loses 5 gongs of time" << endl;
    cout << endl;

    cout << "If the Ranger fights and wins:\n"
        << "     * Moves to the desired cell\n"
        << "     * Loses 2 gongs of time\n" << endl;
    cout << endl;

    cout << "If the Ranger fights and loses\n"
        << "     * Goes back to the initial cell\n"
        << "     * Loses 3 gongs of time\n"
        << "     * The danger remains in the cell" << endl;
    cout << endl;

    cout << "If the Ranger moves to a cell with no dangers:\n"
        << "     * Loses 1 gong of time\n" << endl;
    cout << endl;

    cout << "The game ends when either:\n"
        << "     * The Ranger rescues the group of tourists\n"
        << "     * The time expires and the fate of the tourists is forever unknown. " << endl;
    cout << endl;
}

void startGame() 
{
    // variables
    int gongs = 12, currentX = 0, currentY = 0, RowInput, ColInput, decision;
    const int ROWS = 5, COLS = 5;
    char map[ROWS][COLS];
    char monsterMap[ROWS][COLS];
    string dangerName[] = { "Hungry Alligator", "Swarm of Giant Mosquitos", "Venomous Spider", "Python" };

    //random number generator
    int offset = 1;
    int range = 10;
    srand((unsigned)time(NULL));
    int random;

    //start of game
    cout << "Lost in the Everglades ...\n" << endl;

    //making grid
    for (int row = 0; row < ROWS; row++) 
    {
        for (int col = 0; col < COLS; col++) 
        {
            map[row][col] = '*';
        }
    }

    //sets ranger and tourists in their spots
    map[0][0] = 'R';
    map[4][4] = 'T';
    monsterMap[0][0] = 'R';
    monsterMap[4][4] = 'T';

    //parallel arrays for player movement and danger detection
    createDangers(monsterMap);
    
    while (gongs > 0 && (currentX != 4 || currentY != 4)) //continues playing as long as gongs are left and the ranger has not reached the tourists location
    {     

        printMap(map); // prints map while in the WHILE loop
        
        cout << "Gongs Left: " << gongs << endl << endl; // show gongs and ask for player input
        cout << "Enter next cell (row & col): ";
        cin >> RowInput >> ColInput;

        // movement validation
      // out of bounds?
        if (RowInput < 0 || ColInput < 0 || RowInput > 4 || ColInput > 4) 
        {
            cout << "\nThats out of bounds, try again.\n";
            
        }
          //already in the same area?
                else if (map[RowInput][ColInput] == map[currentX][currentY]){
                  cout << "\nYou are already in this area!\n" << endl;
                }
        else if (map[RowInput] < map[currentX + 2] && map[ColInput] < map[currentY + 2] && map[RowInput] > map[currentX - 2] && map[ColInput] > map[currentY - 2]) 
        {
            // finding danger
            if (monsterMap[RowInput][ColInput] == 'A' || monsterMap[RowInput][ColInput] == 'M' || monsterMap[RowInput][ColInput] == 'S' || monsterMap[RowInput][ColInput] == 'P') 
            {
                //shows hidden danger
                map[RowInput][ColInput] = monsterMap[RowInput][ColInput];

                if (monsterMap[RowInput][ColInput] == 'A')
                {
                    cout << "---> Watch out! There is a " << dangerName[0] << " ahead.\n\n";
                }
                    else if (monsterMap[RowInput][ColInput] == 'M')
                    {
                        cout << "---> Watch out! There is a " << dangerName[1] << " ahead.\n\n";
                    }
                        else if (monsterMap[RowInput][ColInput] == 'S')
                        {
                            cout << "---> Watch out! There is a " << dangerName[2] << " ahead.\n\n";
                        }   
                                else 
                                { 
                                    monsterMap[RowInput][ColInput] = 'P';
                                    cout << "---> Watch out! There is a " << dangerName[3] << " ahead.\n\n";
                                }

                cout << "Choose your next move\n"
                        << "\t1 - fight\n"
                        << "\t2 - hide\n";
              
                    cout << "\nMove: ";
                    cin >> decision;
                    cout << endl;
                //danger choice validation
                while (decision != 1 && decision != 2)
                {  
                    //ask user to fight or hide
                    cout << "Invalid choice. Please choose 1 or 2.\n"
                        << "Choose your next move\n"
                        << "\t1 - fight\n"
                        << "\t2 - hide\n";
                  cout << "\nMove: ";
                    cin >> decision;
                    cout << endl;
                }

                    //switch case to ask user to fight or hide

                    switch (decision)
                    {
                        case 1:  //fight

                        random = offset + (rand() % range);     //random number generated

                        if (random >= 1 && random <= 6)
                        {    
                            //won the fight
                            map[RowInput][ColInput] = ' ';
                            
                            gongs -= 2;
                          if (monsterMap[RowInput][ColInput] == 'A')
                        {
                            cout << "---> You fight the " << dangerName[0] << " and win... You Advance!\n" << endl;
                        }   
                        else if (monsterMap[RowInput][ColInput] == 'M')
                        {
                            cout << "---> You fight the " << dangerName[1] << " and win... You Advance!\n" << endl;
                        }   else if (monsterMap[RowInput][ColInput] == 'S')
                        {
                            cout << "---> You fight the " << dangerName[2] << " and win... You Advance!\n" << endl;
                        }   if (monsterMap[RowInput][ColInput] == 'P')
                        {
                            cout << "---> You fight the " << dangerName[3] << " and win... You Advance!\n" << endl;
                        }   
                            
                          monsterMap[RowInput][ColInput] = ' ';
                            map[RowInput][ColInput] = 'R';
                            map[currentX][currentY] = ' ';
                            monsterMap[RowInput][ColInput] = 'R';
                            monsterMap[currentX][currentY] = ' ';
                            currentX = RowInput;
                            currentY = ColInput;
                            // player advances and loses 2 gongs
                        }
                        else
                        {    
                            //loses the fight
                            gongs -= 3;
                           if (monsterMap[RowInput][ColInput] == 'A')
                        {
                            cout << "---> You fight the " << dangerName[0] << " and lose... Retreat.\n" << endl;
                        }   
                        else if (monsterMap[RowInput][ColInput] == 'M')
                        {
                            cout << "---> You fight the " << dangerName[1] << " and lose... Retreat.\n" << endl;
                        }   else if (monsterMap[RowInput][ColInput] == 'S')
                        {
                            cout << "---> You fight the " << dangerName[2] << " and lose... Retreat.\n" << endl;
                        }   if (monsterMap[RowInput][ColInput] == 'P')
                        {
                            cout << "---> You fight the " << dangerName[3] << " and lose... Retreat.\n" << endl;
                        }  
                            
                            // player retreats to previous cell and loses 3 gongs
                        }
                        break;

                        case 2:  //hide

                          
 if (monsterMap[RowInput][ColInput] == 'A')
                        {
                            cout << "---> The " << dangerName[0] << " has passed. You advance!\n\n";
                        }   
                        else if (monsterMap[RowInput][ColInput] == 'M')
                        {
                            cout << "---> The " << dangerName[1] << " is gone. You advance!\n\n";
                        }   else if (monsterMap[RowInput][ColInput] == 'S')
                        {
                            cout << "---> The " << dangerName[2] << " has passed. You advance!\n\n";
                        }   if (monsterMap[RowInput][ColInput] == 'P')
                        {
                            cout << "---> The " << dangerName[3] << " has passed. You advance!\n\n";
                        }   
                            

                        map[RowInput][ColInput] = 'R';
                        map[currentX][currentY] = ' ';
                        monsterMap[RowInput][ColInput] = 'R';
                        monsterMap[currentX][currentY] = ' ';
                        currentX = RowInput;
                        currentY = ColInput;

                        cout << endl;
                        gongs -= 5;
                        //player hides and loses 5 gongs
                        break;

                        default:
                        cout << "Error. Invalid option. Try again.\n" << endl;
                    }
                

            }    //end of if statement detecting danger

            else 
            {      //no danger detected
                cout << "---> Cell (" << RowInput << ", " << ColInput << ") is free... Able to move!" << endl;

                map[RowInput][ColInput] = 'R';
                map[currentX][currentY] = ' ';
                monsterMap[RowInput][ColInput] = 'R';
                monsterMap[currentX][currentY] = ' ';
                currentX = RowInput;
                currentY = ColInput;

                cout << endl;
                gongs -= 1;
                
                // player advances and loses 1 gong of time
            }
        }
        else
            cout << "Too far!" << endl;
        //to check if ranger is in range to move to the next grid
        //if row and column entered is greater than ranger's area, ranger will not move
        //will repeat until row and column entered is valid
        //if row input and column input is not greater than the grid range
    }
        if (currentX == 4 && currentY == 4) 
        {      
            //if ranger reaches the tourists
            cout << "Congratulations! You have saved the tourists! \n\n"
                << "Care to rescue them again?\n\n";
        }
        else if (gongs <= 0) 
        {      
            //if user runs out of gongs
            cout << "You have ran out of moves and the tourists are forever lost in the Everglades. Oops...\n\n"
                << "Care to try again?\n\n";
        }
}

void printMap(char map[][5])           //printing grid (Everglades map)
{
    /*
  - 0 - 1 - 2 - 3 - 4 -
  0 | R | * | * | * | * |
  1 | * | * | * | * | * |
  2 | * | * | * | * | * |
  3 | * | * | * | * | * |
  4 | * | * | * | * | T |
  */

     /*number row*/
   cout << "  " << "   " << "0" << "   " << "1" << "   " << "2" << "   " << "3" << "   " << "4" << "   " << endl;

    //displays contents of map
    int ROWS = 5, COLS = 5;

    for (int i = 0; i < ROWS; i++) 
    {
        cout << i << " ";

        for (int j = 0; j < COLS; j++) 
        {
            cout << " | " << map[i][j];
        }
        cout << " | " << endl;
    }
    cout << endl;
}

void createDangers(char map[][5]) 
{
    //make for loop that goes through each cell in array and randomly decides if danger lurks there. continue traversing array until 10 dangers are placed
    int offset = 1;
    int range = 10;
    srand((unsigned)time(NULL));
    int random = offset + (rand() % range);
    int dangerrand = (rand() % 4);
    char dangerFill[] = { 'A', 'M', 'S', 'P' };
    int totalMonsters = 10, monstersPlaced = 0;
    const int ROWS = 5, COLS = 5;

    while (monstersPlaced < totalMonsters) //loop while less than 10 monsters are in the array
    {
        for (int i = 0; i < ROWS; i++) 
        {
            for (int j = 0; j < COLS; j++) 
            {
                random = offset + (rand() % range);
                dangerrand = (rand() % 4);

                if (random >= 1 && random <= 4 && monstersPlaced < totalMonsters && (map[i][j] == 0 || map[i][j] == 32)) //0 = NULL, 32 = Space ' '
                { // while random is in range, AND less than 10 monsters placed, AND if the array element is equal to 0 or 32...
                  // add monster to array

                    if (dangerrand == 0 || dangerrand == 1 || dangerrand == 2 || dangerrand == 3) 
                    {
                        map[i][j] = dangerFill[dangerrand];
                        monstersPlaced++;
                    }
                }
                else if (map[i][j] != 'A' && map[i][j] != 'M' && map[i][j] != 'S' && map[i][j] != 'P' && map[i][j] != 'R' && map[i][j] != 'T') 
                {
                    map[i][j] = 32;
                }
            }
        }
    }
    
}
