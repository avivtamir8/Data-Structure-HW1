#ifndef HW1_CONTESTANT_H
#define HW1_CONTESTANT_H
#include "wet1util.h"
#include "Country.h"

class Contestant
{

private:
    int m_contestantId;
    int m_countryId;
    Sport m_sport;
    int m_strength;
    int m_teams[3] = {0};
    Country *m_country;
    int m_tree;
    

public:
    static const int MAX_NUM_OF_TEAMS = 3;
    /*
     * constructor for Contestant
     * @param - the contestant's id
     * @param - the contestant's country's id
     * @param - the contestant's sport
     * @param - the contestant's strength
     * @param - a pointer to the contestant's country
     * @return - a new instance of Contestant
     */
    Contestant(const int contestantId, const int countryId, const Sport &sport, int strength, Country *country);
    /*
     * Destructor of Contestant class
     * @param - none
     * @return - void
     */

    ~Contestant();
    /*
     * Assignment Operator of Contestant class
     * @param - The other Contestant
     * @return - An Contestant with the same data
     */
    Contestant &operator=(const Contestant &contestant) = default;

    /*
     * returns the contestant's sport
     * @param - none
     * @return - contestant's sport
     */
    Sport getSport() const;
    /*
     * returns the contestant's id
     * @param - none
     * @return - contestant's id
     */
    int getId() const;
    /*
     * returns the contestant's country's id
     * @param - none
     * @return - contestant's country's id
     */
    int getCountryId() const;
    /*
     * returns the contestant's strength
     * @param - none
     * @return - contestant's strength
     */
    int getStrength() const;
    /*
     * checks if the contestant is a part of three teams
     * @param - none
     * @return - true if the contestant is a part of three teams and false otherwise
     */
    bool teamFull() const;
    /*
     * adds the given team id to the contestant's teams
     * @param - the teams id
     * @return - void
     */
    void addToTeam(const int teamId);

    /*
     * removes the given team id from the contestant's teams
     * @param - the teams id
     * @return - void
     */
    void removeTeam(const int teamId);
    /*
     * adds the given change to the contestant's strength
     * @param - the change in the contestant's strength
     * @return - void
     */
    void updateStrength(const int change);
    /*
     * returns the ids of the contestant's teams
     * @param - none
     * @return - returns the ids of the contestant's teams
     */
    int *getTeams();
    /*
     * returns the pointer to the contestant's country
     * @param - none
     * @return - pointer to the contestant's country
     */
    Country *getCountry();
    /*
     * returns wether the contestant is a part of any team
     * @param - none
     * @return - true if the contestant is a part of at least one team false otherwise
     */
    bool partOfTeams() const;
    /*
     * checks if the contestant is a part of the given team
     * @param - teams id
     * @return - true if the contestant is a part of the team false otherwise
     */
    bool isInTeam(const int id) const;
    /*
     * returns the number of the tree the contestant is in
     * @param - none
     * @return - number of the tree the contestant is in
     */
    int getTree() const;
    /*
     * sets the number of the tree the contestant is in
     * @param - number of the tree the contestant is in
     * @return - void
     */
    void setTree(const int num);
};

#endif
