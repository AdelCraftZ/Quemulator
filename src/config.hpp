//
// Created by Adel on 2023-02-18.
//

#ifndef QUEMULATOR_CONFIG_HPP
#define QUEMULATOR_CONFIG_HPP

#if __cplusplus >= 202002L
#define CONSTEVAL consteval
#define CONSTEXPR20 constexpr
#elif __cplusplus >= 201703L
#define CONSTEVAL constexpr
#define CONSTEXPR20
#else
#error This project requires C++17 at least!
#endif

#endif //QUEMULATOR_CONFIG_HPP
