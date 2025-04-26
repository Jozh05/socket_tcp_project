#include "TextProcessor.hpp"
#include <sstream>
#include <unordered_set>

namespace processing {
    std::string TextProcessor::process(const std::string& input) {
        std::istringstream iss(input);
        std::unordered_set<std::string> seen;
        std::ostringstream oss;
        std::string word;
        bool first = true;

        while (iss >> word) {
            if (seen.insert(word).second) {
                if (!first)
                    oss << ' ';
                oss << word;
                first = false;
            }
        }
        return oss.str();
    }
}