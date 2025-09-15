#include "counter.h"

Counter::Counter() : value(1) {}

Counter::Counter(int initialValue) : value(initialValue) {}

void Counter::increment()
{
    value++;
}

void Counter::decrement()
{
    value--;
}

int Counter::getValue() const
{
    return value;
}