#include "Olympicsa1.h"

Olympics::Olympics() :  m_numOfPlayers(0), m_numOfTeams(0), m_numOfCountry(0), m_countries(), m_teams(), m_contestants()
{}


Olympics::~Olympics()
{
	if (m_numOfPlayers > 0)
	{
		m_contestants.eraseData();
	}
	if (m_numOfTeams > 0)
	{
		m_teams.eraseData();
	}
	if (m_numOfCountry > 0)
	{
		m_countries.eraseData();
	}
}


StatusType Olympics::add_country(int countryId, int medals)
{
	if (countryId <= 0 || medals < 0)
	{
		return StatusType::INVALID_INPUT;
	}
	Country *country;
	try
	{
		country = new Country(countryId, medals);
		if (!m_countries.insert(country, countryId, countryId))
		{
			delete (country);
			return StatusType::FAILURE;
		}
	}
	catch (const std::exception &e)
	{
		return StatusType::ALLOCATION_ERROR;
	}
	m_numOfCountry++;
	return StatusType::SUCCESS;
}


StatusType Olympics::remove_country(int countryId)
{
	if (countryId <= 0)
	{
		return StatusType::INVALID_INPUT;
	}
	Country *country;
	try
	{
		country = (m_countries.find(countryId, countryId));
	}
	catch (...)
	{
		return StatusType::FAILURE;
	}
	if (country->getNumOfTeams() != 0 || country->getNumOfContestants() != 0)
	{
		return StatusType::FAILURE;
	}
	try
	{
		if (!m_countries.remove(countryId, countryId))
		{
			return StatusType::FAILURE;
		}
	}
	catch (...)
	{
		return StatusType::ALLOCATION_ERROR;
	}
	try
	{
		delete country;
	}
	catch (const std::exception &e)
	{
		return StatusType::FAILURE;
	}
	m_numOfCountry--;
	return StatusType::SUCCESS;
}


StatusType Olympics::add_team(int teamId, int countryId, Sport sport)
{
	if (countryId <= 0 || teamId <= 0)
	{
		return StatusType::INVALID_INPUT;
	}
	Country *country;
	try
	{
		country = (m_countries.find(countryId, countryId));
	}
	catch (...)
	{
		return StatusType::FAILURE;
	}
	Team *team;
	try
	{
		team = new Team(teamId, countryId, sport, country);
		if (!m_teams.insert(team, teamId, teamId))
		{
			delete (team);
			return StatusType::FAILURE;
		}
	}
	catch (...)
	{
		return StatusType::ALLOCATION_ERROR;
	}
	country->updateNumOfTeams(1);
	m_numOfTeams++;
	return StatusType::SUCCESS;
}


StatusType Olympics::remove_team(int teamId)
{
	if (teamId <= 0)
	{
		return StatusType::INVALID_INPUT;
	}
	Team *team;
	try
	{
		team = (m_teams.find(teamId, teamId));
	}
	catch (...)
	{
		return StatusType::FAILURE;
	}
	if (team->hasPlayers())
	{
		return StatusType::FAILURE;
	}
	try
	{
		if (!m_teams.remove(teamId, teamId))
		{
			return StatusType::FAILURE;
		}
	}
	catch (...)
	{
		return StatusType::ALLOCATION_ERROR;
	}
	(team->getCountry())->updateNumOfTeams(-1);
	try
	{
		delete (team);
	}
	catch (const std::exception &e)
	{
		return StatusType::ALLOCATION_ERROR;
	}
	m_numOfTeams--;
	return StatusType::SUCCESS;
}


StatusType Olympics::add_contestant(int contestantId, int countryId, Sport sport, int strength)
{
	if (countryId <= 0 || contestantId <= 0 || strength < 0)
	{
		return StatusType::INVALID_INPUT;
	}
	Country *country;
	try
	{
		country = (m_countries.find(countryId, countryId));
	}
	catch (...)
	{
		return StatusType::FAILURE;
	}
	Contestant *contestant;
	try
	{
		contestant = new Contestant(contestantId, countryId, sport, strength, country);
		if (!m_contestants.insert(contestant, contestantId, contestantId))
		{
			delete (contestant);
			return StatusType::FAILURE;
		}
	}
	catch (...)
	{
		return StatusType::ALLOCATION_ERROR;
	}
	country->updateNumOfContestants(1);
	m_numOfPlayers++;
	return StatusType::SUCCESS;
}


StatusType Olympics::remove_contestant(int contestantId)
{
	if (contestantId <= 0)
	{
		return StatusType::INVALID_INPUT;
	}
	Contestant *contestant;
	try
	{
		contestant = (m_contestants.find(contestantId, contestantId));
	}
	catch (...)
	{
		return StatusType::FAILURE;
	}
	if (contestant->partOfTeams())
	{
		return StatusType::FAILURE;
	}
	try
	{
		if (!m_contestants.remove(contestantId, contestantId))
		{
			return StatusType::FAILURE;
		}
	}
	catch (...)
	{
		return StatusType::ALLOCATION_ERROR;
	}
	(contestant->getCountry())->updateNumOfContestants(-1);
	delete (contestant);
	m_numOfPlayers--;
	return StatusType::SUCCESS;
}


StatusType Olympics::add_contestant_to_team(int teamId, int contestantId)
{
	if (contestantId <= 0 || teamId <= 0)
	{
		return StatusType::INVALID_INPUT;
	}
	Contestant *contestant;
	try
	{
		contestant = (m_contestants.find(contestantId, contestantId));
	}
	catch (...)
	{
		return StatusType::FAILURE;
	}
	if (contestant->teamFull())
	{
		return StatusType::FAILURE;
	}
	Team *team;
	try
	{
		team = (m_teams.find(teamId, teamId));
	}
	catch (...)
	{
		return StatusType::FAILURE;
	}
	if (contestant->getSport() != team->getSport() || contestant->getCountryId() != team->getCountryId())
	{
		return StatusType::FAILURE;
	}
	AVLTree<Contestant *> *toEnterId, *toEnterStrength;
	int firstMax = 0, secondMax = 0;
	try
	{
		firstMax = team->getFirstMaxId();
		secondMax = team->getSecondMaxId();
		if (contestantId <= firstMax)
		{
			toEnterId = team->getFirstThirdId();
			toEnterStrength = team->getFirstThirdStrength();
		}
		else if (contestantId <= secondMax)
		{
			toEnterId = team->getSecondThirdId();
			toEnterStrength = team->getSecondThirdStrength();
		}
		else
		{
			toEnterId = team->getThirdThirdId();
			toEnterStrength = team->getThirdThirdStrength();
		}
	}
	catch (const std::exception &e)
	{
		return StatusType::FAILURE;
	}
	try
	{
		if (!toEnterId->insert(contestant, contestant->getId(), contestant->getId()))
		{
			return StatusType::FAILURE;
		}
		if (!toEnterStrength->insert(contestant, contestant->getStrength(), contestant->getId()))
		{
			toEnterId->remove(contestant->getId(), contestant->getId());
			return StatusType::FAILURE;
		}
	}
	catch (...)
	{
		return StatusType::ALLOCATION_ERROR;
	}

	try
	{
		if (contestantId <= firstMax)
		{
			team->setFirstThirdNumber(team->getFirstThirdNumber() + 1);
			team->rebalanceTrees(Team::FIRST_TREE);
		}
		else if (contestantId <= secondMax)
		{
			team->setSecondThirdNumber(team->getSecondThirdNumber() + 1);
			team->rebalanceTrees(Team::SECOND_TREE);
		}
		else
		{
			team->setThirdThirdNumber(team->getThirdThirdNumber() + 1);
			team->rebalanceTrees(Team::THIRD_TREE);
		}
	}
	catch (const BadAllocation &e)
	{
		toEnterId->remove(contestant->getId(), contestant->getId());
		toEnterStrength->remove(contestant->getStrength(), contestant->getId());
		return StatusType::ALLOCATION_ERROR;
	}

	team->updateMaxAndMin();
	contestant->addToTeam(teamId);
	return StatusType::SUCCESS;
}


StatusType Olympics::remove_contestant_from_team(int teamId, int contestantId)
{
	if (contestantId <= 0 || teamId <= 0)
	{
		return StatusType::INVALID_INPUT;
	}
	Contestant *contestant;
	try
	{
		contestant = (m_contestants.find(contestantId, contestantId));
	}
	catch (...)
	{
		return StatusType::FAILURE;
	}
	Team *team;
	try
	{
		team = (m_teams.find(teamId, teamId));
	}
	catch (...)
	{
		return StatusType::FAILURE;
	}
	AVLTree<Contestant *> *toRemoveId, *toRemoveStrength;
	int firstMax, secondMax;
	try
	{
		firstMax = team->getFirstMaxId();
		secondMax = team->getSecondMaxId();
		if (contestantId <= firstMax)
		{
			toRemoveId = team->getFirstThirdId();
			toRemoveStrength = team->getFirstThirdStrength();
		}
		else if (contestantId <= secondMax)
		{
			toRemoveId = team->getSecondThirdId();
			toRemoveStrength = team->getSecondThirdStrength();
		}
		else
		{
			toRemoveId = team->getThirdThirdId();
			toRemoveStrength = team->getThirdThirdStrength();
		}
		if (!toRemoveId->remove(contestant->getId(), contestant->getId()))
		{
			return StatusType::FAILURE;
		}
		if (!toRemoveStrength->remove(contestant->getStrength(), contestant->getId()))
		{
			return StatusType::FAILURE;
		}
	}
	catch (...)
	{
		return StatusType::ALLOCATION_ERROR;
	}
	try
	{
		if (contestantId <= firstMax)
		{
			team->setFirstThirdNumber(team->getFirstThirdNumber() - 1);
			team->rebalanceTrees(Team::FIRST_TREE);
		}
		else if (contestantId <= secondMax)
		{
			team->setSecondThirdNumber(team->getSecondThirdNumber() - 1);
			team->rebalanceTrees(Team::SECOND_TREE);
		}
		else
		{
			team->setThirdThirdNumber(team->getThirdThirdNumber() - 1);
			team->rebalanceTrees(Team::THIRD_TREE);
		}
	}
	catch (const BadAllocation &e)
	{
		return StatusType::ALLOCATION_ERROR;
	}
	team->updateMaxAndMin();
	contestant->removeTeam(teamId);
	return StatusType::SUCCESS;
}


StatusType Olympics::update_contestant_strength(int contestantId, int change)
{
	if (contestantId <= 0)
	{
		return StatusType::INVALID_INPUT;
	}
	Contestant *contestant;
	try
	{
		contestant = (m_contestants.find(contestantId, contestantId));
	}
	catch (...)
	{
		return StatusType::FAILURE;
	}
	if (contestant->getStrength() + change < 0)
	{
		return StatusType::FAILURE;
	}
	int strength = contestant->getStrength();
	contestant->updateStrength(change);
	int *teams = contestant->getTeams();
	Team *team;
	for (int i = 0; i < Contestant::MAX_NUM_OF_TEAMS; i++)
	{
		try
		{
			if (teams[i] != 0)
			{
				team = (m_teams.find(teams[i], teams[i]));
				team->getFirstThirdStrength()->updateFirstCondition(strength, contestant->getId(), contestant->getStrength());
				team->getSecondThirdStrength()->updateFirstCondition(strength, contestant->getId(), contestant->getStrength());
				team->getThirdThirdStrength()->updateFirstCondition(strength, contestant->getId(), contestant->getStrength());
				team->updateMaxAndMin();
			}
		}
		catch (...)
		{
			return StatusType::FAILURE;
		}
		
	}
	return StatusType::SUCCESS;
}


output_t<int> Olympics::get_strength(int contestantId)
{
	if (contestantId <= 0)
	{
		return StatusType::INVALID_INPUT;
	}
	Contestant *contestant;
	try
	{
		contestant = (m_contestants.find(contestantId, contestantId));
	}
	catch (...)
	{
		return StatusType::FAILURE;
	}
	return contestant->getStrength();
}


output_t<int> Olympics::get_medals(int countryId)
{
	if (countryId <= 0)
	{
		return StatusType::INVALID_INPUT;
	}
	Country *country;
	try
	{
		country = (m_countries.find(countryId, countryId));
	}
	catch (...)
	{
		return StatusType::FAILURE;
	}
	return country->getMedals();
}


output_t<int> Olympics::get_team_strength(int teamId)
{
	if (teamId <= 0)
	{
		return StatusType::INVALID_INPUT;
	}
	Team *team;
	try
	{
		team = m_teams.find(teamId, teamId);
	}
	catch (...)
	{
		return StatusType::FAILURE;
	}
	if (team->getLength() % Team::MAX_NUM_OF_TEAMS != 0)
	{
		return 0;
	}
	return team->getFirstMax() + team->getSecondMax() + team->getThirdMax();
}


StatusType Olympics::unite_teams(int teamId1, int teamId2)
{
	if (teamId1 <= 0 || teamId2 <= 0 || teamId1 == teamId2)
	{
		return StatusType::INVALID_INPUT;
	}
	Team *team1;
	try
	{
		team1 = (m_teams.find(teamId1, teamId1));
	}
	catch (...)
	{
		return StatusType::FAILURE;
	}
	Team *team2;
	try
	{
		team2 = (m_teams.find(teamId2, teamId2));
	}
	catch (...)
	{
		return StatusType::FAILURE;
	}
	if (team1->getCountryId() != team2->getCountryId() || team1->getSport() != team2->getSport())
	{
		return StatusType::FAILURE;
	}
	StatusType status = team1->merge(team2);
	if (status == StatusType::SUCCESS)
	{
		return this->remove_team(teamId2);
	}
	return status;
}


StatusType Olympics::play_match(int teamId1, int teamId2)
{
	if ((teamId1 <= 0) || (teamId2 <= 0) || (teamId1 == teamId2))
	{
		return StatusType::INVALID_INPUT;
	}
	Team *team1;
	Team *team2;
	try
	{
		team2 = (m_teams.find(teamId2, teamId2));
		team1 = (m_teams.find(teamId1, teamId1));
	}
	catch (...)
	{
		return StatusType::FAILURE;
	}
	if (team1->getSport() != team2->getSport())
	{
		return StatusType::FAILURE;
	}
	else
	{
		int team1Medals = (team1->getCountry())->getMedals();
		int team2Medals = (team2->getCountry())->getMedals();
		int team1Strength = get_team_strength(teamId1).ans();
		int team2Strength = get_team_strength(teamId2).ans();
		int team1Score = team1Medals + team1Strength;
		int team2Score = team2Medals + team2Strength;
		if (team1Score > team2Score)
		{
			team1->getCountry()->updateNumOfMedals(1);
		}
		if (team1Score < team2Score)
		{
			team2->getCountry()->updateNumOfMedals(1);
		}
	}
	return StatusType::SUCCESS;
}


output_t<int> Olympics::austerity_measures(int teamId)
{
	if (teamId <= 0)
	{
		return StatusType::INVALID_INPUT;
	}
	Team *team;
	try
	{
		team = (m_teams.find(teamId, teamId));
	}
	catch (...)
	{
		return StatusType::FAILURE;
	}
	if (team->getLength() < Team::MAX_NUM_OF_TEAMS)
	{
		return StatusType::FAILURE;
	}
	int thirdsLength = team->getLength() / 3;
	int *maxAndMin = team->getMaxAndMin();
	int max = 0;
	int checker = 0;
	int *teamMax = team->getMaxes();
	if (thirdsLength == 1 || team->getLength() % Team::MAX_NUM_OF_TEAMS != 0)
	{
		return 0;
	}
	else if (thirdsLength == 2)
	{
		int max1 = searchForMax(teamMax, Team::NUM_OF_MAX, -1), max2 = searchForMax(teamMax, Team::NUM_OF_MAX, -2);
		int max3 = searchForMax(teamMax, Team::NUM_OF_MAX, -3);
		revert(teamMax, Team::NUM_OF_MAX, max1, max2, max3);
		return max1 + max2 + max3;
	}
	else
	{
		max = findMax(teamMax[MAX_FIRST_TREE], maxAndMin[B0_IN_SECOND_TREE], maxAndMin[B1_IN_SECOND_TREE]);
		if (maxAndMin[B0_IN_SECOND_TREE] == teamMax[MAX_SECOND_TREE] || maxAndMin[B1_IN_SECOND_TREE] == teamMax[MAX_SECOND_TREE])
		{
			if (maxAndMin[B1_IN_SECOND_TREE] == teamMax[SECOND_MAX_IN_SECOND_TREE] || maxAndMin[B0_IN_SECOND_TREE] == teamMax[SECOND_MAX_IN_SECOND_TREE])
			{
				max += findMax(teamMax[B0_IN_SECOND_TREE], maxAndMin[C0_IN_THIRD_TREE]);
			}
			else
			{
				max += findMax(teamMax[SECOND_MAX_IN_SECOND_TREE], maxAndMin[C0_IN_THIRD_TREE]);
			}
		}
		else
		{
			max += findMax(teamMax[MAX_SECOND_TREE], maxAndMin[C0_IN_THIRD_TREE]);
		}
		if (maxAndMin[C0_IN_THIRD_TREE] == teamMax[MAX_THIRD_TREE])
		{
			max += teamMax[SECOND_MAX_THIRD_TREE];
		}
		else
		{
			max += teamMax[MAX_THIRD_TREE];
		}
		checker = findMax(teamMax[MAX_FIRST_TREE], maxAndMin[B0_IN_SECOND_TREE]);
		if (maxAndMin[B0_IN_SECOND_TREE] == teamMax[MAX_SECOND_TREE])
		{
			checker += findMax(teamMax[SECOND_MAX_IN_SECOND_TREE], maxAndMin[C0_IN_THIRD_TREE]);
		}
		else
		{
			checker += findMax(teamMax[MAX_SECOND_TREE], maxAndMin[C0_IN_THIRD_TREE]);
		}
		if (maxAndMin[C0_IN_THIRD_TREE] == teamMax[MAX_THIRD_TREE])
		{
			checker += teamMax[SECOND_MAX_THIRD_TREE];
		}
		else
		{
			checker += teamMax[MAX_THIRD_TREE];
		}
		max = findMax(max, checker);
		checker = teamMax[MAX_FIRST_TREE] + findMax(teamMax[MAX_SECOND_TREE], maxAndMin[C0_IN_THIRD_TREE]);
		if (maxAndMin[C0_IN_THIRD_TREE] == teamMax[MAX_THIRD_TREE])
		{
			checker += teamMax[SECOND_MAX_THIRD_TREE];
		}
		else
		{
			checker += teamMax[MAX_THIRD_TREE];
		}
		max = findMax(max, checker);
		checker = findMax(teamMax[MAX_SECOND_TREE], maxAndMin[N2_IN_FIRST_TREE], maxAndMin[C0_IN_THIRD_TREE]);
		if (maxAndMin[N2_IN_FIRST_TREE] == teamMax[MAX_FIRST_TREE])
		{
			checker += teamMax[SECOND_MAX_FIRST_TREE];
		}
		else
		{
			checker += teamMax[MAX_FIRST_TREE];
		}
		if (maxAndMin[C0_IN_THIRD_TREE] == teamMax[MAX_THIRD_TREE])
		{
			checker += teamMax[SECOND_MAX_THIRD_TREE];
		}
		else
		{
			checker += teamMax[MAX_THIRD_TREE];
		}
		max = findMax(max, checker);
		checker = teamMax[MAX_THIRD_TREE] + findMax(teamMax[MAX_SECOND_TREE], maxAndMin[N2_IN_FIRST_TREE]);
		if (maxAndMin[N2_IN_FIRST_TREE] == teamMax[MAX_FIRST_TREE])
		{
			checker += teamMax[SECOND_MAX_FIRST_TREE];
		}
		else
		{
			checker += teamMax[MAX_FIRST_TREE];
		}
		max = findMax(max, checker);
		checker = findMax(maxAndMin[BN_SECOND_TREEE], teamMax[MAX_THIRD_TREE]);
		if (maxAndMin[BN_SECOND_TREEE] == teamMax[MAX_SECOND_TREE])
		{
			checker += findMax(teamMax[SECOND_MAX_IN_SECOND_TREE], maxAndMin[N2_IN_FIRST_TREE]);
		}
		else
		{
			checker += findMax(teamMax[MAX_SECOND_TREE], maxAndMin[N2_IN_FIRST_TREE]);
		}
		if (maxAndMin[N2_IN_FIRST_TREE] == teamMax[MAX_FIRST_TREE])
		{
			checker += teamMax[SECOND_MAX_FIRST_TREE];
		}
		else
		{
			checker += teamMax[MAX_FIRST_TREE];
		}
		max = findMax(max, checker);
		checker = findMax(teamMax[MAX_THIRD_TREE], maxAndMin[BN1_SECOND_TREE], maxAndMin[BN_SECOND_TREEE]);
		if (maxAndMin[BN_SECOND_TREEE] == teamMax[MAX_SECOND_TREE] || maxAndMin[BN1_SECOND_TREE] == teamMax[MAX_SECOND_TREE])
		{
			checker += findMax(teamMax[SECOND_MAX_IN_SECOND_TREE], maxAndMin[N2_IN_FIRST_TREE]);
		}
		else
		{
			checker += findMax(teamMax[MAX_SECOND_TREE], maxAndMin[N2_IN_FIRST_TREE]);
		}
		if (maxAndMin[N2_IN_FIRST_TREE] == teamMax[MAX_FIRST_TREE])
		{
			checker += teamMax[SECOND_MAX_FIRST_TREE];
		}
		else
		{
			checker += teamMax[MAX_FIRST_TREE];
		}
		max = findMax(max, checker);
		checker = findMax(teamMax[MAX_FIRST_TREE], maxAndMin[B0_IN_SECOND_TREE]) + teamMax[MAX_THIRD_TREE];
		if (maxAndMin[B0_IN_SECOND_TREE] == teamMax[MAX_SECOND_TREE])
		{
			checker += teamMax[SECOND_MAX_IN_SECOND_TREE];
		}
		else
		{
			checker += teamMax[MAX_SECOND_TREE];
		}
		max = findMax(max, checker);
		checker = findMax(teamMax[MAX_THIRD_TREE], maxAndMin[BN_SECOND_TREEE]) + teamMax[MAX_FIRST_TREE];
		if (maxAndMin[BN_SECOND_TREEE] == teamMax[MAX_SECOND_TREE])
		{
			checker += teamMax[SECOND_MAX_IN_SECOND_TREE];
		}
		else
		{
			checker += teamMax[MAX_SECOND_TREE];
		}
		max = findMax(max, checker, teamMax[MAX_FIRST_TREE] + teamMax[MAX_SECOND_TREE] + teamMax[MAX_THIRD_TREE]);
	}
	return max;
}


int Olympics::findMax(const int a, const int b, const int c) const
{
	return findMax(findMax(a, b), c);
}


int Olympics::findMax(const int a, const int b) const
{
	if (a >= b)
	{
		return a;
	}
	return b;
}


int Olympics::searchForMax(int *array, const int size, const int seperator)
{
	int max = array[0];
	int index = 0;
	for (int i = 1; i < size; i++)
	{
		if (max < array[i])
		{
			max = array[i];
			index = i;
		}
	}
	array[index] = seperator;
	return max;
}


void Olympics::revert(int *array, const int size, const int max1, const int max2, const int max3)
{
	for (int i = 0; i < size; i++)
	{
		if (array[i] == -1)
		{
			array[i] = max1;
		}
		if (array[i] == -2)
		{
			array[i] = max2;
		}
		if (array[i] == -3)
		{
			array[i] = max3;
		}
	}
}