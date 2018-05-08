package restOfGame;

/**
 * GridSpace
 * 
 * Keep track of a square in a grid and check if there is a ship on that square
 *
 * @author Freya Murphy
 * @version 27-07-17
 */
public class GridSpace
{
    private int column;
    private int row;
    private boolean occupied;

    /**
     * Constructor for objects of class GridSpace
     * 
     * @param   x and y coordinated
     * @return  none
     */
    public GridSpace(int newRow, int newColumn)
    {
        row = newRow;
        column = newColumn;
        occupied = false;
    }
    
    /**
     * getRow
     * 
     * Accessor method for row field
     * 
     * @param   none
     * @return  row of square
     */
    public int getRow()
    {
        return row;
    }
    
    /**
     * getColumn
     * 
     * Accessor method for column field
     * 
     * @param   none
     * @return  column of square
     */
    public int getColumn()
    {
        return column;
    }
    
    /**
     * isOccupied
     * 
     * Accessor method for occupied field
     * 
     * @param   none
     * @return  occupied
     */
    public boolean isOccupied()
    {
        return occupied;
    }
    
    /**
     * setOccupied
     * 
     * Updates value of occupied to true or false
     * 
     * @param   newOccupied (true or false)
     * @return  none
     */
    public void setOccupied(boolean newOccupied)
    {
        occupied = newOccupied;
    }

    /**
     * Display
     * 
     * Displays the square on the screen
     * 
     * @param   array of shots
     * @return  none
     */
    public void display( Shot[] shots )
    {
        boolean shot = false;

        try
        {
            // Check each shot in the array to see if one is at this coordinate
            for (int i = 0; i < shots.length; i++)
            {
                // Check for a shot at this coordinate
                if (shots[i].getRow() == row && shots[i].getColumn() == column)
                {
                    shots[i].display();
                    shot = true;
                }
            }
        }
        catch (NullPointerException e)
        {
            // This error occurs if there are no shots in the array yet
        }
        
        if (!shot)
        {
            // If there were no shots on this square print - to represent a blank space.
            System.out.print("-");
        }
    }
}
