#ifndef MACHINELEARNINGMATHEX_GUTENBERG_H
#define MACHINELEARNINGMATHEX_GUTENBERG_H

#include <iostream>
#include <string>
#include <vector>

class Gutenberg {

public:
    static std::vector<std::string> getDatasetText();

private:
    static std::string trim(const std::string& str);
    static std::string preprocess(const std::string& filename);

};

#endif //MACHINELEARNINGMATHEX_GUTENBERG_H
