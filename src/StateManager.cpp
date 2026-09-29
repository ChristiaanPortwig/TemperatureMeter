#include "StateManager.h"

void StateManager::setNextState()
{
    StateManager::currState = getNextState();
}

enum State StateManager::getNextState()
{
    if (StateManager::currState == BOTH)
    {
        return TEMP;
    }
    else if (StateManager::currState == TEMP)
    {
        return HUM;
    }
    return BOTH;
}

String StateManager::getStateString()
{
    if (StateManager::currState == BOTH)
        return "BOTH";
    else if (StateManager::currState == TEMP)
        return "TEMP";
    return "HUM";
}

enum State StateManager::getState()
{
    return StateManager::currState;
}
