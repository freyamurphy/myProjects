package restOfGame;

import java.util.ArrayList;

/**
 * Player
 * 
 * Keeps track of and display a player’s shots. 
 *
 * @author Freya Murphy
 * @version 27-07-17
 */
public class Player
{
    private int noOfShots; // works like a score
    private Shot[] shots;

    /**
     * Constructor for objects of class Player
     * 
     * @param   none
     * @return  none
     */
    public Player()
    {
        noOfShots = 0;
        // At most 100 shots can be made (on a 10x10 board)
        shots = new Shot[100];
    }
    
    /**
     * getNoOfShots
     * 
     * Accessor method for noOfShots field
     * 
     * @param   none
     * @return  number of shots made
     */
    public int getNoOfShots()
    {
        return noOfShots;
    }
    
    /**
     * getShots
     * 
     * Returns ArrayList of player’s shots
     * 
     * @param   none
     * @return  ArrayList of shots
     */
    public Shot[] getShots()
    {
        return shots;
    }
    
    /**
     * makeShot
     * 
     * Gets a coordinate from the user and uses it to create a new shot object
     * 
     * @param   grid
     * @return  shot
     */
    public void makeShot(Grid grid)
    {
        // Get coordinate from user
        int[] coordinate = getValidShotInput();
            
        // Separate row and column part of coordinate
        int row = coordinate[0];
        int column = coordinate[1];
        
        // Create the shot
        Shot shot = new Shot(row, column);
        
        // Check if the shot has aready been made
        while ( isInShotArray(shot) )
        {
            System.out.println("You have already made this shot.");
            
            // Get another shot
            coordinate = getValidShotInput();
            row = coordinate[0];
            column = coordinate[1];
            
            shot = new Shot(row, column);
        }
        
        // Set the shot to a hit or a miss
        shot.checkForHit(grid);
        // Add shot to the array
        addShot(shot);
        
        // Give feedback to user
        if (shot.isHit())
        {
            System.out.println("Hit!");
        }
        else
        {
            System.out.println("Miss!");
        }
    }
    
    /**
     * getValidShotInput
     * 
     * Gets a coordinate input from the user in the correct form and validates it
     * 
     * @param   none
     * @return  array of form [row, column] representing a coordinate
     */
    private int[] getValidShotInput()
    {
        // Variables for processing input
        int ascii = 65;
        char letter;
        int intNumber = 1;
        String strNumber = "1";
        // Variables for validation
        boolean letterIsValid = false;
        boolean numberIsValid = false;
        boolean valid = false;
        
        // This is to prevent an error message being displayed twice
        boolean error = false;
        do
        {
            // Reset error marker
            error = false;
            
            System.out.println("Please enter your shot.");
            // Get shot from user
            String shot = Genio.getString();
            shot = shot.toUpperCase();
            
            try {
                // Extract letter coordinate
                letter = shot.charAt(0);
                // Convert to ascii value to make validation easier
                ascii = (int) letter;
                
                // Extract number coordinate
                strNumber = shot.substring(1, shot.length());
            
                // Convert to int to make validation easier
                intNumber = Integer.parseInt(strNumber);
                // Check if input is valid
                // Letter must be between A and J
                letterIsValid = ascii >= 65 && ascii <= 74;
                // Number must be between 1 and 10
                numberIsValid = intNumber >=1 && intNumber <= 10;
                valid = letterIsValid && numberIsValid;
            }
            catch (NumberFormatException e)
            {
                // This error occurs if the value of strNumber is not a number (so it cannot be converted to an int)
                System.out.println("Invalid shot format. Please enter a letter followed by a number.");
                error = true;
            }
            catch (StringIndexOutOfBoundsException e)
            {
                // This error occurs if the user enters an empty string
                System.out.println("Error. Please enter a coordinate.");
                error = true;
            }
            
            if (!valid && !error)
            {
                System.out.println("Invalid input. Please try again.");
            }

        } while (!valid);

        // The coordinate entered by the user has to be converted into row and column numbers.
        // A is column 0 so the column number is the ascii value of the column letter - 65.
        int column = ascii - 65;
        // The user enters row numbers starting at 1 but row numbers are processed starting at 0
        int row = intNumber - 1;
        
        // Now the values need to be stored in an array to be returned.
        int[] coordinate = {row, column};
        return coordinate;
    }
    
    /**
     * isInShotArray
     * 
     * Checks if a shot has already been made
     * 
     * @param   shot
     * @return  true / false
     */
    public boolean isInShotArray(Shot newShot)
    {
        boolean found = false;
        int position = 0;
        Shot currentShot;
        
        while (!found && position < noOfShots) // Check length using noOfShots so that all the empty positions aren't checked
        {
            currentShot = shots[position];
            // Check if the shots match
            if (currentShot.getRow() == newShot.getRow() && currentShot.getColumn() == newShot.getColumn())
            {
                found = true;
            }
            
            position++;
        }
        
        return found;
    }

    /**
     * addShot
     * 
     * Adds a shot to the shots array
     * 
     * @param   shot
     * @return  none
     */
    public void addShot( Shot shot)
    {
        shots[noOfShots] = shot;
        noOfShots++;
    }
}
