#include <iostream>
#include <vector>
#include <list>
#include <cstdlib>
#include <ctime>
#include "PatternTemplates.h"

using namespace std;

enum class InputStrategyEnum
{
    Click,
    Touch,
    Silent,
    None
};

class InputStrategy
{
public:
    virtual ~InputStrategy() {}
    virtual void Input() = 0;
};

class ClickInputStrategy : public InputStrategy
{
    void Input() override { cout << "Clicking keys..."; }
};

class TouchInputStrategy : public InputStrategy
{
    void Input() override { cout << "Touching keys..."; }
};

class SilentInputStrategy : public InputStrategy
{
    void Input() override { cout << "Typing silently..."; }
};

InputStrategy* CreateInputStrategy(InputStrategyEnum type)
{
    switch(type)
    {
        case InputStrategyEnum::Click: return new ClickInputStrategy;
        case InputStrategyEnum::Touch: return new TouchInputStrategy;
        case InputStrategyEnum::Silent: return new SilentInputStrategy;
        default: return nullptr;
    }
}

enum class KeyboardType
{
    Mechanical,
    Membrane,
    Optical,
    Unknown
};

class Keyboard
{
private:
    InputStrategy* Strategy;
    bool IsFunctional;

    void UseWithStrategy()
    {
        if (Strategy) Strategy->Input();
        else cout << "No input method defined!";
    }

    void Diagnose()
    {
        if (IsFunctional) cout << "Working";
        else cout << "Broken";
    }

protected:
    virtual void Prepare() = 0;

public:
    Keyboard() : Strategy(nullptr)
    {
        IsFunctional = static_cast<bool>(rand() % 2);
    }

    virtual ~Keyboard()
    {
        if (Strategy) delete Strategy;
    }

    void SetInputStrategy(InputStrategy* newStrategy) { Strategy = newStrategy; }

    void Use()
    {
        PrintType();
        cout << " : ";
        Diagnose();
        cout << " : ";
        Prepare();
        cout << " : ";
        UseWithStrategy();
        cout << endl;
    }

    virtual void PrintType() = 0;
    virtual void Smell() = 0;
};

class MechanicalKeyboard : public Keyboard
{
public:
    MechanicalKeyboard()
    {
        SetInputStrategy(CreateInputStrategy(InputStrategyEnum::Click));
    }

    void PrintType() override { cout << "Mechanical Keyboard"; }
    void Prepare() override { cout << "Lubricate switches"; }
    void Smell() override { cout << "Smells like metal and plastic."; }
};

class MembraneKeyboard : public Keyboard
{
public:
    MembraneKeyboard()
    {
        SetInputStrategy(CreateInputStrategy(InputStrategyEnum::Silent));
    }

    void PrintType() override { cout << "Membrane Keyboard"; }
    void Prepare() override { cout << "Check rubber domes"; }
    void Smell() override { cout << "Smells like rubber."; }
};

class OpticalKeyboard : public Keyboard
{
public:
    OpticalKeyboard()
    {
        SetInputStrategy(CreateInputStrategy(InputStrategyEnum::Touch));
    }

    void PrintType() override { cout << "Optical Keyboard"; }
    void Prepare() override { cout << "Test infrared sensors"; }
    void Smell() override { cout << "Smells like innovation."; }
};

Keyboard* CreateKeyboard(KeyboardType type)
{
    switch (type)
    {
        case KeyboardType::Mechanical: return new MechanicalKeyboard;
        case KeyboardType::Membrane: return new MembraneKeyboard;
        case KeyboardType::Optical: return new OpticalKeyboard;
        default: return nullptr;
    }
}

void UseAll(Iterator<Keyboard*>* it)
{
    for(it->First(); !it->IsDone(); it->Next())
    {
        it->GetCurrent()->Use();
    }
}

int main()
{
    srand(time(0));

    ArrayClass<Keyboard*> keyboardArray;
    for (size_t i = 0; i < 10; ++i)
    {
        int k = rand() % 3;
        keyboardArray.Add(CreateKeyboard(static_cast<KeyboardType>(k)));
    }

    cout << "Using all keyboards:" << endl;
    UseAll(keyboardArray.GetIterator());

    return 0;
}
