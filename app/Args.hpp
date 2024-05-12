/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Args.hpp
*/

#pragma once

#include <getopt.h>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

struct Arg {
    std::string _long;
    char _short;
    int _has_arg;
    std::string _desc;
};

class Args {
   public:
    Args(int argc, char **argv);

    void printHelp(std::ostream &stream = std::cout);

    [[nodiscard]] bool getHelp();
    [[nodiscard]] const std::string &getConfig() const;
    [[nodiscard]] const std::string &getDisplay() const;
    [[nodiscard]] const std::string &getOutputFile() const;

   private:
    int _argc;
    char **_argv;

    bool _help = false;
    std::string _config = "scene.cfg";
    std::string _display = "ppm";
    std::string _output_file = "image.ppm";

    std::vector<Arg> _options = {
        {"help", 'h', no_argument, "show help"},
        {"config", 'c', required_argument, "specify config file (default is scene.cfg)"},
        {"display", 'd', required_argument, "specify display type (default is ppm)"},
        {"output", 'o', required_argument, "specify output file (default is image.ppm)"}
    };

    std::unique_ptr<struct option[]> _getoptOptions();
    constexpr std::string getShortOpts();
    int nextArg(const struct option *opts, int *option_index);
};
