#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "Vector.h"

using namespace std;

Vector<string> getPlanes(){
    ifstream in("planes.txt"); //plane file
    string temp;
    Vector<string> planes;

    while(in.peek() != EOF){
        getline(in,temp); //Reads in planes line by line
        planes.Add(temp); //Adds each plane to an array
    }
    /*for(int i=0;i<planes.GetSize();i++){
        cout << planes[i] << endl;
    }*/
    return planes; //Array of planes
}

bool checkPlane(Vector<string> & planes, string line, ofstream & out){
    for(unsigned i = 0;i< planes.GetSize();i++){ //Checks each plane against the non-formatted string in the HTML. If it's a match, print that plane name and return true.
        if(line.find(planes[i],0) != string::npos){
            out << planes[i] << ',';
            out.flush();
            planes.DeleteAt(i); //Deletes plane from array of planes so it's not detected twice.
            return true;
        }

    }
    return false;
}

bool checkKeyPhrase(string  s, ofstream & out, ifstream & in, string  line){
    static unsigned airspeed = 0; //Makes sure only three airspeeds are read in, due to varying numbers of airspeeds given

    if(line.find(s,0) != string::npos){ //If the HTML line equals one of the keyphrases
            if(airspeed <3 || s!="Maximum true air speed"){ //And it's not a third airspeed stat
                stringstream stream(line);
                getline(stream, line, ':');
                getline(stream, line, ' '); //boring string parsing technicality
                if(s=="Combat debut:"){
                        string second;
                        getline(stream, second);
                        out << line << " " << second << "\n";
                        out.flush();
                        airspeed=0;
                        return true; //If it returns true, then all stats have been read and the program starts checking for plane names again until there are no planes left.
                }
                getline(stream, line, ' ');
                if(s=="Maximum true air speed"){
                    airspeed++;
                }
                out << line << ","; //Prints the value of the statistic
                out.flush();
            }
        }
    return false;
}

void printPlaneData(ifstream & in, ofstream & out){
    string line;
    while(true){ //Keeps looping and checking phrases until "Useful load:" is found, at which point it stops checking and returns to looking for plane names.
        getline(in, line);

        checkKeyPhrase("Indicated stall speed in flight configuration:", out, in, line);
        checkKeyPhrase("Indicated stall speed in takeoff/landing configuration:", out, in, line);
        checkKeyPhrase("Dive speed limit:", out, in, line);
        checkKeyPhrase("Maximum load factor:", out, in, line);
        checkKeyPhrase("Stall angle of attack in flight configuration:", out, in, line);
        checkKeyPhrase("Stall angle of attack in landing configuration:", out, in, line);
        checkKeyPhrase("Maximum true air speed", out, in, line);
        checkKeyPhrase("Service ceiling:", out, in, line);
        checkKeyPhrase("Climb rate at", out, in, line);
        checkKeyPhrase("Maximum performance turn at sea level:", out, in, line);
        checkKeyPhrase("Maximum performance turn at 3000 m:", out, in, line);
        checkKeyPhrase("Flight endurance at 3000 m:", out, in, line);
        checkKeyPhrase("Takeoff speed:", out, in, line);
        checkKeyPhrase("Glideslope speed:", out, in, line);
        checkKeyPhrase("Landing speed:", out, in, line);
        checkKeyPhrase("Landing angle:", out, in, line);
        checkKeyPhrase("Supercharger gear shift altitude:", out, in, line);
        checkKeyPhrase("Empty weight:", out, in, line);
        checkKeyPhrase("Minimum weight (no ammo, 10% fuel):", out, in, line);
        checkKeyPhrase("Standard weight:", out, in, line);
        checkKeyPhrase("Maximum takeoff weight:", out, in, line);
        checkKeyPhrase("Fuel load:", out, in, line);
        checkKeyPhrase("Useful load:", out, in, line);
        checkKeyPhrase("Length:", out, in, line);
        checkKeyPhrase("Wingspan:", out, in, line);
        checkKeyPhrase("Wing surface:", out, in, line);
        if(checkKeyPhrase("Combat debut:", out, in, line)) return;


    }

}


int main()
{

    Vector<string> planes = getPlanes(); //Populates array of planes of which info is required
    ifstream in("html.txt"); //HTML of IL-2 plane stats
    if(!in){ //File not found
        cout << "Can't find HTML. Save it as \"html.txt\" case sensitive and place it in the same folder as the .exe";
        return 1;
    }


    ofstream out("IL-2 Plane Data.csv"); //Creates .csv and adds the first row
    out << "PLANE,Flight stall speed(kmph),takeoff stall speed(kmph),dive speed limit(kmph),maximum load(G),Stall AoA flight,Stall AoA landing," <<
            "max airspeed sea lvl(kmph),max airspeed medium(kmph),max airspeed high(kmph),service ceiling(m)," <<
            "climb rate sea lvl(m/s),climb rate 3000m(m/s),climb rate 6000m(m/s),max turn sea lvl(s),max turn 3000m(s),flight endurance 3000m(h),takeoff speed(kmph),glideslope speed(kmph),landing speed(kmph),landing angle,super charge gear shift alt.(m)," <<
            "empty weight(kg),min. weight(kg),std. weight(kg),max. takeoff weight(kg),fuel load(kg),useful load(kg),length(m),wingspan(m),wing surface(m^2),combat debut\n";
    out.flush();

    string line;

    while(in.peek() != EOF){ //Once the in file is end of file, there's nothing left to read so exit.
        getline(in, line); //Checks each line of HTML
        if(checkPlane(planes, line, out)){ //If it finds a plane, start checking for plane stat key phrases
            printPlaneData(in, out);
        }

    }
    out.close();
    in.close();



    return 0;
}
