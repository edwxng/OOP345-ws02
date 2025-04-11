#include "guild.h"
#include <iostream>

namespace seneca {

    Guild::Guild() : m_name("No guild"), m_members(nullptr), m_size(0) {}

    //constructor with name
    Guild::Guild(const char* name) : m_name(name), m_members(nullptr), m_size(0) {}

    Guild::~Guild() {
        delete[] m_members;
    }

    Guild::Guild(const Guild& other) : m_name(other.m_name), m_size(other.m_size) {
        m_members = new Character * [m_size];
        for (size_t i = 0; i < m_size; ++i) {
            m_members[i] = other.m_members[i];
        }
    }

    Guild& Guild::operator=(const Guild& other) {
        if (this != &other) {
            delete[] m_members;

            m_name = other.m_name;
            m_size = other.m_size;
            m_members = new Character * [m_size];
            for (size_t i = 0; i < m_size; ++i) {
                m_members[i] = other.m_members[i];
            }
        }
        return *this;
    }

    Guild::Guild(Guild&& other) noexcept : m_name(std::move(other.m_name)), m_members(other.m_members), m_size(other.m_size) {
        other.m_members = nullptr;
        other.m_size = 0;
    }

    Guild& Guild::operator=(Guild&& other) noexcept {
        if (this != &other) {
            delete[] m_members;

            m_name = std::move(other.m_name);
            m_members = other.m_members;
            m_size = other.m_size;

            other.m_members = nullptr;
            other.m_size = 0;
        }
        return *this;
    }

    //add member to the guild
    void Guild::addMember(Character* c) {
        //check duplicate
        for (size_t i = 0; i < m_size; ++i) {
            if (m_members[i]->getName() == c->getName()) {
                return;  //already in guild...
            }
        }

        //increase hp by 300
        c->setHealthMax(c->getHealthMax() + 300);
        c->setHealth(c->getHealthMax());

        //add
        Character** temp = new Character * [m_size + 1];
        for (size_t i = 0; i < m_size; ++i) {
            temp[i] = m_members[i];
        }
        temp[m_size] = c;
        delete[] m_members;
        m_members = temp;
        ++m_size;
    }

    //remove
    void Guild::removeMember(const std::string& c) {
        for (size_t i = 0; i < m_size; ++i) {
            if (m_members[i]->getName() == c) {
                m_members[i]->setHealthMax(m_members[i]->getHealthMax() - 300);
                if (m_members[i]->getHealth() > m_members[i]->getHealthMax()) {
                    m_members[i]->setHealth(m_members[i]->getHealthMax());
                }
                for (size_t j = i; j < m_size - 1; ++j) {
                    m_members[j] = m_members[j + 1];
                }
                --m_size;
                return;
            }
        }
    }
    
    //access operator
    Character* Guild::operator[](size_t idx) const {
        return (idx < m_size) ? m_members[idx] : nullptr;
    }

    //show function
    void Guild::showMembers() const {
        if (m_size == 0) {
            std::cout << "No guild." << std::endl;
        }
        else {
            std::cout << "[Guild] " << m_name << std::endl;
            for (size_t i = 0; i < m_size; ++i) {
                std::cout << "    " << i + 1 << ": " << *m_members[i] << std::endl;
            }
        }
    }

}
