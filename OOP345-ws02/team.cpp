#include "team.h"
#include <iostream>
#include <cstring>

namespace seneca {

    Team::Team() : m_name("No team"), m_members(nullptr), m_size(0) {}

    //constructor with name
    Team::Team(const char* name) : m_name(name), m_members(nullptr), m_size(0) {}

    Team::~Team() {
        for (size_t i = 0; i < m_size; ++i) {
            delete m_members[i];
        }
        delete[] m_members;
    }

    Team::Team(const Team& other) : m_name(other.m_name), m_size(other.m_size) {
        m_members = new Character * [m_size];
        for (size_t i = 0; i < m_size; ++i) {
            m_members[i] = other.m_members[i]->clone();
        }
    }

    Team& Team::operator=(const Team& other) {
        if (this != &other) {
            for (size_t i = 0; i < m_size; ++i) {
                delete m_members[i];
            }
            delete[] m_members;

            m_name = other.m_name;
            m_size = other.m_size;
            m_members = new Character * [m_size];
            for (size_t i = 0; i < m_size; ++i) {
                m_members[i] = other.m_members[i]->clone();
            }
        }
        return *this;
    }

    Team::Team(Team&& other) noexcept : m_name(std::move(other.m_name)), m_members(other.m_members), m_size(other.m_size) {
        other.m_members = nullptr;
        other.m_size = 0;
    }

    Team& Team::operator=(Team&& other) noexcept {
        if (this != &other) {
            for (size_t i = 0; i < m_size; ++i) {
                delete m_members[i];
            }
            delete[] m_members;

            m_name = std::move(other.m_name);
            m_members = other.m_members;
            m_size = other.m_size;

            other.m_members = nullptr;
            other.m_size = 0;
        }
        return *this;
    }
    //add member
    void Team::addMember(const Character* c) {
        //check duplicate
        for (size_t i = 0; i < m_size; ++i) {
            if (m_members[i]->getName() == c->getName()) {
                return;  //character already in team
            }
        }

        //create a copy and adding to arr
        Character** temp = new Character * [m_size + 1];
        for (size_t i = 0; i < m_size; ++i) {
            temp[i] = m_members[i];
        }
        temp[m_size] = c->clone();
        delete[] m_members;
        m_members = temp;
        ++m_size;
    }

    //remove
    void Team::removeMember(const std::string& c) {
        for (size_t i = 0; i < m_size; ++i) {
            if (m_members[i]->getName() == c) {
                delete m_members[i];
                for (size_t j = i; j < m_size - 1; ++j) {
                    m_members[j] = m_members[j + 1];
                }
                --m_size;
                return;
            }
        }
    }

    //access operator
    Character* Team::operator[](size_t idx) const {
        return (idx < m_size) ? m_members[idx] : nullptr;
    }

    //show function
    void Team::showMembers() const {
        if (m_size == 0) {
            std::cout << "No team." << std::endl;
        }
        else {
            std::cout << "[Team] " << m_name << std::endl;
            for (size_t i = 0; i < m_size; ++i) {
                std::cout << "    " << i + 1 << ": " << *m_members[i] << std::endl;
            }
        }
    }

}
