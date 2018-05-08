package ships;

import restOfGame.Grid;
import restOfGame.GridSpace;
import java.util.Random;
import restOfGame.Shot;

/**
 * Ship
 * 
 * Keeps track of the position of a ship on the grid
 * 
 * @author  Freya Murphy
 * @version 29-07-17
 */
public class Ship
{
    /* The protected keyword means these fields can be accessed by other class in this package.
     * This means all the subclasses of ship inherit these fields.
     */
    // The GridSpaces occupied by the ship (it's position)
    protected GridSpace[] occupiedSquares;
    
    // The number of GridSpaces occupied by the ship
    protected int size;
    
    // Whether or not all of the ship's occupied GridSpaces have been hit
    protected boolean sunk;
    
    // Class name
    String name;
    
    /**
     * Constructor for objects of class Ship
     * 
     * @param   none
     * @return  none
     */
    public Ship()
    {
        sunk = false;
        // Get the name of the class
        name = this.getClass().getSimpleName().toLowerCase();
    }
    
    /**
     * isSunk
     * 
     * Accessor method for sunk field
     * 
     * @param   none
     * @return  sunk
     */
    public boolean isSunk()
    {
        return sunk;
    }
    
    /**
     * getOccupiedSquares
     * 
     * Accessor method for occupiedSquares field
     * 
     * @param   none
     * @return  array of occupied GridSpaces
     */
    public GridSpace[] getOccupiedSquares()
    {
        return occupiedSquares;
    }
    

    /**
     * getSize
     * 
     * Accessor method for size field
     * 
     * @param   none
     * @returns size of ship (number of squares it occupies)
     */
    public int getSize()
    {
        return size;
    }
    
    /**
     * setOccupiedSquare
     * 
     * Sets the value of occupiedSquares array at a specified index
     * 
     * @param   GridSpace to be added, index
     * @return  none
     */
    public void setOccupiedSquare(GridSpace gridSpace, int index)
    {
        occupiedSquares[index] = gridSpace;
    }
    
    /**
     * checkIfSunk
     * 
     * Checks if all of the ship’s squares have been hit and if so sets the sunk property to true.
     * 
     * @param   array of shots that have been made, number of shots
     * @return  none
     */
    protected void checkIfSunk(Shot[] shots, int noOfShots)
    {        
        // local variables
        int squareRow;
        int squareCol;
        int shotRow;
        int shotCol;
        boolean hit = false;
        boolean tempSunk = true;
        
        // for each square
        int i = 0;
        while (i < occupiedSquares.length && tempSunk && !sunk)
        // while tempSunk is true because there is no point checking more squares once one is not hit
        // while sunk is false because there is no point checking a ship we already know is sunk
        {
            // get position
            squareRow = occupiedSquares[i].getRow();
            squareCol = occupiedSquares[i].getColumn();
            
            hit = false;
            
            // for each shot
            int j = 0;
            while (j < noOfShots && !hit) // There is no point checking other shots once a hit is found
            {
                // get position
                shotRow = shots[j].getRow();
                shotCol = shots[j].getColumn();
                
                // if position of shot = position of squaure
                if (shotRow == squareRow && shotCol == squareCol)
                {
                    // square is hit
                    hit = true;
                }
                
                j++;
            }
            
            // if the square is not hit
            if (!hit)
            {
                // the ship is not sunk
                tempSunk = false;
            }
            
            i++;
        }
        
        // If the ship was sunk this move (the old value of sunk is false but the new value (tempSunk) is true)
        if (!sunk && tempSunk)
        {
            System.out.println("You sunk a " + name + "!");
        }
        
        sunk = tempSunk;
    } 
    
    /**
     * setValidPosition
     * 
     * Chooses a random position on the grid for the boat to occupy and checks to make sure no other ships are already there.
     * 
     * @param   grid
     * @return  none
     */
    protected void setValidPosition(Grid grid)
    {
        // Create the random number generator
        Random numberGenerator = new Random();
        // The row of the ship
        int row = 0;
        // The column
        int col = 0;
        // Its rotation
        int rotation = 0;
        // validPosition must be set to false to enter loop
        boolean validPosition = false;
        
        while (!validPosition)
        {
            // reset validPosition to true
            validPosition = true;
            // Choose a random row and column
            row = numberGenerator.nextInt(10);
            col = numberGenerator.nextInt(10);
            // Choose a random rotation
            rotation = numberGenerator.nextInt(4);
            
            // Store the grid space at the position chosen above
            occupiedSquares[0] = grid.getGridSpace(row, col);
            // Now calculate all the other squares based on rotation
            switch(rotation)
            {
                case 0:     for (int i = 1; i < occupiedSquares.length; i++)
                            {   
                                // Check to make sure the grid space is on the board before trying to access it.
                                if (row-i >= 0) 
                                {
                                    occupiedSquares[i] = grid.getGridSpace(row - i, col);
                                }
                                else
                                {
                                    // If the grid space is not on the board, this is an invalid position for the ship.
                                    validPosition = false;
                                }
                            }
                            break;
                            
                case 1:     for (int i = 1; i < occupiedSquares.length; i++)
                            {
                                if (col+i <= 9)
                                {
                                    occupiedSquares[i] = grid.getGridSpace(row, col + i);
                                }
                                else
                                {
                                    validPosition = false;
                                }
                            }
                            break;
                            
                case 2:     for (int i = 1; i < occupiedSquares.length; i++)
                            {
                                if (row+i <= 9)
                                {
                                    occupiedSquares[i] = grid.getGridSpace(row + i, col);
                                }
                                else
                                {
                                    validPosition = false;
                                }
                            }
                            break;
                            
                case 3:     for (int i = 1; i < occupiedSquares.length; i++)
                            {
                                if (col-i >= 0)
                                {
                                    occupiedSquares[i] = grid.getGridSpace(row, col-i);
                                }
                                else
                                {
                                    validPosition = false;
                                }
                            }
                            break;
                            
                default:    System.out.println("Invalid rotation value.");
                            break;
            }
            
            // Check if any of the squares are already occupied by another ship
            int counter = 0;
            while (validPosition && counter < occupiedSquares.length) // There is no point in running this if the position is already known to be invalid
            {
                if ( occupiedSquares[counter].isOccupied() )
                {
                    // As soon as one square is occupied, there is no point checking the others.
                    validPosition = false;
                }
                counter++;
            }
        }
        
        // The position is valid!
        // Update the occupied squares
        for (int i = 0; i < occupiedSquares.length; i++)
        {
            // They are now occupied by this ship
            occupiedSquares[i].setOccupied(true);
        }
    }
    
    /**
     * getName
     * 
     * Accessor method for name field
     * @param   none
     * @return  name
     */
    public String getName()
    {
        return name;
    }
}
