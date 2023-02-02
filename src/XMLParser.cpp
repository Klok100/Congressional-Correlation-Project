#include "XMLParser.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>

#include "../lib/rapidxml-1.13/rapidxml_utils.hpp"

using std::string;
using std::cout;
using std::endl;
using std::to_string;

void XMLParser::parse() {
    std::ofstream ofs;
    ofs.open("bill_sponsors/bill_sponsors.csv");

    for (int file_num = 108; file_num < 109; file_num++) {
        for (int index = 1; index < 9100; index++) {
            string fileName = "BILLSTATUSzip/BILLSTATUS-" + to_string(file_num) + "-" + "hr/BILLSTATUS-" 
            + to_string(file_num) + "hr" + to_string(index) + ".xml";
            cout << fileName << "\n";

            
            std::ifstream myFile;
            myFile.open(fileName);
            if (!myFile) {
                continue;
            }

            char fileName_char[100];
            strcpy(fileName_char, fileName.c_str());

            rapidxml::file<> xmlFile(fileName_char);
            rapidxml::xml_document<> doc;
            doc.parse<0>(xmlFile.data());

            string test = doc.first_node()->first_node()->first_node("sponsors")->first_node()->first_node()->value();
            cout << test << endl;

            ofs << doc.first_node()->first_node()->first_node("sponsors")->first_node()->first_node()->value() << ",";
            rapidxml::xml_node<>* cosp_node = doc.first_node()->first_node()->first_node("cosponsors")->first_node();
            while (cosp_node) {
                ofs << cosp_node->first_node()->value() << ",";
                cosp_node = cosp_node->next_sibling();
            }
            ofs << "\n";
        }
    }

    for (int file_num = 108; file_num < 118; file_num++) {
        for (int index = 1; index < 9100; index++) {
            string fileName = "BILLSTATUSzip/BILLSTATUS-" + to_string(file_num) + "-" + "s/BILLSTATUS-" 
            + to_string(file_num) + "s" + to_string(index) + ".xml";
            cout << fileName << "\n";
            
            std::ifstream myFile;
            myFile.open(fileName);
            if (!myFile) {
                continue;
            }

            char fileName_char[100];
            strcpy(fileName_char, fileName.c_str());

            rapidxml::file<> xmlFile(fileName_char);
            rapidxml::xml_document<> doc;
            doc.parse<0>(xmlFile.data());

            string test = doc.first_node()->first_node()->first_node("sponsors")->first_node()->first_node()->value();
            cout << test << endl;

            ofs << doc.first_node()->first_node()->first_node("sponsors")->first_node()->first_node()->value() << ",";
            rapidxml::xml_node<>* cosp_node = doc.first_node()->first_node()->first_node("cosponsors")->first_node();
            while (cosp_node) {
                ofs << cosp_node->first_node()->value() << ",";
                cosp_node = cosp_node->next_sibling();
            }
            ofs << "\n";        
        }
    }
    
    ofs.close();
}