/*
** EPITECH PROJECT, 2021
** B-YEP-410-MPL-4-1-zappy-merzouk.rafik
** File description:
** Error
*/

#ifndef ERROR_HPP_
#define ERROR_HPP_
#include <iostream>
#include <exception>

namespace error {
    class ErrorAI;
};

class error::ErrorAI : public std::exception {
    public:
        ErrorAI(const std::string &, const std::string &) noexcept;
        ~ErrorAI();

        const char *what() const noexcept override;
        const std::string &where() const;
    private:
        std::string _message;
        std::string _where;
};

#endif /* !ERROR_HPP_ */
