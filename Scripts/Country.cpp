#include "Country.h"
#include "wet1util.h"

Country::Country(const int country_id, int medals):
    m_countryId(country_id),
    m_medals(medals),
    m_activeTeams(STARTING_ACTIVE_TEAMS),
    m_activePlayers(STARTING_ACTIVE_PLAYERS)
    {}

int Country::getMedals() const
{
    return this->m_medals;
}

int Country::getNumOfTeams() const
{
    return this->m_activeTeams;
}

int Country::getNumOfContestants() const
{
    return this->m_activePlayers;
}

void Country::updateNumOfTeams(const int change) 
{
    this->m_activeTeams+=change;
}

void Country::updateNumOfContestants(const int change)
{
    this->m_activePlayers+=change;
}

void Country::updateNumOfMedals (const int medals)
{
    this->m_medals+=medals;
}

bool Country::isInTeam(const int id) const
{
    return false;
}

int Country::getTree() const
{
    return -1;
}