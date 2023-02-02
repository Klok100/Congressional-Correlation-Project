#pragma once
#include <string>

class XMLParser {
    public:
        /**
          * Function that extracts the sponsors and cosponsors from the original
          * dataset and outputs a condensed csv file containing only the sponsors
          * and cosponsors.   
          */
        void parse();
};