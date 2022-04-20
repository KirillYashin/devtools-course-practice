// Copyright 2022 Yashin Kirill

#include <sstream>
#include <iterator>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

#include "include/prime_numbers_application.h"

std::string PrimeNumbersApplication::getHelp(const std::string& appname) {
        return  "This is an application for finding prime numbers in range\n" \
        "Format for arguments:\n" +
        appname + " <left_border> <right_border> "
        "Where all arguments are positive integer more than 1." +
        "First argument must be less than second.";
}

std::string PrimeNumbersApplication::operator()(int argc, const char** argv) {
    int a, b;

    if (argc == 1)
        return getHelp(argv[0]);

    try {
        if (argc != 3)
            throw std::runtime_error("Error occured: Should be 2 arguments.\n");
        a = parseArgument(argv[1]);
        b = parseArgument(argv[2]);
        if (a <= 1 || b <= 1 || b < a)
            throw std::runtime_error("Error occured: Wrong argument format.\n");
    }
    catch (std::exception& exp) {
        return exp.what();
    }

    std::ostringstream oss;
    std::vector<int> prime = PrimeNumbers::getPrimeNumbers(a, b);
    if (!prime.empty()) {
        std::copy(prime.begin(), prime.end() - 1,
            std::ostream_iterator<int>(oss, " "));
        oss << prime.back();
    }
    return oss.str();
}

bool PrimeNumbersApplication::checkArgument(const std::string& str) {
    for (size_t i = 0; i < str.size(); i++) {
        if (str[i] < '0' || str[i] > '9')
            return false;
    }
    return true;
}

int PrimeNumbersApplication::parseArgument(const char* arg) {
    if (!checkArgument(arg))
        throw std::runtime_error("Error occured: Wrong argument format.\n");
    return std::stoi(arg);
}
