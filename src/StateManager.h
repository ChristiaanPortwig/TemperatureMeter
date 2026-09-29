#include <Arduino.h>

enum State
{
    BOTH,
    TEMP,
    HUM
};

class StateManager
{
public:
    enum State currState = BOTH;
    void setNextState();
    enum State getNextState();
    enum State getState();
    String getStateString();
};
