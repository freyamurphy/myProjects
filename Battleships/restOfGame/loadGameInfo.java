package restOfGame;

import ships.*;


/**
 * loadGameInfo
 * 
 * Stores objects needed to load a game so they can both be returned
 *
 * @author Freya Murphy
 * @version 28-08-17
 */
public class loadGameInfo
{
    private Player player;
    private Fleet fleet;

    /**
     * Constructor for objects of class loadGameInfo
     * 
     * @param   player, fleet
     * @return  none
     */
    public loadGameInfo(Player newPlayer, Fleet newFleet)
    {
        player = newPlayer;
        fleet = newFleet;
        
        // Check which ships are sunk
        fleet.checkIfDestroyed(player.getShots(), player.getNoOfShots());
    }

    /**
     * getPlayer
     * 
     * Accessor method for player field
     * 
     * @param   none
     * @return  player
     */
    public Player getPlayer()
    {
        return player;
    }
    
    /**
     * getFleet
     * 
     * Accessor method for fleet field
     * 
     * @param   none
     * @retrun  fleet
     */
    public Fleet getFleet()
    {
        return fleet;
    }
}
