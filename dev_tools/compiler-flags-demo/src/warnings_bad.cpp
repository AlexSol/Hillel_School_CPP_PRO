#include <cstdint>

enum class Mode
{
    Read,
    Write,
    Execute
};

int main()
{
    int value = 4;
    if (value > 0)
    {
        int value = 2;
        value += 1;
    }

    const double ratio = 3.7;
    const int narrowed = ratio;

    if (0.1f == 0.1f)
    {
        value += narrowed;
    }

    switch (Mode::Read)
    {
    case Mode::Read:
        value += 1;
        break;
    }

    if ((value > 0) && (value > 0))
    {
        value += 1;
    }

    return value;
}