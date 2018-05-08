package ships;
import restOfGame.GridSpace;

/**
 * Cruiser
 * 
 * A type of Ship
 *
 * @author Freya Murphy
 * @version 15-07-17
 */
public class Cruiser extends Ship
{
    /**
     * Constructor for objects of class Cruiser
     * 
     * @param   none
     * @return  none
     */
    public Cruiser()
    {
        super();
        size = 3;
        
        occupiedSquares = new GridSpace[size];
    }
}
