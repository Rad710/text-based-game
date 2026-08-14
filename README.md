# The Fallen Kingdom

A text adventure in C++. You wake up in a strange land with a lamp that is
slowly burning out, and you have to find three keys and open the gate at the
Entrance before it does.

Written in 2021 as a project for a C++ OOP course. It runs as a Windows console
program, and also compiles to WebAssembly and runs in a browser.

```
The Troll's Den

You arrived at a troll's house. The horrible smell makes it hard to breath.
Strangely enough, a beautiful gold door can be seen 'forward'. On the floor
to your left, a strong 'Bottled poison' is ready to cause harm. Blocking the
door with its massive body an 'Obese troll' is in front of you.

>> Command: pick bottled poison

You picked up 'Bottled poison'.

>> Command: throw bottled poison

You threw 'Bottled poison'. It's not very useful...
Aaaand the 'Obese troll' ate it. You truly are fantastic...
  - "Who interrupts my nap?"

The 'Obese troll' received 95 points of damage.
The 'Obese troll' died.

Wait. It actually worked?
```

## The game

21 rooms, 24 enemies across six species, three keys. Everything is typed:

| command | |
| --- | --- |
| `help` | list the commands |
| `inspect <thing>` | also `inspect room` and `inspect inventory` |
| `pick <item>` | take something in the room |
| `equip` / `unequip <weapon>` | swap what you are holding |
| `attack <enemy>` | hit it with whatever you have |
| `use <item>` | eat, drink, reload, unlock |
| `go <direction>` | `left`, `forward`, `right`, `backwards` |
| `talk <enemy>` | they answer differently once provoked |
| `throw <item>` | into the room, or at something |
| `die` | give up |

Every action burns a turn of lamp fuel, and you start with a hundred, so
wandering has a cost. Enemies that are not aggressive leave you alone until you
hit them, which means you can often walk into a room, grab what you came for,
and walk out having taken one hit instead of five.

Some things worth finding out the hard way: swords wear out and break, a rusty
one faster than a good one; the crossbow needs bolts and the skeletons in the
Basement carry them; trolls eat anything thrown at them, including things that
disagree with them; and not everything edible is good for you.

## Building

**Visual Studio.** Open `Sandbox.sln` and build. x64 or Win32, toolset v142.

**Any compiler.** No dependencies beyond the standard library:

```
g++ -std=c++17 -O2 TextBasedGame/*.cpp -o game
```

**Browser.** `./build-web.sh` compiles it to WebAssembly with emscripten and
writes `web/dist/game.js` and `web/dist/game.wasm` — about 113 KB gzipped
between them. The UI is left to whatever page hosts it; `web/README.md`
documents the small contract that page has to implement.

## How it is put together

`Item` is the abstract base for everything you can carry, with `Weapon` in
between for the things that deal damage:

```
Item ── Weapon ── Sword          durability, breaks after enough hits
     │         └─ Crossbow       ammo count
     ├─ Bolt                     stacks, reloads a Crossbow
     ├─ Consumable               heals, or hurts if the number is negative
     ├─ Key                      three of them open the gate
     └─ BlockedWay               not an item you hold; a door a troll is
                                 sitting on, dropped when it dies
```

`Room` owns its items and enemies through `unique_ptr` and links to its
neighbours through four raw pointers, one per direction. `Map` builds all 21
rooms in its constructor and wires the graph. `Player` holds the inventory, the
equipped weapon, and a pointer to the current room. `GameInterface` reads a
line, splits it into a verb and a target, and dispatches.

`BlockedWay` is the one piece worth pointing at: a troll carries a door as its
"drop", so killing it makes the room hand back a connection that did not exist
before. That is how both gated areas open up.

Console I/O is isolated behind `TextBasedGame/Platform.h`, which is the only
thing that differs between the native and WebAssembly builds.
