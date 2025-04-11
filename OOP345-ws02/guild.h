#ifndef SENECA_GUILD_H
#define SENECA_GUILD_H

#include "character.h"
#include <string>

namespace seneca {

    class Guild {
        std::string m_name;
        Character** m_members;
        size_t m_size;

    public:
        Guild();
        Guild(const char* name);
        Guild(const Guild& other);               // Copy Constructor
        Guild& operator=(const Guild& other);    // Copy Assignment Operator
        Guild(Guild&& other) noexcept;           // Move Constructor
        Guild& operator=(Guild&& other) noexcept; // Move Assignment Operator
        ~Guild();                               // Destructor

        void addMember(Character* c);
        void removeMember(const std::string& c);
        Character* operator[](size_t idx) const;
        void showMembers() const;
    };

}

#endif
