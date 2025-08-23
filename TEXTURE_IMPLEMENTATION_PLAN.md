# Texture Loader Implementation Plan

## PHASE 1: Complete load_all_textures() function

### File: srcs/parsing/cub3D.c
**HYBRID STRATEGY: Strict Map + Engine Features**

```c
void load_all_textures(t_game *game)
{
    printf("🔍 Loading map-specified textures...\n");
    
    // ✅ STRICT: Only map-specified textures (already validated during parsing)
    load_texture(game, game->textures.north_wall, game->map.north_texture_path);
    load_texture(game, game->textures.south_wall, game->map.south_texture_path);
    load_texture(game, game->textures.east_wall, game->map.east_texture_path);
    load_texture(game, game->textures.west_wall, game->map.west_texture_path);
    
    // ✅ OPTIONAL: Sky/floor textures if specified in map
    load_optional_map_textures(game);
    
    printf("🎮 Loading standard door texture...\n");
    
    // 🎯 STANDARD: Door texture (portcullis-style for front/back faces)
    load_door_texture(game);
    
    printf("✅ Texture loading complete: Map textures + Door support\n");
}
```

## PHASE 2: Implement strict map texture loading

### New function: load_optional_map_textures()

```c
void load_optional_map_textures(t_game *game)
{
    // Sky texture: Only load if specified in map
    if (game->map.sky_texture_path)
    {
        if (!check_valid_file_path(game->map.sky_texture_path))
        {
            ft_fprintf(2, "Error: Sky texture specified but not found: %s\n", 
                       game->map.sky_texture_path);
            cleanup_early(game);
            exit(1);
        }
        game->textures.sky = malloc(sizeof(t_image));
        load_texture(game, game->textures.sky, game->map.sky_texture_path);
        printf("✅ Loaded sky texture: %s\n", game->map.sky_texture_path);
    }
    
    // Floor texture: Only load if specified in map
    if (game->map.floor_texture_path)
    {
        if (!check_valid_file_path(game->map.floor_texture_path))
        {
            ft_fprintf(2, "Error: Floor texture specified but not found: %s\n", 
                       game->map.floor_texture_path);
            cleanup_early(game);
            exit(1);
        }
        game->textures.floor = malloc(sizeof(t_image));
        load_texture(game, game->textures.floor, game->map.floor_texture_path);
        printf("✅ Loaded floor texture: %s\n", game->map.floor_texture_path);
    }
}
```

### Enhanced validation in init_game()

```c
void init_game(t_game *game, const char *map_file)
{
    // Existing parsing already validates required textures
    if (parse_map(game, map_file) == -1)
    {
        cleanup_early(game);
        exit(1);
    }
    
    // Double-check that all required map textures exist
    validate_required_map_textures(game);
    
    // Load textures (map + engine features)
    load_all_textures(game);
    
    // Continue with existing initialization...
}
```

### New function: validate_required_map_textures()

```c
void validate_required_map_textures(t_game *game)
{
    char *required_textures[] = {
        game->map.north_texture_path,
        game->map.south_texture_path,
        game->map.east_texture_path,
        game->map.west_texture_path,
        NULL
    };
    
    for (int i = 0; required_textures[i]; i++)
    {
        if (!check_valid_file_path(required_textures[i]))
        {
            ft_fprintf(2, "Error: Required wall texture not found: %s\n", 
                       required_textures[i]);
            cleanup_early(game);
            exit(1);
        }
    }
    
    printf("✅ All required map textures validated\n");
}
```

## PHASE 3: Implement standard door texture system

### New function: load_door_texture()

```c
void load_door_texture(t_game *game)
{
    printf("🚪 Loading standard door texture...\n");
    
    // Standard door texture path
    char *door_texture_path = "textures/doors/door.xpm";
    
    // Validate door texture exists
    if (!check_valid_file_path(door_texture_path))
    {
        ft_fprintf(2, "Error: Standard door texture not found: %s\n", door_texture_path);
        cleanup_early(game);
        exit(1);
    }
    
    // Load single door texture for portcullis-style openinga
    load_texture(game, game->textures.door, door_texture_path);
    
    printf("✅ Standard door texture loaded: %s\n", door_texture_path);
}
```

### Door Rendering Strategy:
- **64x64 door tiles** in the map (H for horizontal, V for vertical)
- **Side faces**: Use appropriate wall textures from map (north/south for H doors, east/west for V doors)  
- **Front/back faces**: Use standard door texture with portcullis-style animation
- **No frame animation**: Single door texture with sliding/opening effect
- **Standard texture path**: `textures/doors/door.xpm` (must exist)
```

## PHASE 4: Update struct.h

### Updated struct for standard door system:

```c
typedef struct s_texture
{
    t_image	*north_wall;
    t_image	*south_wall;
    t_image	*east_wall;
    t_image	*west_wall;
    t_image	*sky;            // ← CHANGE FROM void*
    t_image	*floor;          // ← CHANGE FROM void*
    t_image	*door;           // ← SINGLE DOOR TEXTURE (portcullis-style)
}	t_texture;
```

## PHASE 5: Update cleanup functions

### Update cleanup_mlx_textures() in cleanup_b.c:

```c
// Clean up door texture:
if (game->textures.door)
{
    mlx_destroy_image(game->mlx_ptr, game->textures.door->img_ptr);
    free(game->textures.door);
    game->textures.door = NULL;
}
```

## TESTING STRATEGY

### 1. Test strict map texture validation:
```bash
# Test with valid map
make && ./cub3D maps/valid/test_textures.cub

# Test with missing texture (should fail gracefully)
echo "NO textures/nonexistent/missing.xpm" > test_missing.cub
echo "SO textures/test/south.xpm" >> test_missing.cub
echo "WE textures/test/west.xmp" >> test_missing.cub
echo "EA textures/test/east.xpm" >> test_missing.cub
echo "F 20,20,20" >> test_missing.cub
echo "C 200,200,200" >> test_missing.cub
echo "1111" >> test_missing.cub
echo "1001" >> test_missing.cub
echo "10S1" >> test_missing.cub
echo "1111" >> test_missing.cub
./cub3D test_missing.cub  # Should exit with clear error message
```

### 2. Test door texture auto-creation:
```bash
# Remove door textures to test auto-creation
rm -rf textures/doors/

# Run game - should auto-create door textures based on wall textures
./cub3D maps/valid/test_textures.cub

# Verify doors were created
ls -la textures/doors/horizontal/
ls -la textures/doors/verti/
```

### 3. Test H/V door tiles in map:
```bash
# Create test map with doors
cat > test_doors.cub << EOF
NO textures/test/north.xmp
SO textures/test/south.xpm
WE textures/test/west.xpm
EA textures/test/east.xpm
F 20,20,20
C 200,200,200

1111111
1000001
10H0V01
100S001
1000001
1111111
EOF

./cub3D test_doors.cub  # Should handle H and V tiles correctly
```

### Expected output:
```
🔍 Loading map-specified textures...
✅ All required map textures validated
✅ Loaded sky texture: (if specified)
✅ Loaded floor texture: (if specified)
🎮 Loading engine feature textures...
🚪 Loading door animation textures...
ℹ️  Creating default horizontal door textures...
ℹ️  Creating default vertical door textures...
✅ Door animations loaded: 8 horizontal, 8 vertical frames
✅ Texture loading complete: Map textures + Door support
```

## IMPLEMENTATION ORDER (REVISED - STANDARD DOOR APPROACH)

1. ✅ Update struct.h (5 minutes)
2. ✅ Implement validate_required_map_textures() (10 minutes)
3. ✅ Implement load_optional_map_textures() (10 minutes)
4. ✅ Implement load_door_texture() (5 minutes)
5. ✅ Update load_all_textures() with standard door approach (5 minutes)
6. ✅ Update init_game() with enhanced validation (5 minutes)
7. ✅ Update cleanup functions for single door texture (5 minutes)
8. ✅ Test strict validation and standard door loading (10 minutes)

**Total Time: ~55 minutes**

## STANDARD DOOR APPROACH BENEFITS

### Strict Compliance:
- **Only map-specified textures loaded** (wall textures required)
- **Immediate validation** of all required textures
- **Clear error messages** for missing map textures
- **No loading of unused texture sets**

### Standard Door System:
- **Single door texture** for portcullis-style doors
- **64x64 door tiles** using wall textures for sides
- **Standard texture path** (`textures/doors/door.xpm`)
- **Simple door rendering** with sliding animation

### Memory Efficiency:
- **Minimal memory usage** (only required + single door texture)
- **~80KB typical usage** (4 walls + 1 door = 5 textures)
- **Fixed memory footprint**
- **No frame arrays or dynamic allocation**

### Development Benefits:
- **Clear separation** between map requirements and door features
- **Robust error handling** for missing textures
- **Simple door implementation** for users (just use H/V tiles)
- **Easy testing and validation**
- **No malloc for door frames**

## ERROR HANDLING (STRICT + GRACEFUL)

### Map Texture Errors (STRICT - Exit with error):
- **Missing required wall texture**: Exit with clear error message
- **Invalid texture size**: Exit with size validation error  
- **MLX loading failure**: Exit with MLX error details
- **Memory allocation failure**: Exit with cleanup

### Door Texture Errors (STRICT - Exit with error):
- **Missing standard door texture**: Exit with clear error message (`textures/doors/door.xpm`)
- **Invalid door texture size**: Exit with size validation error
- **Door texture loading failure**: Exit with MLX error details

### Optional Texture Errors (GRACEFUL - Continue with fallbacks):
- **Optional sky/floor missing**: Continue without (use colors)

### Example Error Messages:
```
Error: Required wall texture not found: textures/missing/north.xpm
Error: Standard door texture not found: textures/doors/door.xpm
Error: Sky texture specified but not found: textures/sky/clouds.xpm
✅ Standard door texture loaded: textures/doors/door.xpm
```

## MEMORY MANAGEMENT (OPTIMIZED)

### Map Textures:
- **4 wall textures**: Always allocated and loaded
- **Sky/floor textures**: Only allocated if specified in map
- **Immediate cleanup**: On any map texture loading failure

### Door Texture:
- **Single door texture**: Always allocated and loaded
- **Standard allocation**: Simple t_image structure
- **Memory leak prevention**: Clean up on any allocation failure

### Cleanup Strategy:
```c
// Simplified cleanup for standard door system
void cleanup_mlx_textures(t_game *game)
{
    // Clean up required wall textures
    cleanup_wall_textures(game);
    
    // Clean up optional map textures (only if allocated)
    cleanup_optional_textures(game);
    
    // Clean up single door texture
    cleanup_door_texture(game);
}
```

## PORTCULLIS DOOR SYSTEM DESIGN

### Door Tile Structure (64x64):
- **H tiles (horizontal doors)**: 
  - Side faces: Use `north_wall` and `south_wall` textures
  - Front/back faces: Use standard door texture with vertical sliding animation
- **V tiles (vertical doors)**:
  - Side faces: Use `east_wall` and `west_wall` textures  
  - Front/back faces: Use standard door texture with vertical sliding animation

### Door Animation Strategy:
- **Single texture**: `textures/doors/door.xpm` (64x64 portcullis pattern)
- **Sliding effect**: Render texture with vertical offset based on door state
- **No frame arrays**: Use mathematical sliding calculation
- **Animation states**: Closed (0%) → Opening → Open (100%) → Closing

### Rendering Implementation:
```c
// Example door rendering with portcullis sliding effect
void render_door_face(t_game *game, int door_state)
{
    int slide_offset = (door_state * DOOR_TEXTURE_HEIGHT) / 100;
    
    // Render door texture with vertical sliding
    render_texture_with_offset(game->textures.door, 0, slide_offset);
    
    // Render wall texture above the sliding door if partially open
    if (slide_offset > 0)
        render_wall_texture_above_door(wall_texture, slide_offset);
}
```
