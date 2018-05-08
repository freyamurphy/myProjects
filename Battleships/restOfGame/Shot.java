package restOfGame;

/**
 * Shot
 * 
 * Keep track of a shot’s position on the grid and whether it is a hit or a miss.
 *
 * @author Freya Murphy
 * @version 23-07-17
 */
public class Shot
{
    // Position on grid
    private int row;
    private int column;
    
    // Hit or miss?
    private boolean hit;

    /**
     * Constructor for objects of class Shot
     * 
     * @param   row, column
     * @return  none
     */
    public Shot(int newRow, int newCol)
    {
        row = newRow;
        column = newCol;
        hit = false;
    }
    
    /**
     * Another constructor that also sets the value of hit
     * 
     * @param   row, column, hit
     * @return  none
     */
    public Shot(int newRow, int newCol, boolean newHit)
    {
        row = newRow;
        column = newCol;
        hit = newHit;
    }
    
    /**
     * getRow
     * 
     * Accessor method for row
     * 
     * @param   none
     * @return  row
     */
    public int getRow()
    {
        return row;
    }
    
    /**
     * getColumn
     * 
     * Accessor method for column
     * 
     * @param   none
     * @return  column
     */
    public int getColumn()
    {
        return column;
    }
    
    /**
     * isHit
     * 
     * Accessor method for hit field
     * 
     * @param   none
     * @return  hit
     */
    public boolean isHit()
    {
        return hit;
    }

    /**
     * checkForHit
     * 
     * Check if the position of the shot matches an occupied space on the grid. If it does set hit to true and otherwise set hit to false.
     * 
     * @param   grid (a 2d array)
     * @return  none
     */
    public void checkForHit( Grid grid )
    {
        // Extract the gridSpace that the shot is fired to
        GridSpace gridSpace = grid.getGridSpace(row, column);
        
        // Check if it is occupied
        boolean occupied = gridSpace.isOccupied();
        
        if ( occupied )
        {
            hit = true;
        }
        else
        {
            hit = false;
        }
    }
    
    /**
     * display
     * 
     * Displays the shot as an X on the grid
     * 
     * @param   none
     * @return  none
     */
    public void display()
    {
        if (hit)
        {
            // Display hits as an X
            System.out.print("X");
        }
        else
        {
            // Display misses as an O
            System.out.print("O");
        }
    }
}
