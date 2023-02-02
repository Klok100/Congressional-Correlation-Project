#pragma once


#include "graphs.h"

#include <iostream>
#include <list>
#include <stack>
#include <map>
#include <unordered_map>
#define NIL -1

class Tarjan {
    public:
        Tarjan(CongressGraph g);
        
        Tarjan(CongressGraph g, int threshold);

        void SCCUtil(std::string u, map<std::string, int> * disc, map<std::string, int> * low, std::stack<std::string> *st, map<std::string, bool> * stackMember);

        void SCC();

        vector<vector<std::string>> getSCC();

        vector<std::string> getSCCbySenator(std::string senator);

    private:
        CongressGraph g;
        std::map<std::string, std::vector<std::string>> adj;
        vector<string> data;
        vector<vector<std::string>> scc_;
        std::unordered_map<std::string, vector<std::string>> sen_SCC;
        int V;
};