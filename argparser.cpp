#include "argparser.h"

#include <iostream>
#include <boost/program_options.hpp>

// shorthand for namespace.
namespace po = boost::program_options;

ArgParser::ArgParser()
{
    // Nothing to do here.
}

int ArgParser::parse(int argc, char** argv)
{
    // Initalise our variables first.
    po::options_description desc("Allowed options");
    po::positional_options_description pos;
    po::variables_map vm;

    // Odd Boost-specific syntax
    desc.add_options()("help,h", "Prints this help message");
    pos.add("STN", 1);

    po::store(po::command_line_parser(argc, argv).options(desc).positional(pos).run(), vm);
    po::notify(vm);

    if (vm.count("help")) {

        return 1;
    }
    return 0;
}
