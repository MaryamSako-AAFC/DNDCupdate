#include "stdafx.h"
#include "CommandLine.h"

options_t getOptionsFromArguments(const std::vector<std::string>& args)
{
    options_t umap;
    for (int counter = 1; counter < args.size(); ++counter) {
        std::string a = args[counter];
        string b, key;
        bool hasNext = counter < args.size() - 1;
        bool isKey = ! a.empty() && a.front() == '-';

        if (isKey == true) {
            key = a.erase(0, 1);
        }
        if (hasNext == true) {
            b = args[counter + 1];
            if (b.substr(0, 1) != "-") {
                umap[key] = b;
                counter++;
            }
            else {
                umap[key] = "true";
            }

        }
        else {
            if (isKey) umap[key] = "true";
        }
    }

    return umap;
}

options_t getOptionsFromArguments(int argc, const char** argv)
{
    std::vector<std::string> args;
    //args.push_back("PROG_NAME");
    for (int i = 0; i < argc; ++i)
        args.push_back(argv[i]);

    return getOptionsFromArguments(args);
}


