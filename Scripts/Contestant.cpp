#include "Contestant.h"
#include "wet1util.h"

Contestant::Contestant(const int contestantId, const int countryId, const Sport &sport, int strength, Country *country) : m_contestantId(contestantId),
                                                                                                                          m_countryId(countryId),
                                                                                                                          m_sport(sport),
                                                                                                                          m_strength(strength),
                                                                                                                          m_country(country),
                                                                                                                          m_tree(-1)
{
}
Contestant::~Contestant()
{
    m_country = nullptr;
}
Sport Contestant::getSport() const
{
    return this->m_sport;
}

int Contestant::getId() const
{
    return this->m_contestantId;
}

int Contestant::getCountryId() const
{
    return this->m_countryId;
}

int Contestant::getStrength() const
{
    return this->m_strength;
}

bool Contestant::teamFull() const
{
    bool full = true;
    for (int i = 0; i < MAX_NUM_OF_TEAMS; i++)
    {
        if (this->m_teams[i] == 0)
        {
            full = false;
        }
    }
    return full;
}

void Contestant::addToTeam(const int teamId)
{
    for (int i = 0; i < MAX_NUM_OF_TEAMS; i++)
    {
        if (this->m_teams[i] == teamId)
        {
            return;
        }
    }
    for (int i = 0; i < MAX_NUM_OF_TEAMS; i++)
    {
        if (this->m_teams[i] == 0)
        {
            this->m_teams[i] = teamId;
            return;
        }
    }
}

void Contestant::removeTeam(const int teamId)
{
    for (int i = 0; i < MAX_NUM_OF_TEAMS; i++)
    {
        if (this->m_teams[i] == teamId)
        {
            this->m_teams[i] = 0;
            return;
        }
    }
}

void Contestant::updateStrength(const int change)
{
    this->m_strength = this->m_strength + change;
}

int *Contestant::getTeams()
{
    return m_teams;
}

Country *Contestant::getCountry()
{
    return this->m_country;
}

bool Contestant::partOfTeams() const
{
    for (int i = 0; i < MAX_NUM_OF_TEAMS; i++)
    {
        if (this->m_teams[i] != 0)
        {
            return true;
        }
    }
    return false;
}

bool Contestant::isInTeam(const int id) const
{
    for (int i = 0; i < MAX_NUM_OF_TEAMS; i++)
    {
        if (this->m_teams[i] == id)
        {
            return true;
        }
    }
    return false;
}

int Contestant::getTree() const
{
    return this->m_tree;
}

void Contestant::setTree(const int num)
{
    this->m_tree = num;
}