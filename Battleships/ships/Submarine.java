package ships;
import restOfGame.GridSpace;

/**
 * Submarine
 * 
 * A type of Ship
 *
 * @author Freya Murphy
 * @version 15-07-17
 */
public class Submarine extends Ship
{
    /**
     * Constructor for objects of class Submarine
     * 
     * @param   none
     * @return  none
     */
    public Submarine()
    {
        super();
        size = 1;
        
        occupiedSquares = new GridSpace[size];
    }
}
