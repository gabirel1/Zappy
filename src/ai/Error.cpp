/*
** EPITECH PROJECT, 2021
** B-YEP-410-MPL-4-1-zappy-merzouk.rafik
** File description:
** Error
*/

#include "Error.hpp"

error::ErrorAI::ErrorAI(const std::string &message, const std::string &whe) noexcept: _message(message), _where(whe)
{
}

error::ErrorAI::~ErrorAI()
{
}

const char * error::ErrorAI::what() const noexcept
{
    return (_message.c_str());
}

const std::string &error::ErrorAI::where() const
{
    return (_where);
}