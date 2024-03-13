#ifndef HW1_COUNTRY_H
#define HW1_COUNTRY_H
#include "wet1util.h"

class Country
{

private:
    static const int STARTING_ACTIVE_TEAMS = 0;
    static const int STARTING_ACTIVE_PLAYERS = 0;

    int m_countryId;
    int m_medals;
    int m_activeTeams = 0;
    int m_activePlayers = 0;

public:
    /*
     * constructor for Contestant
     * @param - the country's id
     * @param - the countrys medals
     * @return - a new instance of Country
     */
    Country(const int country_id, int medals);
    /*
     * Destructor of Country class
     * @param - none
     * @return - void
     */
    ~Country() = default;
    /*
     * Assignment Operator of Country class
     * @param - The other Country
     * @return - An instance of Country with the same data
     */
    Country &operator=(const Country &country) = default;
    /*
     * returns the country's medals
     * @param - none
     * @return - country's medals
     */
    int getMedals() const;
    /*
     * returns the number of teams in the country
     * @param - none
     * @return - number of teams in the country
     */
    int getNumOfTeams() const;
    /*
     * returns the number of contestants in the country
     * @param - none
     * @return - number of contestants in the country
     */
    int getNumOfContestants() const;
    /*
     * updates the number of teams in the country by a given change
     * @param - the change given
     * @return - void
     */
    void updateNumOfTeams(const int change);
    /*
     * updates the number of contestants in the country by a given change
     * @param - the change given
     * @return - void
     */
    void updateNumOfContestants(const int change);
    /*
     * updates the number of medals in the country by a given change
     * @param - the change given
     * @return - void
     */
    void updateNumOfMedals(const int medals);
    /*
     * always return false function required for implementation
     * @param - none
     * @return - false
     */
    bool isInTeam(const int id) const;

    /*
     * always return -1 function required for implementation
     * @param - none
     * @return - -1
     */
    int getTree() const;
    /*
     * required for implementation
     * @param - number of the tree the contestant is in
     * @return - void
     */
    void setTree(const int num){};
};

#endif
