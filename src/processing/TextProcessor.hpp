#pragma once
#include <string>

namespace processing {
class TextProcessor {

public:
    TextProcessor() = delete;
    TextProcessor(const TextProcessor&) = delete;
    TextProcessor& operator= (const TextProcessor&) = delete;


    static std::string process(const std::string& input);
};
}