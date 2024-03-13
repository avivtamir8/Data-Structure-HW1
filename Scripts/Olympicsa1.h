//
// 234218 Data Structures 1.
// Semester: 2024A (winter).
// Wet Exercise #1.
//
// Recommended TAB size to view this file: 8.
//
// The following header file contains all methods we expect you to implement.
// You MAY add private methods and fields of your own.
// DO NOT erase or modify the signatures of the public methods.
// DO NOT modify the preprocessors in this file.
// DO NOT use the preprocessors in your other code files.
//

#ifndef STREAMINGDBA1_H_
#define STREAMINGDBA1_H_

#include "wet1util.h"
#include "AVLTree.h"
#include "Country.h"
#include "Team.h"
#include "Contestant.h"

class Olympics
{
private:

    // Total number of players throughout the entire tournament
    int m_numOfPlayers;

    //Total number of teams throughout the entire tournament
    int m_numOfTeams;

    //Total number of countries in the tournament
    int m_numOfCountry;

    //Tree of pointers of the type country, with all the countries in the tournament sorted by their ID
    AVLTree<Country *> m_countries;

    //Tree of pointers of the type team, with all the teams in the tournament sorted by their ID
    AVLTree<Team *> m_teams;

    //Tree of pointers of the type contestant, with all the contestants in the tournament sorted by their ID
    AVLTree<Contestant *> m_contestants;

    /*
     * Helper functions for Olympics
     * findMax: returns the maximum of three numbers
     * findMax: returns the maximum of two numbers
     * searchForMax: finds the maximum in an array and sets it equal to a given separator
     * revert: returns the three maximum values in the array to their original values
    */
    int findMax(const int a, const int b, const int c) const;
    int findMax(const int a, const int b) const;
    int searchForMax(int *array, const int size, const int seperator);
    void revert(int *array, const int size, const int max1, const int max2, const int max3);

    static const int MAX_FIRST_TREE = 2;
    static const int B0_IN_SECOND_TREE = 3;
    static const int B1_IN_SECOND_TREE = 4;
    static const int MAX_SECOND_TREE = 5;
    static const int SECOND_MAX_IN_SECOND_TREE = 4;
    static const int C0_IN_THIRD_TREE = 9;
    static const int MAX_THIRD_TREE = 8;
    static const int SECOND_MAX_THIRD_TREE = 7;
    static const int N2_IN_FIRST_TREE = 2;
    static const int SECOND_MAX_FIRST_TREE = 1;
    static const int BN_SECOND_TREEE = 8;
    static const int BN1_SECOND_TREE = 7;
public:
    // <DO-NOT-MODIFY> {

    Olympics();

    virtual ~Olympics();

    StatusType add_country(int countryId, int medals);

    StatusType remove_country(int countryId);

    StatusType add_team(int teamId, int countryId, Sport sport);

    StatusType remove_team(int teamId);

    StatusType add_contestant(int contestantId, int countryId, Sport sport, int strength);

    StatusType remove_contestant(int contestantId);

    StatusType add_contestant_to_team(int teamId, int contestantId);

    StatusType remove_contestant_from_team(int teamId, int contestantId);

    StatusType update_contestant_strength(int contestantId, int change);

    output_t<int> get_strength(int contestantId);

    output_t<int> get_medals(int countryId);

    output_t<int> get_team_strength(int teamId);

    StatusType unite_teams(int teamId1, int teamId2);

    StatusType play_match(int teamId1, int teamId2);

    output_t<int> austerity_measures(int teamId);

    // } </DO-NOT-MODIFY>
};

#endif // STREAMINGDBA1_H_
