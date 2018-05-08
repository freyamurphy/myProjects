package restOfGame;

import ships.Ship;

/**
 * Grid
 * 
 * Displays a grid of squares
 *
 * @author Freya Murphy
 * @version 28-07-18
 */
public class Grid
{
    private GridSpace gridData[][]; // 2d array of squares
    private int rows; // The number of squares on a side of the grid
    private int cols;

    /**
     * Constructor for objects of class Grid
     * 
     * @param   number of rows and columns
     * @return  none
     */
    public Grid()
    {
        rows = 10;
        cols = 10;
        
        // A square is accessed using [row][column] indexing
        gridData = new GridSpace[rows][cols];
        // Initialise values in each GridSpace
        for (int r = 0; r < rows; r++)
        {
            for (int c = 0; c < cols; c++)
            {
                gridData[r][c] = new GridSpace(r, c);
            }
        }
    }
    
    /**
     * getRows;
     * 
     * Accessor method for rows field
     * 
     * @param   none
     * @return  number of rows
     */
    public int getRows()
    {
        return rows;
    }
    
    /**
     * getCols
     * 
     * Accessor method for cols field
     * 
     * @param   none
     * @return  number of columns
     */
    public int getCols()
    {
        return cols;
    }
    
    /**
     * getGridData
     * 
     * Returns the gridData 2d array
     * 
     * @param   none
     * @return  2d array of GridSpaces
     */
    public GridSpace[][] getGridData()
    {
        return gridData;
    }
    
    /**
     * getGridSpace
     * 
     * Returns the GridSpace object stored in a specified position of the gridData array
     * 
     * @param   row, column
     * @return  gridSpace
     */
    public GridSpace getGridSpace(int row, int col)
    {
        GridSpace gridSpace = gridData[row][col];
        return gridSpace;
    }
    
    /**
     * updateGridData
     * 
     * Checks the positions of ships and sets appropriate GridSpaces to occupied
     * 
     * @param   array of ships
     * @return  none
     */
    public void updateGridData(Ship[] ships)
    {
        GridSpace[] occupiedSquares;
        int row;
        int col;
        
        // Check the position of each ship in the array
        for (int i = 0; i < ships.length; i++)
        {
            // Get the grid spaces occupied by the ship
            occupiedSquares = ships[i].getOccupiedSquares();
            
            // For each grid space
            for (int j = 0; j < occupiedSquares.length; j++)
            {
                // Get the grid space's position
                row = occupiedSquares[j].getRow();
                col = occupiedSquares[j].getColumn();
                
                // Update this grid space to occupied
                gridData[row][col].setOccupied(true);
            }
        }
    }
    
    /**
     * display
     * 
     * Displays each grid square on the screen.
     * 
     * @param   array of shots the player has made
     * @return  none
     */
    public void display(Shot[] shots)
    {
        // First display the column headings
        System.out.println("   A B C D E F G H I J");
        
        // Display each row
        for (int r = 0; r < rows; r++)
        {
            // Display row number
            if (r == 9)
            {
                System.out.print(r+1);
            }
            else
            {
                // Add a space so columns line up
                System.out.print(" " + (r+1));
            }
            
            // Display each grid space in the row
            for (int c = 0; c < cols; c++)
            {
                System.out.print(" ");
                gridData[r][c].display(shots);
            }
            // New line for next row
            System.out.println();
        }
    }
}
