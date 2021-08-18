#include <iostream>
#include <unistd.h>

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
string bathroom_monster = R"(As soon as I open the bathroom door, I see a huge Grim Reaper.
                                         .""--..__
                     _                     []       ``-.._
                  .'` `'.                  ||__           `-._
                 /    ,-.\                 ||_ ```---..__     `-.
                /    /:::\\               /|//}          ``--._  `.
                |    |:::||              |////}                `-. \
                |    |:::||             //'///                    `.\
                |    |:::||            //  ||'                      `|
                /    |:::|/        _,-//\  ||
               /`    |:::|`-,__,-'`  |/  \ ||
             /`  |   |'' ||           \   |||
           /`    \   |   ||            |  /||
         |`       |  |   |)            \ | ||
        |          \ |   /      ,.__    \| ||
        /           `         /`    `\   | ||
       |                     /        \  / ||
       |                     |        | /  ||
       /         /           |        `(   ||
      /          .           /          )  ||
     |            \          |     ________||
    /             |          /     `-------.|
   |\            /          |              ||
   \/`-._       |           /              ||
    //   `.    /`           |              ||
   //`.    `. |             \              ||
  ///\ `-._  )/             |              ||
 //// )   .(/               |              ||
 ||||   ,'` )               /              //
 ||||  /                    /             || 
 `\\` /`                    |             // 
     |`                     \            ||  
    /                        |           //  
  /`                          \         //   
/`                            |        ||    
`-.___,-.      .-.        ___,'        (/    
         `---'`   `'----'`

The reaper throws the sickle almost missing my heart. I use the shotgun and kill the monster and on its hand, I find the code for the master bedroom written.
        )";


string corridor = R"(The room was dark and desolate. Everything was silent, except for the sound of my heavy breathing.My heart was pounding so hard I thought they could hear it)";

string childroomnote = R"(My eyes widened as I turned to the side and saw something on the wall. It was blood. The last thing I wanted to see in here. The blood was written in shaky letters that I could barely comprehend.
On the floor i find a note.

   ______________________________
 / \                             \ .
|   | I have been trappeed here   |.
 \ _| for 5 days without food     |.
    | and water now. There are    |.
    | monsters in every room.     |.
    | I found out that the        |.
    | moster in the bathroom has  |.
    | the key to the master       |.
    | bedroom and with this key   |.
    | you will be able to escape  |.
    | this haunted house. THE     |.
    | VOICES YOU HEAR ARE NOT     |.
    | REAL YOU MUST BREAK FREE    |.
    | OUT OF IT!                  |.
    |    _________________________|___
    |   /                            /.
    \ _/dc__________________________/ .  )";


string swimmingpool = R"(
            / . .\         
            \  ---<        
             \  /
   __________/ /
-=:___________/

            / . .\
            \  ---<
             \  /
   __________/ /
-=:___________/

            / . .\
            \  ---<
             \  /
   __________/ /
-=:___________/

There are some venomous snakes in the swimming pool. They start to approach you, In shock you take the shotgun and try to shoot it forgetting that the gun is not loaded.
The snakes try to wrap around your leg. You take the axe and strike it a few times. One of the snake manages to bite you. You start bleeding out but you continue to move on.

)";

string masterbedroom = R"(

                            ,-.
       ___,---.__          /'|`\          __,---,___
    ,-'    \`    `-.____,-'  |  `-.____,-'    //    `-.
  ,'        |           ~'\     /`~           |        `.
 /      ___//              `. ,'          ,  , \___      \
|    ,-'   `-.__   _         |        ,    __,-'   `-.    |
|   /          /\_  `   .    |    ,      _/\          \   |
\  |           \ \`-.___ \   |   / ___,-'/ /           |  /
 \  \           | `._   `\\  |  //'   _,' |           /  /
  `-.\         /'  _ `---'' , . ``---' _  `\         /,-'
     ``       /     \    ,='/ \`=.    /     \       ''
             |__   /|\_,--.,-.--,--._/|\   __|
             /  `./  \\`\ |  |  | /,//' \,'  \
            /   /     ||--+--|--+-/-|     \   \
           |   |     /'\_\_\ | /_/_/`\     |   |
            \   \__, \_     `~'     _/ .__/   /
             `-._,-'   `-._______,-'   `-._,-'


Final boss
You open the door to the master bedroom and you find the key to exit the house. The key was guarded by Surtur the fire giant. You load the shotgun ammo and fire a few shots at him. The bullets merely did any damage to him.You then take the axe swing it towards the beasts head.
The axe directly slits the throat of the giant and falls to the ground
)";
// ----------------------------------------------------------------------------------------

void set_rooms(room *rms)
{
    rms[ENTRANCE].description.assign("entrance");
    rms[ENTRANCE].exits_to_room[FRONT] = LIVINGROOM;
    rms[ENTRANCE].exits_to_room[BACK ] = NONE;
    rms[ENTRANCE].exits_to_room[LEFT ] = NONE;
    rms[ENTRANCE].exits_to_room[RIGHT] = NONE;
    rms[ENTRANCE].story.assign("I made it to the front door following the voice. The door is wide open and i can see the living room in front filled with cobblewebs.Use the commands to move inside");
 
    rms[LIVINGROOM].description.assign("living room");
    rms[LIVINGROOM].exits_to_room[FRONT] = CORRIDOR;
    rms[LIVINGROOM].exits_to_room[BACK ] = ENTRANCE;
    rms[LIVINGROOM].exits_to_room[LEFT ] = BATHROOM;
    rms[LIVINGROOM].exits_to_room[RIGHT] = MASTERBEDROOM;
    rms[LIVINGROOM].story.assign("Coughing and sneezing, I entered the doorway causing a cloud of dust erupt in my face. It was frightening inside. The wallpapers were torn and hanging, pictures hung crooked on the walls and some were lying shattered on the floor.");


    rms[BATHROOM].description.assign("bathroom");
    rms[BATHROOM].exits_to_room[FRONT] = NONE;
    rms[BATHROOM].exits_to_room[BACK ] = LIVINGROOM;
    rms[BATHROOM].exits_to_room[LEFT ] = NONE;
    rms[BATHROOM].exits_to_room[RIGHT] = NONE;
    rms[BATHROOM].story.assign(bathroom_monster);

    rms[MASTERBEDROOM].description.assign("master bedroom");
    rms[MASTERBEDROOM].exits_to_room[FRONT] = NONE;
    rms[MASTERBEDROOM].exits_to_room[BACK ] = LIVINGROOM;
    rms[MASTERBEDROOM].exits_to_room[LEFT ] = NONE;
    rms[MASTERBEDROOM].exits_to_room[RIGHT] = NONE;
    rms[MASTERBEDROOM].story.assign(masterbedroom);

    rms[CORRIDOR].description.assign("corridor");
    rms[CORRIDOR].exits_to_room[FRONT] = DININGROOM;
    rms[CORRIDOR].exits_to_room[BACK ] = LIVINGROOM;
    rms[CORRIDOR].exits_to_room[LEFT ] = CHILDROOM;
    rms[CORRIDOR].exits_to_room[RIGHT] = STAIRSDOWN;
    rms[CORRIDOR].story.assign(corridor);

    rms[CHILDROOM].description.assign("child's room");
    rms[CHILDROOM].exits_to_room[FRONT] = NONE;
    rms[CHILDROOM].exits_to_room[BACK ] = CORRIDOR;
    rms[CHILDROOM].exits_to_room[LEFT ] = NONE;
    rms[CHILDROOM].exits_to_room[RIGHT] = NONE;
    rms[CHILDROOM].story.assign(childroomnote);

    rms[STAIRSDOWN].description.assign("stairs down");
    rms[STAIRSDOWN].exits_to_room[FRONT] = BASEMENT;
    rms[STAIRSDOWN].exits_to_room[BACK ] = CORRIDOR;
    rms[STAIRSDOWN].exits_to_room[LEFT ] = NONE;
    rms[STAIRSDOWN].exits_to_room[RIGHT] = NONE;
    rms[STAIRSDOWN].story.assign("Its a dark place but enough light to keep walking");
    
    rms[BASEMENT].description.assign("basement");
    rms[BASEMENT].exits_to_room[FRONT] = NONE;
    rms[BASEMENT].exits_to_room[BACK ] = STAIRSDOWN;
    rms[BASEMENT].exits_to_room[LEFT ] = NONE;
    rms[BASEMENT].exits_to_room[RIGHT] = NONE;
    rms[BASEMENT].story.assign("the place was filled with bear treaps and a lot of dead pigs hanging. The whole place was stinking with flies all over the place");

    rms[DININGROOM].description.assign("dining room");
    rms[DININGROOM].exits_to_room[FRONT] = KITCHEN;
    rms[DININGROOM].exits_to_room[BACK ] = CORRIDOR;
    rms[DININGROOM].exits_to_room[LEFT ] = SWIMMINGPOOL;
    rms[DININGROOM].exits_to_room[RIGHT] = NONE;
    rms[DININGROOM].story.assign("the room looks pretty empty.keep moving on");

    rms[SWIMMINGPOOL].description.assign("swimming pool");
    rms[SWIMMINGPOOL].exits_to_room[FRONT] = SHED;
    rms[SWIMMINGPOOL].exits_to_room[BACK ] = DININGROOM;
    rms[SWIMMINGPOOL].exits_to_room[LEFT ] = NONE;
    rms[SWIMMINGPOOL].exits_to_room[RIGHT] = NONE;
    rms[SWIMMINGPOOL].story.assign(swimmingpool);

    rms[KITCHEN].description.assign("kitchen");
    rms[KITCHEN].exits_to_room[FRONT] = BACKYARD;
    rms[KITCHEN].exits_to_room[BACK ] = DININGROOM;
    rms[KITCHEN].exits_to_room[LEFT ] = LAUNDRY;
    rms[KITCHEN].exits_to_room[RIGHT] = STOREROOM;
    rms[KITCHEN].story.assign("The windows rattled vigorously from the howling wind, as though they were about to fall out of the frames which were made from rotting wood being eaten away by wood worm. A few potted plants lay next to the door and across the table there were some half rotted apples.");

    rms[LAUNDRY].description.assign("laundry room");
    rms[LAUNDRY].exits_to_room[FRONT] = NONE;
    rms[LAUNDRY].exits_to_room[BACK ] = KITCHEN;
    rms[LAUNDRY].exits_to_room[LEFT ] = NONE;
    rms[LAUNDRY].exits_to_room[RIGHT] = NONE;
    rms[LAUNDRY].story.assign("I looked up and noticed that I was right in front of the laundry. A shattered mirror hung on the wall.There was a torch light hanging in the room");

    rms[SHED].description.assign("shed");
    rms[SHED].exits_to_room[FRONT] = NONE;
    rms[SHED].exits_to_room[BACK ] = SWIMMINGPOOL;
    rms[SHED].exits_to_room[LEFT ] = NONE;
    rms[SHED].exits_to_room[RIGHT] = NONE;
    rms[SHED].story.assign("The shed was filled with cobwebs and dust. Within the dust I found some shotgun ammo. I immediately load the gun up to fight the monster in the bathroom next");

    rms[STOREROOM].description.assign("storage room");
    rms[STOREROOM].exits_to_room[FRONT] = NONE;
    rms[STOREROOM].exits_to_room[BACK ] = KITCHEN;
    rms[STOREROOM].exits_to_room[LEFT ] = NONE;
    rms[STOREROOM].exits_to_room[RIGHT] = NONE;
    rms[STOREROOM].story.assign("All that was in sight was a damp, old looking door at the far end of the room, so I began to walk towards it. I find a shotgun on a table but there were no shells in it");

    rms[BACKYARD].description.assign("backyard");
    rms[BACKYARD].exits_to_room[FRONT] = NONE;
    rms[BACKYARD].exits_to_room[BACK ] = KITCHEN;
    rms[BACKYARD].exits_to_room[LEFT ] = NONE;
    rms[BACKYARD].exits_to_room[RIGHT] = NONE;
    rms[BACKYARD].story.assign("I crept into the gardenit was like anover grown rainforest. The gardengate was hanging off its hinges.As I raced forward theground in the house was green with mouldand so werethe walls.I find an axe hanging from the door with blood stains on it");


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
    nns[KEY].description = "I find a key on the shelf";
    nns[KEY].on_hand = false;
    nns[KEY].location = MASTERBEDROOM;

    nns[APPLE].word = "apple";
    nns[APPLE].code = APPLE;
    nns[APPLE].description = "I find an apple on the table";
    nns[APPLE].on_hand = false;
    nns[APPLE].location = KITCHEN;

    nns[AXE].word = "axe";
    nns[AXE].code = AXE;
    nns[AXE].description = "I got an axe";
    nns[AXE].on_hand= false;
    nns[AXE].location = BACKYARD;

    nns[TORCH].word = "torch";
    nns[TORCH].code = TORCH;
    nns[TORCH].description = "I find a torch";
    nns[TORCH].on_hand = false;
    nns[TORCH].location = LAUNDRY;

    nns[SHOTGUN].word = "shotgun";
    nns[SHOTGUN].code = KEY;
    nns[SHOTGUN].description = "I find a shotgun";
    nns[SHOTGUN].on_hand = false;
    nns[SHOTGUN].location = STOREROOM;

    nns[SHOTGUNAMMO].word = "shotgun ammo";
    nns[SHOTGUNAMMO].code = SHOTGUNAMMO;
    nns[SHOTGUNAMMO].description = "I find some shotgun ammo";
    nns[SHOTGUNAMMO].on_hand = false;
    nns[SHOTGUNAMMO].location = SHED;

    nns[DININGCODE].word = "dining room code";
    nns[DININGCODE].code = DININGCODE;
    nns[DININGCODE].description = "I find a code to open the dining room";
    nns[DININGCODE].on_hand = false;
    nns[DININGCODE].location = BASEMENT;

    nns[BEDROOMCODE].word = "bedroom code";
    nns[BEDROOMCODE].code = BEDROOMCODE;
    nns[BEDROOMCODE].description = "I find the key to the bedroom";
    nns[BEDROOMCODE].on_hand = false;
    nns[BEDROOMCODE].location = BATHROOM;

    
}
// ------------------------------------------------------------------------------------------------
void look_around(int loc, room *rms, word *dir, /* Added parameter */ noun *nns)
{
    cout << rms[loc].story << endl;
    int i;
 
    for(i = 0; i < DIRS; i++)
    {
        if(rms[loc].exits_to_room[i] != NONE)
        {
            std::cout << "There is an exit " << dir[i].word << " to the " << rms[rms[loc].exits_to_room[i]].description << "." << endl;
        }
    }
 
    // Added code
    // The look command should check which objects (nouns) are in the current room and report them to the player.
    
}

void inventory(noun *nns)
{
    int i;
    for(i = 0; i < NOUNS; i++)
    {
        if(nns[i].on_hand == true)
        {
            std::cout << "U have the " << nns[i].word << endl; 
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

    if(VERB_ACTION == "1" )
    {
        look_around(loc, rms, dir, /* Added parameter nns */ nns);
        return true;
    }

    else if(VERB_ACTION == "w")
    {
        wd1 = "FRONT";
    }
    else if(VERB_ACTION == "d")
    {
        wd1 = "RIGHT";
    }
    else if(VERB_ACTION == "a")
    {
        wd1 = "LEFT";
    }
    else if(VERB_ACTION == "s")
    {
        wd1 = "BACK";
    }

    else if(VERB_ACTION == "2")
    {
        inventory(nns);
        return true;
    }

    else
    {
        cout << "Please stick to the following commands\nType 1 for looking at rooms or objects around \nType 2 for accessing your inventory\nType w for moving forward \nType a for moving to the left\nType s for moving backwards  \nType d for moving to the right";
    }
    // Added code
    // ....


    int i;
    for(i = 0; i < DIRS; i++)
    {
        if(wd1 == dir[i].word)
        {
            if(loc == CORRIDOR && dir[i].code == FRONT && nns[DININGCODE].on_hand == false)
            {
                std::cout << "this door is locked, I need to find a passcode to open it";
            }
            else if(loc == LIVINGROOM && dir[i].code == BACK && nns[KEY].on_hand == true)
            {
                std::cout << R"(I made it to the entrance again but this time I'm exiting the place. I ran as fast as i could and stopped at one part to take a look behind hearing her voice again.....
       ^  ^  ^   ^      ___I_      ^  ^   ^  ^  ^   ^  ^
      /|\/|\/|\ /|\    /\-_--\    /|\/|\ /|\/|\/|\ /|\/|\
      /|\/|\/|\ /|\   /  \_-__\   /|\/|\ /|\/|\/|\ /|\/|\
      /|\/|\/|\ /|\   |[]| [] |   /|\/|\ /|\/|\/|\ /|\/|\                                              
      _____ _____ _____    _____ _____ ____  
     |_   _|  |  |   __|  |   __|   | |    \ 
       | | |     |   __|  |   __| | | |  |  |
       |_| |__|__|_____|  |_____|_|___|____/ 
                                                

                )";
            }
            else if(loc == LIVINGROOM && dir[i].code == RIGHT && nns[BEDROOMCODE].on_hand == false)
            {
                std::cout << "this door is locked, I need to find a code to unlock it";
            }
            else if(loc == LIVINGROOM && dir[i].code == LEFT && nns[SHOTGUN].on_hand == false)
            {
                std::cout << "You see a giant monster in the bathroom. You decide to close the door ";
            }
            else if(loc == CORRIDOR && dir[i].code == FRONT && nns[DININGCODE].on_hand == false)
            {
                std::cout << "you need a code to open this door";
            }
            else if(loc == DININGROOM && dir[i].code == LEFT && nns[AXE].on_hand == false)
            {
                std::cout << "there is a monster in the swimming pool and you do not have a weapon to kill it";
            }
            else if(loc == KITCHEN && dir[i].code == FRONT && nns[TORCH].on_hand == false)
            {
                std::cout << "the backyard is too dark I need a torch to go outside";
            }
            else if(loc == KITCHEN && dir[i].code == RIGHT && nns[AXE].on_hand == false)
            {
                std::cout << "the door seems to be locked I need an axe to break it";
            }
                


            else if(rms[loc].exits_to_room[dir[i].code] != NONE)
            {
                
                loc = rms[loc].exits_to_room[dir[i].code];
                look_around(loc, rms, dir, /* Added parameter nns */ nns);
                std::cout << "I am now in the " << rms[loc].description << "." << endl;
                // Added code. Special locked rooms
                

                if(loc == MASTERBEDROOM && nns[BEDROOMCODE].on_hand == true)
                {
                    nns[KEY].on_hand = true;
                    std::cout << "U HAVE OBTAINED A KEY";
                }
                // ....
                

                if (loc == BASEMENT)
                {
                    nns[DININGCODE].on_hand = true;
                    std::cout << "you have found a passcode for the dining room in a note";
                }

                if (loc == CHILDROOM)
                {
                    std::cout << "i found a way to get out but im not sure if i can make it. the monster in the bathroom is guarding the code to unlock the bedroom and once I get the key in the bedroom I will be free of this cursed house.";
                }

                if (loc == KITCHEN)
                {
                    nns[APPLE].on_hand = true;
                    std::cout << nns[AXE].description;
                }
                if (loc == LAUNDRY)
                {
                    nns[TORCH].on_hand = true;
                    std::cout << nns[TORCH].description;
                }
                if (loc == STOREROOM)
                {
                    nns[SHOTGUN].on_hand = true;
                    std::cout << nns[SHOTGUN].description;
                }
                if (loc == BACKYARD)
                {
                    nns[AXE].on_hand = true;
                    std::cout << nns[AXE].description;
                }
                if (loc == SHED)
                {
                    nns[SHOTGUNAMMO].on_hand = true;
                    std::cout << nns[SHOTGUNAMMO].description;
                }
                if (loc == BATHROOM)
                {
                    nns[BEDROOMCODE].on_hand = true;
                    std::cout << nns[SHOTGUNAMMO].description;

                }
                return true;
            }
            else
            {
                std::cout << "I cannot go that way" << endl;
                return true;
            }
        }
    }
    

 
    // Added code
    // Actions for usage of VERB OPEN
    // ....
 
    return false;
}


int main()
{   

    string start;
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
    


    int i = 0;
    if(i==0)
    {
        std::cout << R"(
This game is a text based game 
Type 1 for looking at rooms or objects around
Type 2 for accessing your inventory
Type w for moving forward 
Type a for moving to the left
Type s for moving backwards  
Type d for moving to the right
The commands are number/letter specific and can be accessed anytime in the game by typing HELP.
ENJOY THE GAME...)" << '\n';
        sleep(10);
        string intro = "I stand there in front of an old abandoned house, lost. The house was rugged and broken down. I was suprised it was stil standing. I crept up the long wooden stairs and reached the door. I do not remember how I ended up here but i can hear the voice of my girlfriend calling me in....";
        cout <<endl << endl << intro << endl << endl ;
        sleep(12);
        std::cout << R"(


         (
                                    //  ____________ _____  ___   _   __ ____________ _____ _____   //
           )                        //  | ___ \ ___ \  ___|/ _ \ | | / / |  ___| ___ \  ___|  ___|  //
         ( _   _._                  //  | |_/ / |_/ / |__ / /_\ \| |/ /  | |_  | |_/ / |__ | |__    //
          |_|-'_~_`-._              //  | ___ \    /|  __||  _  ||    \  |  _| |    /|  __||  __|   //
       _.-'-_~_-~_-~-_`-._          //  | |_/ / |\ \| |___| | | || |\  \ | |   | |\ \| |___| |___   //
   _.-'_~-_~-_-~-_~_~-_~-_`-._      //  \____/\_| \_\____/\_| |_/\_| \_/ \_|   \_| \_\____/\____/   //
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~     //                                                              //
    |  []  []   []   []  [] |                                                                 
    |           __    ___   |   
  ._|  []  []  | .|  [___]  |_._._._._._._._._._._._._._._._._.  
  |=|________()|__|()_______|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=| 
^^^^^^^^^^^^^^^ === ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^  
     ___________   ===   
    <_A GAME BY_>    === 
    <__MANOJ____>      ===     
        ^|^              ===
         |                 ===

                                        TYPE START TO CONTINUE




        )" << '\n';

    cin >> start;
    
    int location = ENTRANCE;
    word_1 = "1";

    parser(location, word_1, directions, verbs, rooms, /* Added parameter */ nouns);
    
    
    }
    
    

    int location = ENTRANCE;
    
    while(word_1 != "6")
    {
        std::cout << endl;
        std::cin >> word_1;
        std::cout << "\n\n";


    
        if(word_1 != "6")
        {
            parser(location, word_1, directions, verbs, rooms, /* Added parameter */ nouns);
        }
    }
    return 0;

}