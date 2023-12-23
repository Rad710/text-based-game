#include"Map.h"
#include"Room.h"
#include"Bolt.h"
#include"Consumable.h"
#include"Crossbow.h"
#include"Sword.h"
#include"BlockedWay.h"
#include"Key.h"

Map::Map()
{
    rooms.reserve(25);
    //Room 0
    rooms.push_back(Room("Entrance", "You find yourself in a strange room with "
        "torches lighting up the place. Infront of you there is a giant metal "
        "gate with three key slots. There's light coming from behind, showing "
        "a path 'backwards'."
        , { new Sword("Old sword", 20, Condition::rusty,
            "There is an 'Old sword' in the middle of the room.") },
        { new Enemy(20, 5, true, EnemyType::undead, std::make_unique<Sword>(
        "Broken sword", 5, Condition::broken), "Undead",
        "To your left stands an 'Undead' ready to attack you.",
        "A weak-looking 'Undead', wielding a broken sword.", "Eughhhh!") }));
    //Room 1
    rooms.push_back(Room("Hill", "You stand on a small hill with an orange "
        "tree near you. To the 'left' there's a small black house. "
        "'Forward' there is a foggy stone path, but you can't see where it takes "
        "you. To your 'right', stairs that take you to a cavern.",
        { new Consumable("Ripe orange", 20, "On a branch of the tree "
        "you see a 'Ripe orange'."), new Consumable("Green orange",
            10, "There's a 'Green orange' next to your feet.") }, {}));
    //Room 2
    rooms.push_back(Room("Old House", "You are in the living room. The place seems "
        "to have been abandoned a long time ago. In front of you there's a table "
        "and behind the table the fireplace is falling apart. To your "
        "'left' there's a stairway that leads downwards. To the 'right' you "
        "can go to what looks like a kitchen.", { new Consumable("Moldy bread",
            -20, "Inside a basket on the table you can see a 'Moldy bread'."),
        new Consumable("Old wine", 20, "On the table there's an 'Old wine' bottle."
        ) }, { new Enemy(100, 15, false, EnemyType::warrior,
            std::make_unique<Sword>("Butterfly knife", 30, Condition::goodCondition),
            "Grey warrior", "On a chair next to the table, a 'Grey warrior' is "
            "doing cool tricks with a butterfly knife.", "A warrior with a grey "
            "armor and an eagle emblem on his chest plate.", "I'll kill you, "
            "filthy casual!", "Hmmm...", "Really?...") }));
    //Room 3
    rooms.push_back(Room("Basement", "After going down the stairs you reach a "
        "basement. The place looks like a disco, with a disco ball and even fog "
        "machines. Looks like someone is having a party.", {}, { new Enemy(20, 10,
        true, EnemyType::skeleton, nullptr, "Skeleton", "West of the stairway a 'Skeleton' is break "
        "dancing.", "A crazy looking skeleton.", "Shake them bones!"),
        new Enemy(20, 10, true, EnemyType::skeleton, std::make_unique<Bolt>(
         "Bolts", 3), "Cringey skeleton", "To your left a 'cringey skeleton' is default "
        "dancing.", "A silly little skeleton.", "Are you seeing those moves?!"),
        new Enemy(20, 10, true, EnemyType::skeleton, std::make_unique<Bolt>(
        "Bolts", 5), "Party hat skeleton", "In the middle of the room, a 'Party hat "
        "skeleton' is aggressively staring at you.", "A skeleton wearing a ridiculous "
        "party hat. He seems upset at you.", "I don't remember inviting you"), new Enemy(20, 10, true,
        EnemyType::skeleton, std::make_unique<Sword>("Skeleton's knife", 40, Condition::rusty),
        "Warrior skeleton", "Standing on an shelf the 'Warrior skeleton' is "
        "sharpening his knife.", "A skeleton armed with a crossbow.", "Luckily I brought"
        " my trusty knife"), new Enemy(20, 10, true, EnemyType::skeleton,
        nullptr, "Breakdancer skeleton", "On the northwest corner of the room a "
        "'Breakdancer skeleton' is living up to its name.", "His moves looks fucking "
        "cool, are you seeing this? Wow, unbelievable!", "Get ready to dance!") }));
    //Room 4
    rooms.push_back(Room("Kitchen", "You arrived to the kitchen. The place is "
        "crumbling, and there's not a roof anymore. Still, the beautiful "
        "marble counter and an old refrigerator stay intact.", { new Sword("Abandoned sword", 50,
        Condition::goodCondition, "On the counter you observe a nice looking "
        "'Abandoned sword'.") }, { new Enemy(40, 20, true, EnemyType::orc,
        nullptr, "Orc", "East of the counter an 'Orc' is contemplating the sword. "
        "It seems annoyed by your interruption.", "It's an orc.", "Hey! It's my "
        "precious!"), new Enemy(50, 20, true, EnemyType::orc, std::make_unique
        <Consumable>("Cake", 30), "Fat orc", "An extremely 'Fat orc' is in front "
        "of the refrigerator eating anything he finds. It's angry at the prospect "
        "of having to share food with you.", "A fat orc.", "My food only") }));
    //Room 5
    rooms.push_back(Room("Cavern", "The walls of the cavern are filled with primitive "
        "painting, probably made by cavemen a long time ago. 'Forward' there's a tunnel "
        "with light at the end. 'Right' there's a dark path that leads even deeper into "
        "the ground.", {}, {}));
    //Room 6
    rooms.push_back(Room("Golden Room", "A place made of pure gold. The walls are "
        "so shiny they hurt your eyes.", { new Key("Golden key", "On a pedestal "
        "the 'Golden key' glitters.") }, {}));

    //Room 7
    rooms.push_back(Room("Troll's Den", "You arrived at a troll's house. The horrible"
        " smell makes it hard to breath. Strangely enough, a beautiful gold door "
        "can be seen 'forward'.", { new Consumable("Bottled poison", -95, "On the floor "
        "to your left, a strong 'Bottled poison' is ready to cause harm.") }, { new Enemy(
        95, 1, false, EnemyType::troll, std::make_unique<BlockedWay>(rooms[6],
        "forward"), "Obese troll", "Blocking the door with its massive body "
        "an 'Obese troll' is in front of you.", "An unhealthy and overweight "
        "troll. Trolls are known to eat anything thrown at them.", "Get closer so I can beat the living crap outta you", "Zzzzzz",
        "Who interrupts my nap?") }));

    //Room 8
    rooms.push_back(Room("Ravine", "You are at the west border of a ravine. The sun "
        "comes from above. Still, it's so deep that you can't see the end of the hole. "
        "But you can hear a river ravaging at the bottom. To the 'left' there's a "
        "path that takes you to a green field.", {},
        { new Enemy(100, 40, false, EnemyType::golem, std::make_unique<Consumable>(
            "Red gem", 100), "Rock golem",  "At the northeast a "
        "'Rock golem' stands tall, curiously looking down the ravine.",
        "A golem made of rock, it's hard composition makes it resilient.",
        "Why you make me do this?", "You also came to look the ravine? :D",
        "I'll have to kill you now :c") }));
    //Room 9
    rooms.push_back(Room("Garden", "You arrived to a magnificent garden, filled "
        "with flowers of all types. It's truly quite the view. There's a greenhouse "
        "to your 'left'. 'Forward', you see a graveyard.", {},
        { new Enemy(150, 45, false, EnemyType::warrior, std::make_unique<Sword>("Legendary sword", 100,
        Condition::goodCondition),"Legendary warrior", "Sitting on top of the green grass a "
        "'Legendary warrior' is meditating.", "The warrior's aura tells you "
        "it will make for a fierce opponent. Still, he seems rather peaceful.",
        "Do you dare challenge me, boy?", "...", "Should have read my description. Smh") }));
    //Room 10
    rooms.push_back(Room("Greenhouse", "A placed filled with dense vegetation. "
        "Seems like this placed wasn't taken care of for a long time. To the 'right' "
        "there's a path to the outside.",
        { new Consumable("Red apple", 35, "On a basket to your left you see a "
        "'Red apple'."), new Consumable("Green apple", 35, "On the branch of a "
        "small apple tree there's a 'Green apple'."), new Consumable(
        "Giant watermelon", 90, "In front of you on the floor a 'Giant watermelon "
        "is ready to be eaten.") }, { new Enemy(40, 25, true, EnemyType::orc,
        nullptr, "Fat orc", "A 'Fat orc' is eating all the fruits. He stops and "
        "gets ready to fight you.", "You can see fruits leftovers all over him.",
        "What kind of man interrupts someone's meal?") }));
    //Room 11
    rooms.push_back(Room("Graveyard", "A huge graveyard, filled with tombstones and "
        "many realistic looking statues.", {}, { new Enemy(50, 20, false, EnemyType::golem,
        std::make_unique<Consumable>("White gem", 75), "Small golem", "Among the statues a 'Small golem' stays so incredibly still that it becomes "
        "invisible to the eye.", "A small golem that thinks he's invisible.", "If I "
        "kill you then you can't see me anymore", "I'm not here", "How can you see me?")
        , new Enemy(20, 10, true, EnemyType::undead, nullptr, "Undead",
        "Behind an angle's statue an 'Undead' is ready to ambush you.", "The undead "
        "looks almost completely rotten.", "Eughhhh"), new Enemy(20, 10, true,
        EnemyType::undead, nullptr, "Undead", "From behind an 'Undead' comes to "
        "attack you.", "The undead looks completely rotten.", "Eughhhh"),
        new Enemy(20, 25, true, EnemyType::undead, std::make_unique<Sword>("Undead's sword", 50,
        Condition::goodCondition),"Big undead", "A 'Big undead' stands menacingly "
        "over a tombstone with a sword.", "A very tall and ripped Undead, hard to kill.",
        "Eughhhh"), new Enemy(20, 10, true, EnemyType::skeleton, nullptr, "Skeleton",
        "A 'Skeleton' on the middle of the graveyard is ready to attack you.",
        "A skeleton, known to be aggressive to humans.", "I was in need of a rib bone")
        , new Enemy(20, 10, true, EnemyType::skeleton, nullptr, "Skeleton", "On one "
        "wall a 'Skeleton' is angrily looking at you.", "A very angry skeleton.",
        "You are not welcomed here") }));
    //Room 12
    rooms.push_back(Room("Warrior's Mausoleum", "An elegant mausoleum. On the front wall "
        "a writing reads: \"To our dear friend, great warrior and a good hunter with "
        "the crossbow, rest in peace.\". In front of you see the coffin of the deceased warrior.",
        { new Key("Black key", "On the floor there is a 'Black key'."),
        new Crossbow("Crossbow", 40, 5, "On top of the coffin you see the 'Crossbow' "
        "that once belonged to the warrior. He won't be needing it anytime soon lmao.") },
        {}));
    //Room 13
    rooms.push_back(Room("Ruins of a Temple", "A place that where once many people "
        "gathered for worshipping, now completely destroyed by time. A corridor "
        "takes you 'forward' to the altar. To the 'right' another corridor takes "
        "you to a poorly lit room.", { new Consumable("Health potion", 100,
        "On a shelft to the northeast of the room, there's a bright red 'Health "
        "potion'.") }, { new Enemy(100, 30, true, EnemyType::undead, nullptr, "Armored undead",
        "The 'Armored undead' that is sitting in a bench sees you.", "The undead "
        "is wearing a black leather armor.", "Eughhhh") }));

    //Room 14
    rooms.push_back(Room("Bridge", "The fog disappears, and 'forward' there's a small bridge. "
        "To your 'left' a path takes you to a forest. To the 'right' you see a shrine.", {},
        { new Enemy(200, 25, false, EnemyType::troll, std::make_unique<BlockedWay>(rooms[13],
        "forward"), "Rock troll", "Blocking the bridge, "
        "a 'Rock troll' is in front of you.", "A troll with skin made of rock. Trolls are known to eat anything thrown at them.",
        "I'll rock you", "This is my bridge and you shall not pass!",
        "I'll have to eat you then") }));
    //Room 15
    rooms.push_back(Room("Ruined house", "After going through the forest you arrive at "
        "a ruined house and go inside. The only thing that remains inside is a table with a basket on top. A dark hole on your 'left' takes you down. "
        "While a wood ladder to the 'right' takes you to the attic.", {
        new Consumable("Corn can", 25, "On the basket there's a 'Corn can'."),
        new Consumable("Old cookie", -15, "Next to the basket you see a very "
        "'Old cookie'.") }, {}));
    //Room 16
    rooms.push_back(Room("Attic", "A boring empty attic. There's nothing to see here. "
        " Only spiders live here now.", {}, {}));
    //Room 17
    rooms.push_back(Room("Dungeon", "After going down the hole you are inside a "
        "dungeon. The place is so dark that you can barely see something even though "
        "you have a lamp.", { new Consumable("Legendary venom", -125, "Inside the coffin "
        "you see a bottle of 'Legendary venom' of an ancient snake.") }, { new Enemy(
        70, 25, false, EnemyType::undead, nullptr, "Sleepy undead", "Inside the coffin "
        "there's a 'Sleepy undead'.", "A very tired undead, only wants to sleep in peace.",
        "Eughhhh", "Zzzzzz", "Eughhhh!!!") }));
    //Room 18
    rooms.push_back(Room("Ancient Shrine", "An forgone sanctuary. You see there are "
        "many offerings to the gods on the floor.", { new Consumable("Banana",
        10, "There's a 'Banana' on the floor in front of you."),
        new Consumable("Melon",
        10, "There's a 'Melon' on a small stone.") }, { new Enemy(100, 30, true,
        EnemyType::skeleton, nullptr, "Giant skeleton", "For some reason, on the ceiling "
        "there is a goddamn 'Giant skeleton'.", "A colossal skeleton, this one looks"
        " very dangerous.", "Huehuehue, macaco!") }));
    //Room 19
    rooms.push_back(Room("Storage room", "An old storage room, used in the past to "
        "store goods. Now little remains here.", { new Consumable("Old cheese", -5,
        "On the wet floor, you see what looks like an 'Old cheese'.") }, { new
        Enemy(100, 30, true, EnemyType::warrior, nullptr, "Tiny warrior",
        "On the northwest dark corner of the storage room, a 'Tiny warrior' is hidden.",
        "A very tiny warrior, doesn't have a weapon so he fights with his bare fists.",
        "Wanna fight?") }));
    //Room 20
    rooms.push_back(Room("Altar Chamber", "The chamber is falling apart, there's no ceiling anymore. "
        "Still, the room retains its sacred aura.", { new Key("Silver key", "On the altar "
        "a 'Silver key' is somehow still intact.") }, { new Enemy(100, 35, true,
        EnemyType::golem, std::make_unique<Consumable>("Silver gem", 100),
        "Protector golem", "Next to the altar, a 'Protector golem' is defending the key.",
        "A fierce stone golem, its sole purpose is to protect the key.",
        "You will never escape this land") }));

    rooms[0].setBackwards(rooms[1]);
    rooms[1].setBackwards(rooms[0]);
    rooms[1].setLeft(rooms[2]);
    rooms[2].setBackwards(rooms[1]);
    rooms[2].setLeft(rooms[3]);
    rooms[3].setBackwards(rooms[2]);
    rooms[4].setBackwards(rooms[2]);
    rooms[2].setRight(rooms[4]);
    rooms[5].setBackwards(rooms[1]);
    rooms[1].setRight(rooms[5]);
    rooms[5].setRight(rooms[7]);
    rooms[6].setBackwards(rooms[7]);
    rooms[7].setBackwards(rooms[5]);
    rooms[8].setBackwards(rooms[5]);
    rooms[5].setForward(rooms[8]);
    rooms[9].setBackwards(rooms[8]);
    rooms[8].setLeft(rooms[9]);
    rooms[10].setBackwards(rooms[9]);
    rooms[9].setLeft(rooms[10]);
    rooms[11].setBackwards(rooms[9]);
    rooms[9].setForward(rooms[11]);
    rooms[10].setRight(rooms[12]);
    rooms[12].setBackwards(rooms[10]);
    rooms[13].setBackwards(rooms[14]);
    rooms[14].setBackwards(rooms[1]);
    rooms[1].setForward(rooms[14]);
    rooms[15].setBackwards(rooms[14]);
    rooms[14].setLeft(rooms[15]);
    rooms[16].setBackwards(rooms[15]);
    rooms[15].setRight(rooms[16]);
    rooms[17].setBackwards(rooms[15]);
    rooms[15].setLeft(rooms[17]);
    rooms[18].setBackwards(rooms[14]);
    rooms[14].setRight(rooms[18]);
    rooms[13].setRight(rooms[19]);
    rooms[19].setBackwards(rooms[13]);
    rooms[20].setBackwards(rooms[13]);
    rooms[13].setForward(rooms[20]);
}
