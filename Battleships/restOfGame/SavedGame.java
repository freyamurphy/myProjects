package restOfGame;

import java.io.*;
import ships.*;

/**
 * Save and load game from text file.
 *
 * @author Freya Murphy
 * @version 31-07-17
 */
public class SavedGame
{
    private File file;
    private boolean empty;

    /**
     * Constructor for objects of class SavedGame
     */
    public SavedGame()
    {
        file = new File("battleships.txt");
        
        // If the file has 0 length or does not exist then empty is set to true
        empty = file.length() == 0;
    }
    
    /**
     * isEmpty
     * 
     * Accessor method for empty field
     * 
     * @param   none
     * @return  empty
     */
    public boolean isEmpty()
    {
        return empty;
    }
    
    /**
     * loadGame
     * 
     * Loads saved game from text file and allows user to continue playing
     * 
     * @param   none
     * @return  none
     */
    public loadGameInfo loadGame()
    {
        // Game objects to be read into
        Fleet fleet = new Fleet();
        Player player = new Player();
            
        // Number of ships in fleet
        int noOfShips = fleet.getShips().length;
 
        // Current ship being read
        Ship ship;
        // Current GridSpace being read
        GridSpace currentSpace;
        // Curent position being read
        char charRow;
        char charCol;
        int row = 0;
        int col = 0;
            
        // Current shot being read
        Shot shot;
        // Whether current shot is a hit or a miss
        boolean hit;
        
        // fleet and player must be return as properties of another class
        loadGameInfo returnValue;
        
        try
        {
            // Create file reading objects
            FileReader fileReader = new FileReader(file);
            BufferedReader reader = new BufferedReader(fileReader);

            // Read a line of the file
            String data = reader.readLine();
            
            // Counter for end of loop
            int counter = 0;
            
            // Read in positions of ships
            while (data != null && counter < noOfShips)
            {
                // Get a ship from the fleet
                ship = fleet.getShip(counter);

                for (int i = 0; i+1 < data.length(); i+=2)
                {
                    
                    // Extract next position from the line being read in
                    charRow = data.charAt(i);
                    charCol = data.charAt(i+1);
                    
                    // Convert position variables to integers
                    row = Character.getNumericValue(charRow);
                    col = Character.getNumericValue(charCol);
                    
                    // Save the row and column into a GridSpace
                    currentSpace = new GridSpace(row, col);

                    // Save this to the ship
                    ship.setOccupiedSquare(currentSpace, i/2);
                }
                
                // Get next line
                data = reader.readLine();
                counter++;
            }

            // Read in shots
            while (data != null)
            {
                // The first two characters of data are the position of the shot
                charRow = data.charAt(0);
                charCol = data.charAt(1);
                
                // Convert position variables to integers
                row = Character.getNumericValue(charRow);
                col = Character.getNumericValue(charCol);
                
                // The third character is whether the shot was a hit or a miss
                if (data.charAt(2) == '1')
                {
                    hit = true;
                }
                else
                {
                    hit = false;
                }
                
                // Create the shot and add it to player
                shot = new Shot(row, col, hit);
                player.addShot(shot);
                
                data = reader.readLine();
            }
        }
        catch (IOException e)
        {
            System.out.println("Error. Unable to load file.");
        }
        System.out.println("Game loaded.");
        
        returnValue = new loadGameInfo(player, fleet);
        return returnValue;
    }
    
    /**
     * saveGame
     * 
     * Saves shots fired and positions of ships for both players to a text file.
     * 
     * @param   grid with position of ships, array of shots fired, number of shots fired
     * @return  none
     */
    public void saveGame(Fleet fleet, Shot[] shots, int noOfShots)
    {
        // Array of ships
        Ship[] ships;
        // Current ship being sent to file
        Ship currentShip;
        // Array of GridSpaces occupied by ship
        GridSpace[] occupiedSquares;
        // Current GridSpace being sent to the file
        GridSpace currentSpace;
        // Row of currentSpace
        int row;
        // Column of currentSpace
        int col;
        // Current shot being sent to file
        Shot shot;
            
        ships = fleet.getShips();
        
        try
        {
            // Create objects needed to write to file
            FileOutputStream outputStream;
            PrintWriter printWriter;
            outputStream = new FileOutputStream(file);
            printWriter = new PrintWriter(outputStream);
 
            for (int i = 0; i < ships.length; i++)
            {
                // Get the ship and the squares it occupies
                currentShip = ships[i];
                occupiedSquares = currentShip.getOccupiedSquares();
                
                // Send each square to the file
                for (int j = 0; j < occupiedSquares.length; j++)
                {
                    currentSpace = occupiedSquares[j];
                    
                    // Get the position the occupied space
                    row = currentSpace.getRow();
                    col = currentSpace.getColumn();
                    
                    // Send position to file 
                    printWriter.print(row);
                    printWriter.print(col);
                }
                
                // Start a new line in the file for the next ship
                if (i < ships.length - 1)
                {
                    printWriter.println();
                }
            }
            
            // Send shots to file
            for (int i = 0; i < noOfShots; i++)
            {
                shot = shots[i];
                
                // Take a new line for the shot
                printWriter.println();
                
                // Send position of shot to file
                printWriter.print(shot.getRow());
                printWriter.print(shot.getColumn());
                
                // A hit is represented by a 1 and a miss by a 0.
                if (shot.isHit())
                {
                    printWriter.print("1");
                }
                else
                {
                    printWriter.print("0");
                }
            }
           
            // Close connection
            printWriter.flush();
            printWriter.close();
            
            System.out.println("Game saved to " + file + ".");
        }
        catch (IOException e)
        {
            System.out.println("Error. Cannot write to file.");
        }
    }
}
