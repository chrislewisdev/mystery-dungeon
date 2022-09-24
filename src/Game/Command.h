#pragma once

class Character;

class Command {
    protected:
        Character& target;
        Command(Character& target) : target(target) {}
    public:
        virtual void apply() = 0;
};