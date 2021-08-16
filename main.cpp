#include <iostream>
#include <string>
#include <vector>
#include <cctype>
 
using namespace std;

enum en_DIRS {FRONT, BACK, LEFT, RIGHT};
enum en_ROOMS {ENTRANCE, LIVINGROOM, BATHROOM, MASTERBEDROOM , CORRIDOR ,STAIRSDOWN , BASEMENT , DININGROOM , SWIMMINGPOOL , SHED , LAUNDRY , BACKYARD , KITCHEN , STOREROOM , CHILDROOM };
enum en_VERBS {USE, OPEN, CLOSE, EXAMINE, INVENTORY, LOOK};
enum en_NOUNS {KEY , APPLE , AXE, TORCH, SHOTGUN , SHOTGUNAMMO, DININGCODE , BEDROOMCODE};

const int NONE = -1;
const int DIRS = 4;
const int ROOMS = 15;
const int VERBS = 6;
const int NOUNS = 8;

struct word
{
    string word;
    int code;
};

struct room
{
    string description;
    int exits_to_room[DIRS];
    string story;
};

struct noun
{
    string word;
    string description;
    int code;
    int location;
    bool on_hand;
};

// ----------------------------------------------------------------------------------------

void set_rooms(room *rms)
{
    rms[ENTRANCE].description.assign("entrance");
    rms[ENTRANCE].exits_to_room[FRONT] = LIVINGROOM;
    rms[ENTRANCE].exits_to_room[BACK ] = NONE;
    rms[ENTRANCE].exits_to_room[LEFT ] = NONE;
    rms[ENTRANCE].exits_to_room[RIGHT] = NONE;
    rms[ENTRANCE].story.assign("The sky is misty and the clouds are dark, u can hear wolves howl and bats go brrrrr");
 
    rms[LIVINGROOM].description.assign("living room");
    rms[LIVINGROOM].exits_to_room[FRONT] = CORRIDOR;
    rms[LIVINGROOM].exits_to_room[BACK ] = ENTRANCE;
    rms[LIVINGROOM].exits_to_room[LEFT ] = BATHROOM;
    rms[LIVINGROOM].exits_to_room[RIGHT] = MASTERBEDROOM;

    rms[BATHROOM].description.assign("bathroom");
    rms[BATHROOM].exits_to_room[FRONT] = NONE;
    rms[BATHROOM].exits_to_room[BACK ] = LIVINGROOM;
    rms[BATHROOM].exits_to_room[LEFT ] = NONE;
    rms[BATHROOM].exits_to_room[RIGHT] = NONE;

    rms[MASTERBEDROOM].description.assign("master bedroom");
    rms[MASTERBEDROOM].exits_to_room[FRONT] = NONE;
    rms[MASTERBEDROOM].exits_to_room[BACK ] = LIVINGROOM;
    rms[MASTERBEDROOM].exits_to_room[LEFT ] = NONE;
    rms[MASTERBEDROOM].exits_to_room[RIGHT] = NONE;

    rms[CORRIDOR].description.assign("corridor");
    rms[CORRIDOR].exits_to_room[FRONT] = DININGROOM;
    rms[CORRIDOR].exits_to_room[BACK ] = LIVINGROOM;
    rms[CORRIDOR].exits_to_room[LEFT ] = CHILDROOM;
    rms[CORRIDOR].exits_to_room[RIGHT] = STAIRSDOWN;

    rms[CHILDROOM].description.assign("child's room");
    rms[CHILDROOM].exits_to_room[FRONT] = NONE;
    rms[CHILDROOM].exits_to_room[BACK ] = CORRIDOR;
    rms[CHILDROOM].exits_to_room[LEFT ] = NONE;
    rms[CHILDROOM].exits_to_room[RIGHT] = NONE;

    rms[STAIRSDOWN].description.assign("stairs down");
    rms[STAIRSDOWN].exits_to_room[FRONT] = BASEMENT;
    rms[STAIRSDOWN].exits_to_room[BACK ] = CORRIDOR;
    rms[STAIRSDOWN].exits_to_room[LEFT ] = NONE;
    rms[STAIRSDOWN].exits_to_room[RIGHT] = NONE;

    rms[BASEMENT].description.assign("basement");
    rms[BASEMENT].exits_to_room[FRONT] = NONE;
    rms[BASEMENT].exits_to_room[BACK ] = STAIRSDOWN;
    rms[BASEMENT].exits_to_room[LEFT ] = NONE;
    rms[BASEMENT].exits_to_room[RIGHT] = NONE;

    rms[DININGROOM].description.assign("dining room");
    rms[DININGROOM].exits_to_room[FRONT] = KITCHEN;
    rms[DININGROOM].exits_to_room[BACK ] = NONE;
    rms[DININGROOM].exits_to_room[LEFT ] = SWIMMINGPOOL;
    rms[DININGROOM].exits_to_room[RIGHT] = NONE;

    rms[SWIMMINGPOOL].description.assign("swimming pool");
    rms[SWIMMINGPOOL].exits_to_room[FRONT] = SHED;
    rms[SWIMMINGPOOL].exits_to_room[BACK ] = DININGROOM;
    rms[SWIMMINGPOOL].exits_to_room[LEFT ] = NONE;
    rms[SWIMMINGPOOL].exits_to_room[RIGHT] = NONE;

    rms[KITCHEN].description.assign("kitchen");
    rms[KITCHEN].exits_to_room[FRONT] = BACKYARD;
    rms[KITCHEN].exits_to_room[BACK ] = DININGROOM;
    rms[KITCHEN].exits_to_room[LEFT ] = LAUNDRY;
    rms[KITCHEN].exits_to_room[RIGHT] = STOREROOM;

    rms[LAUNDRY].description.assign("laundry room");
    rms[LAUNDRY].exits_to_room[FRONT] = NONE;
    rms[LAUNDRY].exits_to_room[BACK ] = KITCHEN;
    rms[LAUNDRY].exits_to_room[LEFT ] = NONE;
    rms[LAUNDRY].exits_to_room[RIGHT] = NONE;

    rms[SHED].description.assign("shed");
    rms[SHED].exits_to_room[FRONT] = NONE;
    rms[SHED].exits_to_room[BACK ] = SWIMMINGPOOL;
    rms[SHED].exits_to_room[LEFT ] = NONE;
    rms[SHED].exits_to_room[RIGHT] = NONE;

    rms[STOREROOM].description.assign("storage room");
    rms[STOREROOM].exits_to_room[FRONT] = NONE;
    rms[STOREROOM].exits_to_room[BACK ] = KITCHEN;
    rms[STOREROOM].exits_to_room[LEFT ] = NONE;
    rms[STOREROOM].exits_to_room[RIGHT] = NONE;

    rms[BACKYARD].description.assign("backyard");
    rms[BACKYARD].exits_to_room[FRONT] = NONE;
    rms[BACKYARD].exits_to_room[BACK ] = KITCHEN;
    rms[BACKYARD].exits_to_room[LEFT ] = NONE;
    rms[BACKYARD].exits_to_room[RIGHT] = NONE;


}

// --------------------------------------------------------------------
 
void set_directions(word *dir)
{
    dir[FRONT].code = FRONT;
    dir[FRONT].word = "FRONT";
    dir[RIGHT].code = RIGHT;
    dir[RIGHT].word = "RIGHT";
    dir[BACK].code = BACK;
    dir[BACK].word = "BACK";
    dir[LEFT].code = LEFT;
    dir[LEFT].word = "LEFT";
}
 
// --------------------------------------------------------------------

void set_verbs(word *vbs)
{
    // enum en_VERBS {GET, DROP, USE, OPEN, CLOSE, EXAMINE, INVENTORY, LOOK};
    vbs[USE].code = USE;
    vbs[USE].word = "USE";
    vbs[OPEN].code = OPEN;
    vbs[OPEN].word = "OPEN";
    vbs[CLOSE].code = CLOSE;
    vbs[CLOSE].word = "CLOSE";
    vbs[EXAMINE].code = EXAMINE;
    vbs[EXAMINE].word = "EXAMINE";
    vbs[INVENTORY].code = INVENTORY;
    vbs[INVENTORY].word = "INVENTORY";
    vbs[LOOK].code = LOOK;
    vbs[LOOK].word = "LOOK";
}


void set_nouns(noun *nns)
{
    //enum en_NOUNS {STORE_DOOR, MAGNET, METER, ROULETTE, MONEY, FISHROD};
    nns[KEY].word = "key";
    nns[KEY].code = KEY;
    nns[KEY].description = "a closed store room door";
    nns[KEY].on_hand = false;
    nns[KEY].location = MASTERBEDROOM;

    nns[APPLE].word = "apple";
    nns[APPLE].code = APPLE;
    nns[APPLE].description = "you found an apple";
    nns[APPLE].on_hand = false;
    nns[APPLE].location = KITCHEN;

    nns[AXE].word = "axe";
    nns[AXE].code = AXE;
    nns[AXE].description = "u got an axe!";
    nns[AXE].on_hand= false;
    nns[AXE].location = BACKYARD;

    nns[TORCH].word = "torch";
    nns[TORCH].code = TORCH;
    nns[TORCH].description = "you found a torch";
    nns[TORCH].on_hand = false;
    nns[TORCH].location = LAUNDRY;

    nns[SHOTGUN].word = "shotgun";
    nns[SHOTGUN].code = KEY;
    nns[SHOTGUN].description = "a closed store room door";
    nns[SHOTGUN].on_hand = false;
    nns[SHOTGUN].location = STOREROOM;

    nns[SHOTGUNAMMO].word = "shotgun ammo";
    nns[SHOTGUNAMMO].code = SHOTGUNAMMO;
    nns[SHOTGUNAMMO].description = "you found some shotgun ammo";
    nns[SHOTGUNAMMO].on_hand = false;
    nns[SHOTGUNAMMO].location = SHED;

    nns[DININGCODE].word = "dining room code";
    nns[DININGCODE].code = DININGCODE;
    nns[DININGCODE].description = "you found a code";
    nns[DININGCODE].on_hand = false;
    nns[DININGCODE].location = BASEMENT;

    nns[BEDROOMCODE].word = "bedroom code";
    nns[BEDROOMCODE].code = BEDROOMCODE;
    nns[BEDROOMCODE].description = "you found sa code";
    nns[BEDROOMCODE].on_hand = false;
    nns[BEDROOMCODE].location = BATHROOM;

    
}
// ------------------------------------------------------------------------------------------------
void look_around(int loc, room *rms, word *dir, /* Added parameter */ noun *nns)
{
    int i;
    cout << "I am in the " << rms[loc].description << "." << endl;
    cout << rms[loc].story << "." << endl;
 
    for(i = 0; i < DIRS; i++)
    {
        if(rms[loc].exits_to_room[i] != NONE)
        {
            cout << "There is an exit " << dir[i].word << " to a " << rms[rms[loc].exits_to_room[i]].description << "." << endl;
        }
    }
 
    // Added code
    // The look command should check which objects (nouns) are in the current room and report them to the player.
    for(i = 0; i < NOUNS; i++)
    {
        if(nns[i].location == loc)
        {
            cout << "I see " << nns[i].description << "." << endl;
        }
    }
}

void inventory(noun *nns)
{
    int i;
    for(i = 0; i < NOUNS; i++)
    {
        if(nns[i].on_hand == true)
        {
            cout << "U have " << nns[i].word; 
        }

    }

}

bool parser(int &loc, string wd1, word *dir, word *vbs, room *rms, /* Added parameter */ noun *nns)
{
    // word *dir is direction
    // word *vbs is action used
    // Added code
    // ....
    string VERB_ACTION = wd1;

    if(VERB_ACTION == "2")
    {
        wd1 = "FRONT";
    }

    if(VERB_ACTION == "3")
    {
        wd1 = "RIGHT";
    }

    if(VERB_ACTION == "4")
    {
        wd1 = "LEFT";
    }

    if(VERB_ACTION == "5")
    {
        wd1 = "BACK";
    }

    int i;
    for(i = 0; i < DIRS; i++)
    {
        if(wd1 == dir[i].word)
        {
            if(loc == CORRIDOR && dir[i].code == FRONT && nns[DININGCODE].on_hand == false)
            {
                cout << "this door is locked find a passcode to open it";
            }
            else if(rms[loc].exits_to_room[dir[i].code] != NONE)
            {
                
                loc = rms[loc].exits_to_room[dir[i].code];
                cout << "I am now in the " << rms[loc].description << "." << endl;
                // Added code. Special locked rooms


                if(loc == MASTERBEDROOM && nns[BEDROOMCODE].on_hand == true)
                {
                    nns[KEY].on_hand = true;
                    cout << "U HAVE OBTAINED A KEY";
                }
                // ....
                

                if (loc == BASEMENT)
                {
                    nns[DININGCODE].on_hand = true;
                    cout << "you have found a passcode for the dining room in a note";
                }
                return true;
            }
            else
            {
                cout << "No exit that way." << endl;
                return true;
            }
        }
    }
 
    // Added code
    // ....

    if(VERB_ACTION == "1")
    {
        look_around(loc, rms, dir, /* Added parameter nns */ nns);
        return true;
    }
    cout << VERB_ACTION;

    if(VERB_ACTION == "8")
    {
        inventory(nns);
        return true;
    }

 
    // Added code
    // Actions for usage of VERB OPEN
    // ....
 
    return false;
}


int main()
{
    string command;
    string word_1;
 
    room rooms[ROOMS];
    set_rooms(rooms);
 
    word directions[DIRS];
    set_directions(directions);
 
    word verbs[VERBS];
    set_verbs(verbs);
 
    // Added code
    noun nouns[NOUNS];
    set_nouns(nouns);
     // ....
 
    int location = ENTRANCE;
    while(word_1 != "6")
    {

	    cout << "1. to look around" << endl;
	    cout << "2. go front" << endl;
        cout << "3. go right" << endl;
        cout << "4. go left" << endl;
        cout << "5. go back" << endl;
        cin >> word_1;
        cout << "\n\n";


    
        if(word_1 != "6")
        {
            parser(location, word_1, directions, verbs, rooms, /* Added parameter */ nouns);
        }
    }
    return 0;

}