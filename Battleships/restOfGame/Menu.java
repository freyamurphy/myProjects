package restOfGame;

import ships.Fleet;

/**
 * Menu
 * 
 * Displays a menu and handles user input for menu options.
 * The menu options are run from this class by calling methods from other classes.
 * 
 * @author  Freya Murphy
 * @version 29-07-17
 */
public class Menu
{
    private int option;
    private Player player;
    private Grid grid;
    private Fleet fleet;
    private boolean gameOver = false;
    
    /**
     * Constructor for objects of class Menu
     * 
     * @param   none
     * @return  none
     */
    public Menu()
    {
        player = new Player();
        grid = new Grid();
        fleet = new Fleet();
        
        option = 3;
    }
    
    /**
     * main method for Menu
     */
    public static void main( String args[] )
    {
        Menu myGame = new Menu();
        myGame.run();
    }
    
    /**
     * run
     * 
     * Gets option from user and then calls relevant method
     * 
     * @param   none
     * @return  none
     */
    public void run()
    {
        // Display welcome message
        welcome();
        
        /* Call this method at the beginning so that the user can't accidentally crash the program
         * e.g. by firing a shot before initialising the board
         */
        startGame();
       
        // Get choice from the user
        setOpeningOption();
        switch (option)
        {
            case 1:     startGame();
                        break;
                        
            case 2:     loadGame();
                        break;
                        
            case 3:     displayInstructions();
                        break;
                        
            case 4:     gameOver = true;
                        break;
            
            default:    System.out.println("Error. Invalid option.");
                        break;
        }
        
        
        // Game loop
        while (!gameOver)
        {
            setOption();
        
            switch (option)
            {
                case 1:     startGame();
                            break;
                            
                case 2:     fireShot();
                            break;
                            
                case 3:     viewGrid();
                            break;
                            
                case 4:     saveGame();
                            break;
                            
                case 5:     loadGame();
                            break;
                            
                case 6:     displayInstructions();
                            break;
                            
                case 7:     gameOver = true;
                            break;
                
                default:    System.out.println("Error. Invalid option.");
                            break;
            }
        }
    }
    
    /**
     * welcome
     * 
     * Print a message welcoming the user to the game.
     * 
     * @param   none
     * @return  none
     */
    private void welcome()
    {
        System.out.println("Welcome to battleships!");
    }
    
    /**
     * printOpeningMenu
     * 
     * Displays options to the user when the program is first run, before a game has been started / loaded.
     * 
     * @param   none
     * @return  none
     */
    private void printOpeningMenu()
    {
        System.out.println("Enter 1 to start a new game.");
        System.out.println("Enter 2 to load a previously saved game.");
        System.out.println("Enter 3 to view the instructions.");
        System.out.println("Enter 4 to quit.");
    }
    
    /**
     * printMenu
     * 
     * Displays options to the user
     * 
     * @param   none
     * @return  none
     */
    private void printMenu()
    {
        System.out.println("Enter 1 to start a new game.");
        System.out.println("Enter 2 to fire a shot.");
        System.out.println("Enter 3 to view the grid.");
        System.out.println("Enter 4 to save your game.");
        System.out.println("Enter 5 to load a previously saved game.");
        System.out.println("Enter 6 to view the instructions.");
        System.out.println("Enter 7 to quit.");
    }
    
    /**
     * setOpeningOption
     * 
     * Gets an option from the user when the program is first run and validates it.
     * 
     * @param   none
     * @return  none
     */
    private void setOpeningOption()
    {
        System.out.println();
        // Display the menu
        printOpeningMenu();
        
        // Get input from user
        option = Genio.getInteger();
        
        // Validate input
        while (option < 1 || option > 4)
        {
            // Give feedback to user
            System.out.println("Invalid input. Please enter one of the following options:");
            printOpeningMenu();
            
            // Get another input
            option = Genio.getInteger();
        }
    }
    
    /**
     * setOption
     * 
     * Gets an option from the user and validates it.
     * 
     * @param   none
     * @return  none
     */
    private void setOption()
    {
        System.out.println();
        // Display the meny
        printMenu();
        
        // Get input from user
        option = Genio.getInteger();
        
        // Validate input
        while ( option < 1 || option > 7 )
        {
            // Give feedback to user
            System.out.println("Invalid input. Please enter one of the following options:");
            printMenu();
            
            // Get another input
            option = Genio.getInteger();
        }
    }
    
    /**
     * displayInstructions
     * 
     * Displays instructions for the game
     * 
     * @param   none
     * @return  none
     */
    private void displayInstructions()
    {
        String INSTRUCTIONS = "\nBattleships is played on a 10x10 grid. At the start of the game the computer will\nplace its fleet on the grid. A fleet is made up of one battleship, two cruisers,\nthree destroyers and four submarines. Each type of ship takes up a different number\nof squares on the grid and ships may be placed vertically or horizontally. The aim\nof the game is to destroy the computer's fleet in the minimum number of shots. After\nmaking a shot the outcome (hit or miss) will be displayed and whether you sunk any\nships. Hits are represented on the grid by an X and misses by a O. Shots that have not\nbeen made are represented by a -. Using the in-game menu you can choose to start a new\ngame, make a shot, save your game or load a previous game. ";
        System.out.println(INSTRUCTIONS);
    }
    
    /**
     * startGame
     * 
     * Starts a new game of battleships and randomly positions ships on grid.
     * 
     * @param   none
     * @return  none
     */
    public void startGame()
    {
        // Reset objects needed for the game
        player = new Player();
        grid = new Grid();
        fleet = new Fleet();
        
        // Initialise grid by randomly placing ships
        fleet.placeShips(grid);
    }
    
    /**
     * fireShot
     * 
     * Gets a grid position from the user and updates the grid with the shot
     * 
     * @param   none
     * @return  none
     */
    public void fireShot()
    {
        // Display the grid
        grid.display( player.getShots() );
        
        // Get the player's shot
        player.makeShot(grid);
        
        // Check if the fleet is destroyed
        fleet.checkIfDestroyed( player.getShots(), player.getNoOfShots() );
        
        if (fleet.isDestroyed())
        {
            System.out.println("Game over!");
            System.out.println("You took " + player.getNoOfShots() + " moves to destroy the fleet.");
        }
    }
    
    /**
     * viewGrid
     * 
     * Grid showing ships hit and shots fired is displayed
     * 
     * @param   none
     * @return  none
     */
    private void viewGrid()
    {
        // Display the grid
        grid.display( player.getShots() );
    }
    
    /**
     * saveGame
     * 
     * Saves the current game state to a text file.
     * 
     * @param   none
     * @return  none
     */
    private void saveGame()
    {
        SavedGame game = new SavedGame();
        game.saveGame(fleet, player.getShots(), player.getNoOfShots());
    }
    
    /**
     * loadGame
     * 
     * Loads previously saved game from a text file.
     * 
     * @param   none
     * @return  none
     */
    private void loadGame()
    {
        SavedGame game = new SavedGame();
        
        // Only attempt to load the file if a game is saved there.
        if (!game.isEmpty())
        {
            // Load game from file
            loadGameInfo gameInfo = game.loadGame();
            
            // Get fleet and player from the loaded data
            fleet = gameInfo.getFleet();
            player = gameInfo.getPlayer();
            
            // Initialise grid
            grid = new Grid();
            grid.updateGridData(fleet.getShips());
        }
        else
        {
            System.out.println("There is no game to load.");
        }
    }
}
