package ships;
import restOfGame.GridSpace;

/**
 * Destroyer
 * 
 * A type of Ship
 *
 * @author Freya Murphy
 * @version 26-07-17
 */
public class Destroyer extends Ship
{
    /**
     * Constructor for objects of class Destroyer
     * 
     * @param   none
     * @return  none
     */
    public Destroyer()
    {
        super();
        size = 2;
        
        occupiedSquares = new GridSpace[size];
    }
}
