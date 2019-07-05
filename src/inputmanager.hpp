#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

enum Key {
    W, A, S, D
}

class InputManager
{
public:
    void processInputs();
    void registerInput(Key key, Command command);
}
#endif
