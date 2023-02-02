#include "graphs.h"
#include "DFS.h"
#include "Dijkstra.h"
#include "Tarjan.h"
#include "Utils.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>

#include "includes/XMLParser.h"
#include "includes/graphs.h"
#include "lib/rapidxml-1.13/rapidxml_utils.hpp"

using std::string;
using std::cout;
using std::cin;
using std::getline;
using std::endl;
using std::to_string;
using std::vector;

#define MAX_LEGISLATORS_PER_LINE 8

/* ANSI Color Guides */
  std::string red = "\033[1;31m";
  std::string white = "\033[;37m";
  std::string blue = "\033[1;34m";
  std::string green = "\033[1;32m";
  std::string yellow = "\033[1;33m";
  std::string end_color = "\033[0m";

int main() {
    CongressGraph g;

    // Main screen where the user can choose if they want to work with the standard data set or import their own
    system("clear");
    std::cout << "- - - - - - - - - " << green << "CS 225 Project: Congressional Correlation" << end_color << " - - - - - - -"  << std::endl;
    std::cout << "      Created by: Kyle Kenmotsu, Joe Ku, Nathan Kim, and Neil Prabhu" << std::endl;
    std::cout << "=========================================================================" << std::endl;
    std::cout << blue << "  This project uses the public dataset available from GovInfo Bulk Data" << end_color << std::endl;
    std::cout << "=========================================================================" << std::endl;
    std::cout << "Please select whether you would like to input your own formatted CSV file or use the standard CSV file:" << std::endl;
    std::cout << yellow << "[1]" << end_color << " Import User CSV File (Must be Correctly Formatted)" << std::endl;
    std::cout << yellow << "[2]" << end_color << " Continue with Standard CSV File" << std::endl;
    std::cout << yellow << "[3]" << end_color << " Exit" << std::endl;

    std::string user_input;
    std::string file_location;
    size_t navigationchoice;
    std::getline(std::cin, user_input);

    while (true) {
      try {
        navigationchoice = std::stoi(user_input);
        if (navigationchoice > 0 && navigationchoice < 4) {
         break;
        }
        std::cout << red << "Please enter a valid option:" << end_color << std::endl;
        std::getline(std::cin, user_input);
      } catch (...) {
        std::cout << red << "Please enter a valid option:" << end_color << std::endl;
        std::getline(std::cin, user_input);
      }
    }

    if (navigationchoice == 1) {
      // Allows the user to enter their own properly formatted CSV 
      // (CSV file must be put in the folder bill_sponsors/user_csv)
      system("clear");
      cout << "Please enter the name of the CSV file you want to import (Please include the .csv at the end): ";
      string user_csv;
      getline(cin, user_csv);
      file_location = "bill_sponsors/user_csv/" + user_csv;
      bool fileExists = false;

      while (!fileExists) {
        std::ifstream myFile;
        myFile.open(file_location);
        if (!myFile) {
          cout << "Please enter a valid CSV file name: ";
          getline(cin, user_csv);
          if (user_csv != "") {
            file_location = "bill_sponsors/user_csv/" + user_csv;
          }
        } else {
          fileExists = true;
        }
      }

      g.importData(file_location);
      goto HOME;

    } else if (navigationchoice == 2) {
      // Imports in the full dataset
      g.importData("bill_sponsors/bill_sponsors.csv");   
      goto HOME;

    } else {
        // Exits the Program
        system("clear");
        std::cout << "================" << std::endl;
        std::cout << green << "    Goodbye!" << end_color << std::endl;
        std::cout << "================" << std::endl;  
        cout << "Thanks for using our program. Have a nice day!\n\n";
        return 0;      
    }

// Main Home Screen
HOME: system("clear");
    std::cout << "- - - - - - - - - " << green << "CS 225 Project: Congressional Correlation" << end_color << " - - - - - - -"  << std::endl;
    std::cout << "      Created by: Kyle Kenmotsu, Joe Ku, Nathan Kim, and Neil Prabhu" << std::endl;
    std::cout << "=========================================================================" << std::endl;
    std::cout << blue << "  This project uses the public dataset available from GovInfo Bulk Data" << end_color << std::endl;
    std::cout << "=========================================================================" << std::endl; 
    std::cout << "Select an option below and hit enter to run the selected algorithm or action: " << std::endl << std::endl;
    std::cout << yellow << "[1]" << end_color << " Depth-First Search Traversal" << std::endl;
    std::cout << yellow << "[2]" << end_color << " Dijkstra's Algorithm" << std::endl;
    std::cout << yellow << "[3]" << end_color << " Tarjan's Algorithm" << std::endl;
    std::cout << yellow << "[4]" << end_color << " Get Number of Connections for a Legislator" << std::endl;
    std::cout << yellow << "[5]" << end_color << " Get Number of Bills Worked On Together (2 Legislators)" << std::endl;
    std::cout << yellow << "[6]" << end_color << " Get Name via BioGuide ID" << std::endl;
    std::cout << yellow << "[7]" << end_color << " Get BioGuide ID via Name" << std::endl;
    std::cout << yellow << "[8]" << end_color << " Exit" << std::endl;

    std::getline(std::cin, user_input);

    // Checks that the user input is valid and turns it into an integer
    while (true) {
      try {
        navigationchoice = std::stoi(user_input);
        if (navigationchoice > 0 && navigationchoice < 9) {
         break;
        }
        std::cout << red << "Please enter a valid option:" << end_color << std::endl;
        std::getline(std::cin, user_input);
      } catch (...) {
        std::cout << red << "Please enter a valid option:" << end_color << std::endl;
        std::getline(std::cin, user_input);
      }
    }

    if (navigationchoice == 1) {
        // Run DFS
        system("clear");
        std::cout << "==========================" << std::endl;
        std::cout << green << "    Depth-First Search" << end_color << std::endl;
        std::cout << "==========================" << std::endl;        

        DFS d(g);

        // Prompt back to Homescreen
        promptHome();
        goto HOME;

    } else if (navigationchoice == 2) {
        // Run Dijkstra's Algorithm
        system("clear");
        std::cout << "============================" << std::endl;
        std::cout << green << "    Dijkstra's Algorithm" << end_color << std::endl;
        std::cout << "============================" << std::endl;
        bool isValid = true;
        cout << "Enter two legislators (BioGuide IDs) to connect\nLegislator 1: ";
        string legislator1;
        string legislator2;
        getline(cin, legislator1);

        isValid = printLegislatorValidation(g, legislator1);
        if (isValid) {
          cout << "Legislator 2: ";
          getline(cin, legislator2);
          isValid = printLegislatorValidation(g, legislator2);
        }

        if (isValid) {
          Dijkstra d;
          vector<string> path = d.findShortestPath(g, legislator1, legislator2);
          int connectivity = d.getConnectivityRating(g, legislator1, legislator2);
          if (connectivity == -1) {
            cout << "There are no connections between Legislator " << legislator1 << " and Legislator " 
                << legislator2 << "\n";
          } else {
            cout << "Path: ";
            for (unsigned int i = 0; i < path.size() - 1; i++) {
              cout << path[i] << " --> ";
            }
            cout << path[path.size() - 1] << "\n";
            cout << "Connectivity Rating: " << connectivity << "\n";
          }
        }

        // Prompt back to Homescreen
        promptHome();
        goto HOME;

    } else if (navigationchoice == 3) {
        // Run Tarjan's Algorithm
        system("clear");
        std::cout << "==========================" << std::endl;
        std::cout << green << "    Tarjan's Algorithm" << end_color << std::endl;
        std::cout << "==========================" << std::endl;
        string legislator_in;
        cout << "Enter a legislator (BioGuide ID) to find Strongly Connected Component (SCC) for: ";
        bool isValid;
        getline(cin, legislator_in);
        isValid = printLegislatorValidation(g, legislator_in);

        if (isValid) {
          cout << "Enter integer threshold t > 1 (Legislators will only be considered to have an edge between them if edge.weight >= t): ";
          string threshold_in;
          getline(cin, threshold_in);
          unsigned int threshold;
          try {
            threshold = std::stoul(threshold_in);
          }
          catch (...) {
            cout << "Invalid input.\n";
            promptHome();
            goto HOME;
          }
          if (threshold < 1) {
            cout << "Invalid input.\n";
            promptHome();
            goto HOME;
          }
          
          Tarjan graph(g, threshold);
          graph.SCC();
          vector<std::string> this_scc = graph.getSCCbySenator(legislator_in);
          if (this_scc.size() > 2) {
            cout << "Legislators strongly connected to " << legislator_in << ":\n";

            int counter = 0;
            for (unsigned p = 0; p < this_scc.size(); p++) {
              cout << this_scc[p];
              counter++;
              if (p != this_scc.size() - 1 && counter < (MAX_LEGISLATORS_PER_LINE)) {
                cout << ", ";
              }
              if (counter == MAX_LEGISLATORS_PER_LINE) {
                counter = 0;
                cout << "\n";
              }
            }
            cout << "\nThere are " << this_scc.size() << " legislators in this strongly connected component(scc)!\n";
            cout << "\n===================================";
          } else {
            cout << "No legislators strongly connected to " << legislator_in << endl;
          }
        }

        // Prompt back to Homescreen
        promptHome();
        goto HOME;
    } else if (navigationchoice == 4) {
        // Runs Number of Connections for a Legislator
        system("clear");
        std::cout << "=============================" << std::endl;
        std::cout << green << "    Number of Connections" << end_color << std::endl;
        std::cout << "=============================" << std::endl;  

        cout << "Enter a legislator to see how many connections they have: ";
        string legislator;
        getline(cin, legislator);
        int numBills = numConnections(g, legislator);
        if (numBills != -1) {
          cout << legislator << " is connected to " << numBills << " other legislators.\n";
        }

        // Prompt back to Homescreen
        promptHome();
        goto HOME;

    } else if (navigationchoice == 5) {
        // Runs Number of Bills Worked on Together for 2 Legislators
        system("clear");
        std::cout << "==========================================" << std::endl;
        std::cout << green << "    Number of Bills Worked on Together" << end_color << std::endl;
        std::cout << "==========================================" << std::endl;  

        cout << "Enter two legislators (BioGuide IDs) to see how many bills they have worked on together\nLegislator 1: ";
        bool isValid = true;
        string legislator1;
        string legislator2;
        getline(cin, legislator1);

        isValid = printLegislatorValidation(g, legislator1);
        if (isValid) {
          cout << "Legislator 2: ";
          getline(cin, legislator2);
          isValid = printLegislatorValidation(g, legislator2);
        }

        if (isValid) {
          int numBills = numBillsSponsoredTogether(g, legislator1, legislator2);
          if (numBills == 1) {
            cout << legislator1 << " and " << legislator2 << " have worked on " << numBills << " bill together.\n";
          } else {
            cout << legislator1 << " and " << legislator2 << " have worked on " << numBills << " bills together.\n";
          }
        }  

        // Prompt back to Homescreen
        promptHome();
        goto HOME;

    } else if (navigationchoice == 6) {
        // Runs BioGuide ID To Name
        system("clear");
        std::cout << "===========================" << std::endl;
        std::cout << green << "    BioGuide ID to Name" << end_color << std::endl;
        std::cout << "===========================" << std::endl;  

        cout << "Enter the BioGuide ID of the Legislator you want the name of: ";
        string bioguideID;
        getline(cin, bioguideID);

        cout << bio_To_Name(bioguideID);

        // Prompt back to Homescreen
        promptHome();
        goto HOME;    

    } else if (navigationchoice == 7) {
        // Runs Name To BioGuide ID
        system("clear");
        std::cout << "===========================" << std::endl;
        std::cout << green << "    Name to BioGuide ID" << end_color << std::endl;
        std::cout << "===========================" << std::endl;  

        cout << "Enter the name of the Legislator (Last, First Middle Initial) you want the BioGuide ID of: ";
        string name;
        getline(cin, name);

        cout << name_To_Bio(name);

        // Prompt back to Homescreen
        promptHome();
        goto HOME;

    } else if (navigationchoice == 8) {
        // Exits the Program
        system("clear");
        std::cout << "================" << std::endl;
        std::cout << green << "    Goodbye!" << end_color << std::endl;
        std::cout << "================" << std::endl;  
        cout << "Thanks for using our program. Have a nice day!\n\n";
        return 0;
    }
}