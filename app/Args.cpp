/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Args.cpp
*/

#include "Args.hpp"

#include <getopt.h>
#include <iostream>

Args::Args(int argc, char **argv) : _argc(argc), _argv(argv) {
    int option_index = 0;
    auto opts = _getoptOptions();
    for (int c = 0; (c = nextArg(opts.get(), &option_index)) != -1;) {
        switch (c) {
            case 'h':
                _help = true;
                break;
            case 'c':
                _config = optarg;
                break;
            case '?':
                std::cerr << "Unknown option " << optopt << std::endl;
                break;
            default:
                break;
        }
    }
}

std::unique_ptr<struct option[]> Args::_getoptOptions() {
    auto result = std::make_unique<struct option[]>(_options.size() + 1);
    for (std::size_t i = 0; i < _options.size(); ++i) {
        result[i] = {
            _options[i]._long.c_str(),
            _options[i]._has_arg,
            nullptr,
            _options[i]._short,
        };
    }
    return result;
}

int Args::nextArg(const struct option *opts, int *option_index) {
    auto short_opts = getShortOpts();
    return getopt_long(_argc, _argv, short_opts.c_str(), opts, option_index);
}

void Args::printHelp(std::ostream &stream) {
    stream << "Usage: raytracer [options]" << std::endl;
    for (const auto &opt : _options) {
        if (opt._short != 0) {
            stream << "  -" << opt._short << ", ";
        }
        if (!opt._long.empty()) {
            stream << "--" << opt._long;
        }
        if (opt._has_arg == required_argument) {
            stream << " <arg>";
        }
        stream << ": " << opt._desc << std::endl;
    }
}

constexpr std::string Args::getShortOpts() {
    std::string short_opts;
    for (const auto &opt : _options) {
        if (opt._short == 0) {
            continue;
        }
        short_opts += opt._short;
        if (opt._has_arg == required_argument) {
            short_opts += ':';
        }
    }
    return short_opts;
}

bool Args::getHelp() {
    return _help;
}

std::string Args::getConfig() {
    return _config;
}
