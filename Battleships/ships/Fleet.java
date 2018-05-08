package ships;

import restOfGame.Grid;
import restOfGame.Shot;

/**
 * Fleet
 * 
 * Keeps track of all the computer's ships
 *
 * @author Freya Murphy
 * @version 29-07-17
 */
public class Fleet
{
    private Ship [] ships;
    private boolean destroyed;

    /**
     * Constructor for objects of class Fleet
     * 
     * @param   none
     * @return  none
     */
    public Fleet()
    {
        // There are 9 ships in the fleet.
        ships = new Ship [9];
        // Add 1 battleship to fleet;
        ships[0] = new Battleship();
        
        // Add 2 cruisers to fleet
        for (int i = 1; i < 3; i++)
        {
            ships[i] = new Cruiser();
        }
        // Add 3 destroyers to fleet
        for (int i = 3; i < 6; i++)
        {
            ships[i] = new Destroyer();
        }
        // Add 3 submarines to fleet
        for (int i = 6; i < 9; i++)
        {
            ships[i] = new Submarine();
        }
        
        
        // Start with no ships sunk
        destroyed = false;
    }
    
    /**
     * getShips
     * 
     * Accessor method for ships field
     * 
     * @param   none
     * @return  array of ships
     */
    public Ship[] getShips()
    {
        return ships;
    }
    
    /**
     * getShip
     * 
     * Returns the ship at a specified index of the ships array
     * 
     * @param   index
     * @return  ship
     */
    public Ship getShip(int index)
    {
        return ships[index];
    }
    
    /**
     * isDestroyed
     * 
     * Accessor method for destroyed field
     * 
     * @param   none
     * @return  true / false
     */
    public boolean isDestroyed()
    {
        return destroyed;
    }
    
    /**
     * checkIfDestroyed
     * 
     * Checks if all ships in the fleet have been sunk and updates the destroyed field accordingly
     * 
     * @param   array of shots that have been made, number of shots
     * @return  none
     */
    public void checkIfDestroyed(Shot[] shots, int noOfShots)
    {
        destroyed = true;
        
        for (int i = 0; i < ships.length; i++)
        {
            // Check if any ship was just sunk
            ships[i].checkIfSunk(shots, noOfShots);
        }
        
        int i = 0;
        while (i < ships.length && destroyed)
        {
            // If any ship is not sunk then the fleet is not destroyed
            if (!ships[i].isSunk())
            {
                destroyed = false;
            }
            
            i++;
        }
    }
    
    /**
     * placeShips
     * 
     * Randomly places ships on the grid and checks to make sure the layout is valid
     * 
     * @param   grid
     * @return  none
     */
    public void placeShips(Grid grid)
    {
        for (int i = 0; i < ships.length; i++)
        {
            ships[i].setValidPosition(grid);
        }
    }
}
