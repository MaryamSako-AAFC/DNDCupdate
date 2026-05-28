#pragma once
#include <string>
#include <unordered_map>

using namespace std;

using options_t = unordered_map<string, string>;

options_t getOptionsFromArguments(int argc, const char** argv);
