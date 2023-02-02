#pragma once

#include "graphs.h"

#include <string>

using std::string;

/**
 * Function that returns the name of a legislator given their Bioguide ID
 *  
 * @param bio_id A legislator's Bioguide ID
 * @return The legislator's legal name
 */
string bio_To_Name(string bio_id);

/**
 * Function that returns the Bioguide ID of a legislator given their legal name
 *  
 * @param name A legislator's legal name
 * @return The legislator's Bioguide ID
 */
string name_To_Bio(string name);

/**
 * Function that returns the total number of other legislators that a legislator is connected to
 *  
 * @param g A graph of sponsors and co-sponsors.
 * @param legislator The Bioguide ID of the legislator
 * @return The number of bills other legislators that have co-sponsored a bill that is sponsored by the given legislator
 */
int numConnections(CongressGraph g, string legislator);

/**
 * Function that returns the total number of bills two legislators have worked on together
 *  
 * @param g A graph of sponsors and co-sponsors.
 * @param legislator1 The Bioguide ID of the first legislator
 * @param legislator2 The Bioguide ID of the second legislator
 * @return The number of bills the two legislators have worked on together
 */
int numBillsSponsoredTogether(CongressGraph g, string legislator1, string legislator2);

/**
 * Function that determines whether a given legislator exists
 *  
 * @param g A graph of sponsors and co-sponsors.
 * @param legislator The Bioguide ID of the legislator
 * @return A boolean value representing whether the given legislator exists in the graph
 */
bool printLegislatorValidation(CongressGraph g, string legislator);

void promptHome();
