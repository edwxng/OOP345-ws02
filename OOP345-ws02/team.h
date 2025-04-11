#ifndef SENECA_TEAM_H
#define SENECA_TEAM_H

#include "character.h"
#include <string>

namespace seneca {

    class Team {
        std::string m_name;
        Character** m_members;
        size_t m_size;

    public:
        Team();
        Team(const char* name);
        Team(const Team& other);               // Copy Constructor
        Team& operator=(const Team& other);    // Copy Assignment Operator
        Team(Team&& other) noexcept;           // Move Constructor
        Team& operator=(Team&& other) noexcept; // Move Assignment Operator
        ~Team();                               // Destructor

        void addMember(const Character* c);
        void removeMember(const std::string& c);
        Character* operator[](size_t idx) const;
        void showMembers() const;
    };

}

#endif

