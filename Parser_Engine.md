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
│  N|S|E|W|D)     │
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
│ • D (door)      │
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
   - **What happens**: Returns NULL, calls `cleanup_early`, then exits

3. **Memory Problems** (`alloc_and_init_all`)
   - Computer runs out of memory
   - **What happens**: Shows error message, calls `cleanup_early`, exits program

4. **Settings Problems** (`config_parser.c`, `parse_settings.c`, `parse_texture.c`, `parse_colors.c`)
   - Missing wall textures or wrong color values
   - **What happens**: Calls `cleanup_early`, then exits

5. **Map Layout Problems** (`map_parser.c`, `populate_map.c`)
   - Map too small or has invalid characters
   - **What happens**: Calls `cleanup_early`, then exits

6. **Map Content Problems** (`map_validation.c`, `final_map_validation`)
   - No player, too many players, or player can escape
   - **What happens**: Shows error message, calls `cleanup_later`, then exits

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
   t_texture   textures;          // All wall/floor/door textures
   t_map       map;               // Map info and layout
   t_image     img;               // Main image buffer
   t_mini      minimap;           // Minimap data
   int         doorcount;         // How many doors
   t_door      *doors;            // Array of doors and their states
   double      curr_x;            // Player current X position
   double      curr_y;            // Player current Y position
   double      view_elevation;    // Camera up/down angle
   double      view_direction;    // Which way player faces
   int         midline;           // Screen midline for rendering
} t_game;
```

### Map Information

```c
typedef struct s_map {
   char        **map;             // The actual map layout
   char        *map_path;         // Where the file is
   char        *north_texture_path;  // North wall picture path
   char        *south_texture_path;  // South wall picture path
   char        *east_texture_path;   // East wall picture path
   char        *west_texture_path;   // West wall picture path
   int         sky_color[3];      // Sky color [red, green, blue]
   int         floor_color[3];    // Floor color [red, green,
                                  //  blue]
   int         max_cols;          // Maximum columns in map
   int         max_rows;          // Maximum rows in map
   int         map_start_line;    // First line of map in file
   int         map_last_line;     // Last line of map in file
   int         herocount;         // Number of players found
   double      player_x;          // Player starting X position
   double      player_y;          // Player starting Y position
   t_direction start_direction;   // Which way player faces
} t_map;
```

### Map Rules

1. **Basic Structure**:
   - At least 3 rows tall
   - Can be rectangular or irregular shapes
   - Top and bottom row must be only walls (`1`)
   - All outer boundaries (leftmost and rightmost columns) 
     must be walls (`1`)
   - Interior must be fully enclosed by walls

2. **Characters You Can Use**:
   - `1`: Wall (blocks player)
   - `0`: Floor (player can walk here)
   - `N,S,E,W`: Where player starts and which way they face
   - `D`: Door
   - ` `: Empty space (blocks player. Is shown as a lava tile)

3. **Player Rules**:
   - Must have exactly one player
   - Player must be in an area they can actually reach
   - Player must not be able to "escape" to the edge of the map
