package ships;
import restOfGame.GridSpace;

/**
 * Battleship
 * 
 * A type of ship
 *
 * @author Freya Murphy
 * @version 15-07-17
 */
public class Battleship extends Ship
{
    /**
     * Constructor for objects of class Battleship
     * 
     * @param   none
     * @return  none
     */
    public Battleship()
    {
        super();
        size = 4;
        
        occupiedSquares = new GridSpace[size];
    }
}
