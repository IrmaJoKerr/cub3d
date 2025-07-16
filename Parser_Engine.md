# Cub3D Parser Engine Documentation

## What is this?

The Cub3D Parser Engine reads and checks map files for a 3D game. It works in two steps: first it reads the settings (like textures and colors), then it reads and validates the map layout. It makes sure the map is playable and the player can't escape.

## Main Parts

The parser has 5 main parts:

1. **Setup System** (`initstructs.c`) - Gets memory ready and sets up data
2. **Input Checker** (`parse_path.c`) - Makes sure the file name is correct  
3. **File Reader** (`parser.c`, `config_parser.c`, `map_parser.c`) - Reads the file in two steps
4. **Map Checker** (`map_validation.c`, `map_utils.c`) - Makes sure the map works
5. **Cleanup System** (`cleanup_a.c`, `cleanup_b.c`) - Cleans up when things go wrong

## How the Program Starts

```
┌─────────────────┐
│   Program Start │
│   main(argc,    │
│      argv)      │
└────────┬────────┘
         │
         ▼
┌─────────────────┐
│ Argument Check  │
│ chk_args()      │
│ • Argc == 2     │
│ • .cub ext      │
└────────┬────────┘
         │
         ▼
┌─────────────────┐
│ Path Resolution │
│ get_map_path()  │
│ • Build path    │
│ • Validate file │
└────────┬────────┘
         │
         ▼
┌─────────────────┐
│ Memory Alloc    │
│ alloc_and_init_ │
│ all()           │
│ • Allocate game │
│ • Init structs  │
└────────┬────────┘
         │
         ▼
┌─────────────────┐
│ Parser Engine   │
│ init_game()     │
│ • Two-pass      │
│ • Validation    │
└────────┬────────┘
         │
         ▼
┌─────────────────┐
│ Event Setup     │
│ setup_event_    │
│ hooks()         │
└────────┬────────┘
         │
         ▼
┌─────────────────┐
│ MLX Loop        │
│ mlx_loop()      │
└─────────────────┘
```

## How the File Reader Works

The program reads your `.cub` file in two steps:

### Step 1: Read Settings (`parse_configuration_section`)

```
┌─────────────────┐
│ Open .cub File  │
│ Set map_path    │
└────────┬────────┘
         │
         ▼
┌─────────────────┐    ┌─────────────────┐
│ Read Line by    │───▶│ Skip Empty/     │
│ Line            │    │ Whitespace      │
└────────┬────────┘    └─────────────────┘
         │
         ▼
┌─────────────────┐
│ Check if Map    │
│ Start Line      │
│ (contains 1|0|  │
│  N|S|E|W|H|V)   │
└────────┬────────┘
         │
         ▼ NO
┌─────────────────┐
│ Parse Config    │
│ Settings:       │
│ • N,S,E,W paths │
│ • C (ceiling)   │
│ • F (floor)     │
│ • R (resolution)│
│ • SK (sky)      │
│ • HD/VD (doors) │
└────────┬────────┘
         │
         ▼ YES (Map Start)
┌─────────────────┐
│ Return Map      │
│ Start Line      │
│ Number          │
└─────────────────┘
```

### Step 2: Read Map (`parse_map_section`)

```
┌─────────────────┐
│ Calculate Map   │
│ Dimensions      │
│ • max_rows      │
│ • max_cols      │
│ • Validate chars│
└────────┬────────┘
         │
         ▼
┌─────────────────┐
│ Allocate 2D     │
│ Map Array       │
│ • Uniform sizing│
│ • Debug markers │
└────────┬────────┘
         │
         ▼
┌─────────────────┐
│ Populate Map    │
│ Array           │
│ • Character     │
│   copying       │
│ • Player count  │
└────────┬────────┘
         │
         ▼
┌─────────────────┐
│ Find Player     │
│ Position        │
│ • Set coords    │
│ • Set direction │
└────────┬────────┘
         │
         ▼
┌─────────────────┐
│ Final Map       │
│ Validation      │
│ • Player count  │
│ • Wall borders  │
│ • Flood fill    │
└─────────────────┘
```

## How We Check if the Map Works

### The "Flood Fill" Check

The program uses a smart way to check if the player can escape the map. It's like pouring water from the player's starting position - if the water can reach the edge of the map, then the player can escape (which is bad).

```
┌─────────────────┐
│ Create Test Map │
│ (Copy of main)  │
└────────┬────────┘
         │
         ▼
┌─────────────────┐
│ Start Flood     │
│ Fill from       │
│ Player Position │
└────────┬────────┘
         │
         ▼
┌─────────────────┐
│ Recursive Check:│
│ • Mark visited  │
│ • Check bounds  │
│ • Validate char │
│ • Check edges   │
└────────┬────────┘
         │
         ▼
┌─────────────────┐
│ Return Result:  │
│ • 1 = Valid     │
│ • 0 = Invalid   │
└─────────────────┘
```

## What Happens When Things Go Wrong

### Types of Problems

1. **Wrong Arguments** (`chk_args`)
   - Not enough arguments or wrong file type
   - **What happens**: Program stops immediately with error message

2. **File Problems** (`get_map_path`, `check_valid_file_path`)
   - Can't find the file or can't open it
   - **What happens**: Returns NULL, cleans up, then exits

3. **Memory Problems** (`alloc_and_init_all`)
   - Computer runs out of memory
   - **What happens**: Shows error message, exits program

4. **Settings Problems** (`parse_configuration_section`)
   - Missing wall textures or wrong color values
   - **What happens**: `cleanup_and_return(fd, line, -1)`

5. **Map Layout Problems** (`calculate_map_dimensions`)
   - Map too small or has invalid characters
   - **What happens**: Closes file, returns -1

6. **Map Content Problems** (`final_map_validation`)
   - No player, too many players, or player can escape
   - **What happens**: Shows error message, returns -1

7. **Unexpected Problems** (during file reading)
   - Can't allocate memory for lines or map
   - **What happens**: Immediate cleanup and exit

### How We Clean Up Messes

```
Problem Type → Cleanup Function → What Gets Cleaned
──────────────────────────────────────────────────────
Early Problem → cleanup_early() → • Texture file paths
(Before graphics)                  • Map data
                                  • Game memory

Late Problem  → cleanup_later() → • Graphics textures
(After graphics)                   • Texture file paths
                                  • Map data
                                  • Graphics system
                                  • Game memory

Normal Exit   → cleanup()       → • Everything
                                  • Plus a small delay
```

## The Main Data We Store

### Game Information

```c
typedef struct s_game {
    void        *mlx_ptr;          // Graphics system
    void        *win_ptr;          // Game window
    t_texture   textures;          // All wall/floor pictures
    t_map       map;               // Map info and layout
    int         doorcount;         // How many doors
    double      curr_x, curr_y;    // Where player is now
    double      view_elevation;    // Camera up/down angle
    double      view_direction;    // Which way player faces
} t_game;
```

### Map Information

```c
typedef struct s_map {
    char        **map;             // The actual map layout
    char        **test_map;        // Copy for testing
    char        *map_path;         // Where the file is
    char        *north_texture_path;  // North wall picture path
    char        *south_texture_path;  // South wall picture path
    char        *east_texture_path;   // East wall picture path
    char        *west_texture_path;   // West wall picture path
    char        *sky_texture_path;    // Sky/ceiling picture path
    char        *floor_texture_path;  // Floor picture path
    char        *hdoor_texture_path;  // Horizontal door picture path
    char        *vdoor_texture_path;  // Vertical door picture path
    int         resolution[2];     // Screen size [width, height]
    int         sky_color[3];      // Sky color [red, green, blue]
    int         floor_color[3];    // Floor color [red, green, blue]
    int         max_cols;          // Maximum columns in map
    int         max_rows;          // Maximum rows in map
    bool        map_first_wall;    // First row wall check
    bool        map_last_wall;     // Last row wall check
    int         herocount;         // Number of players found
    double      player_x;          // Player starting X position
    double      player_y;          // Player starting Y position
    t_direction start_direction;   // Which way player faces
} t_map;
```

## Rules for Your Map File

### What Settings You Need

- **Must have**: North, South, East, West wall pictures
- **Optional**: Screen size (defaults to 1920x1080)
- **Optional**: Sky and floor pictures or colors
- **Optional**: Door pictures (horizontal and vertical)

### Map Rules

1. **Basic Structure**:
   - At least 3 rows tall
   - Can be rectangular or weird shapes
   - Top row must be only walls and empty spaces
   - Inside must be completely surrounded by walls

2. **Characters You Can Use**:
   - `1`: Wall (blocks player)
   - `0`: Floor (player can walk here)
   - `N,S,E,W`: Where player starts and which way they face
   - `H`: Horizontal door
   - `V`: Vertical door
   - ` `: Empty space

3. **Player Rules**:
   - Must have exactly one player
   - Player must be in an area they can actually reach
   - Player must not be able to "escape" to the edge of the map

## Debug and Testing Features

### What You'll See in the Output

- Step-by-step progress as it reads your file
- Map size calculations
- Each character as it builds the map
- The "flood fill" test running
- Memory usage tracking

### Special Debug Markers

- Map uses `'9'` characters to mark empty spots 
- Flood-fill test uses `'X'` to mark where it's been
- Clear error messages that tell you exactly what went wrong

## What Could Be Added Later

1. **Door Animation**: Make doors open and close with multiple pictures
2. **Texture Loading**: Actually load the wall pictures into graphics memory  
3. **Better Map Checking**: Handle more complex map shapes


*This guide explains how the map file reader works, from when you start the program until it finishes checking your map.*
