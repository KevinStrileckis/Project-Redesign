#include "../include/LocationList.h"
#include "../include/Location.h"
#include <iostream>
#include <fstream>
#include <string>
#include <map>
using namespace std;

void writeLocationListToFile(map<Location *, int> sites, string file){
    ofstream ofp("sites.txt", ofstream::out);
    cout<<"Start\n";
    for(map<Location*, int>::iterator it=sites.begin(); it!=sites.end(); ++it){
        cout<<*(it->first);
        ofp<<*(it->first);
    }
}

map<Location *, int> makeLocationList(map<Location *, int> locs){
    int index = 0;

    locs[new Location(" KevinStrileckis.", "  Personal", ' ', ' ', 's')]	= 0;
    locs[new Location("      SketchList.", "    Public", ' ', ' ', 's')]	= 32;
    locs[new Location("      TotesLegal.", "    Public", ' ', ' ', 's')]	= 64;
    locs[new Location("        eKrampus.", "    Public", ' ', ' ', 's')]	= 96;
    locs[new Location("     MediaOnFire.", "    Public", ' ', ' ', 's')]	= 128;

    index = 160;

    //Make (hacked) Dummy Profiles -- can be used by hackers
    char *buffer;
    for(int i=0; i<64; ++i, index+=32){
        buffer = "                .";
        buffer[14] = to_string(i)[0];
        locs[new Location(buffer, "  Personal", ' ', ' ', 's')]	= index;
    }

    //Make darkweb sites
    for(int i=0; i<3; ++i, index+=32){
        locs[new Location("fejwio21ji.onion.", "   Darkweb", ' ', ' ', 's')]	= index;
    }

    return locs;
}

map<string, int> makeLocationList(map<string, int> locs, bool tf){
    int index = 0;

    locs[" KevinStrileckis.  Personal  s"]	= 0;
    locs["      SketchList.    Public  s"]	= 32;
    locs["      TotesLegal.    Public  s"]	= 64;
    locs["        eKrampus.    Public  s"]	= 96;
    locs["     MediaOnFire.    Public  s"]	= 128;

    index = 160;

    //Make (hacked) Dummy Profiles -- can be used by hackers
    string s = "                .";
    for(int i=0; i<12; ++i, index+=32){
        s[0] = (char)(i+96);
        s[1] = (char)(i+96+1);
        s[2] = (char)(i%10 + 72);
        s[3] = (char)(i%10 + 48);
        s[6] = (char)(i%10 + 96);
        locs[s+"  Personal  s"]	= index;
    }

    //Make darkweb sites
    s = "fejwio21ji.onion.";
    for(int i=0; i<3; ++i, index+=32){
        s[3] = (char)(i+48);
        s[6] = (char)(i+48);
        locs[s+"   Darkweb  s"]	= index;
    }

    return locs;
}

map<string,int> makeList(map<string,int> locs){
    int index = 0;

    locs["KStril"]		= 0;
    locs["SketchList"]	= 32;
    locs["TotesLegal"]	= 64;
    locs["eKrampus"]	= 96;
    locs["MediaOnFire"]	= 128;

    index = locs["MediaOnFire"];

    //Make (hacked) Dummy Profiles -- can be used by hackers
    for(int i=0; i<64; ++i, index+=32){
        locs[""]	= index;
    }

    //Make darkweb sites
    for(int i=0; i<6; ++i, index+=32){
        locs[""]	= index;
    }
    return locs;
}
