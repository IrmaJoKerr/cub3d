# Cub3D Raycasting Engine Documentation

## What is this?

The Cub3D Raycasting Engine renders the 3D view, handles wall and door textures, and draws the minimap overlay. It uses a column-by-column raycasting approach, integrating door logic, sky/floor rendering, and a dynamic minimap.

## Main Parts

1. **Raycasting Setup** (`raycasting_setup.c`) – Initializes the frame, draws sky/floor, and manages the main render loop.
2. **Raycasting Utilities** (`raycasting_utils.c`) – Handles ray initialization, pixel drawing, texture selection, and DDA step calculations.
3. **Column Rendering** (`render_colum.c`) – Computes projection, texture mapping, and draws each vertical column.
4. **Door Logic and Rendering** (`door_utils.c`, `render_doors.c`) – Manages door states, animations, and rendering.
5. **Space and Floor Rendering** (`draw_space.c`, `raycasting_floor.c`) – Renders special tiles and floor projections.
6. **Minimap Engine** (`minimap.c`, `minimap_setup.c`, `minimap_utils.c`, `minimap_draw_player.c`) – Renders the minimap, player indicator, and handles minimap memory and tile setup.

## How the Raycasting Engine Starts

```
┌────────────────────┐
│ Frame Render Start │
│ render_img(game)   │
└─────────┬──────────┘
          │
          ▼
┌──────────────────────┐
│ Raycast & Minimap    │
│ render_raycast()     │
│ • fill_sky_and_floor |
│ • render_column(x)   |
│ • render_minimap()   │
└─────────┬────────────┘
          │
          ▼
┌────────────────────┐
│ Door Animation     │
│ update_doors()     │
└─────────┬──────────┘
          │
          ▼
┌────────────────────┐
│ Crosshair Render   │
│ draw_crosshair()   │
└────────────────────┘
```

## How Raycasting Works

### Step 1: Frame Setup
- `render_img(game)` calls `render_raycast(game)`.
- Sky and floor are filled using `fill_sky_and_floor(game)` and `draw_sky_and_floor(game, ...)`.

### Step 2: Column Raycasting

```
┌───────────────────────┐
│ For each column x     │
│ render_column(game, x)|
└─────────┬─────────────┘
          │
          ▼
┌─────────────────────────────┐
│ Ray Init                    │
│ init_ray(&wall_ray, game, x)|
└─────────┬───────────────────┘
          │
          ▼
┌──────────────────────────┐
│ DDA & Door Logic         │
│ perform_dda_with_door()  |
└─────────┬────────────────┘
          │
          ▼
┌─────────────────────┐
│ Projection & Tex    │
│ compute_projection()|
│ compute_texture()   |
└─────────┬───────────┘
          │
          ▼
┌───────────────────────┐
│ Draw Column           │
│ draw_textured_column()|
└───────────────────────┘
```

### Step 3: Minimap Rendering
- `render_minimap(game)` draws the minimap overlay, including player indicator and border.

## How the Minimap Engine Works

```
┌────────────────────────┐
│ Minimap Render         │
│ render_minimap(game)   │
└─────────┬──────────────┘
          │
          ▼
┌────────────────────────┐
│ Viewport Calculation   │
│ calc_minimap_viewport()│
└─────────┬──────────────┘
          │
          ▼
┌────────────────────────┐
│ Pixel Copy             │
│ copy_minimap_pixels()  │
└─────────┬──────────────┘
          │
          ▼
┌──────────────────────────────────┐
│ Border & Player                  |
│ draw_minimap_border()            |
│ draw_triangle_player_indicator() |
└──────────────────────────────────┘
```

## Rules and Error Handling

- All rendering and minimap functions check for valid pointers and memory before drawing.
- Door logic is updated every frame for animation.
- Minimap is rendered only if images are initialized.
- Errors in memory allocation or rendering result in cleanup and exit.

## Debug and Testing Features

- Step-by-step rendering progress.
- Minimap viewport and player indicator debug output.
- Door state and animation debug output.
- Clear error messages for rendering failures.

## How the Math Works

Raycasting works by shooting a "ray" from the player's position for each vertical column of the screen. The engine calculates where each ray hits a wall, door, or special tile by stepping through the map grid using DDA (Digital Differential Analyzer) until a collision is found. The distance to the hit is used to compute how tall to draw the wall slice, making closer walls appear taller and farther walls shorter. Texture mapping uses the hit position to select the correct pixel from the wall or door image. The minimap uses simple scaling and translation to show the player's position and surroundings.

## Sample Calculations

Raycasting in Cub3D is performed for each vertical column of the screen, using the following sequence of function calls and calculations:

1. **Ray Initialization** (`init_ray`)
   - For each column `x`, `render_column(game, x)` calls `init_ray(&wall_ray, game, x)`.
   - Sets up the ray’s direction and starting position based on the player’s coordinates and camera plane.
   - Calculates `delta_x` and `delta_y` as the distance the ray travels to cross a grid line in x/y:
     ```c
     if (ray->dir_x == 0)
         ray->delta_x = 1e30;
     else
         ray->delta_x = fabs(1.0 / ray->dir_x);

     if (ray->dir_y == 0)
         ray->delta_y = 1e30;
     else
         ray->delta_y = fabs(1.0 / ray->dir_y);
     ```
     - `fabs` returns the absolute value of a floating-point number, ensuring the distance is always positive.

2. **DDA Step Setup** (`initialize_deltas_and_steps`)
   - Determines step direction (`step_x`, `step_y`) and initial side distances (`side_x`, `side_y`):
     ```c
     if (ray->dir_x < 0)
         ray->step_x = -1;
         ray->side_x = (game->curr_x - ray->map_x) * ray->delta_x;
     else
         ray->step_x = 1;
         ray->side_x = (ray->map_x + 1.0 - game->curr_x) * ray->delta_x;
     // Same for Y
     ```

3. **DDA Traversal** (`perform_dda_with_door`)
   - The ray steps through the grid, incrementing `side_x` or `side_y` by `delta_x` or `delta_y` until a hit is found (wall or door).

4. **Hit Detection**
   - When a wall or door is hit, the loop exits.

5. **Distance Calculation** (`compute_projection`)
   - Perpendicular distance is calculated using the side and direction, not directly from `delta_x`/`delta_y`:
     ```c
     if (side == 0)
         perp_wall_dist = (ray->map_x - game->curr_x + (1 - ray->step_x) / 2) / ray->dir_x;
     else
         perp_wall_dist = (ray->map_y - game->curr_y + (1 - ray->step_y) / 2) / ray->dir_y;
     ```

6. **Wall Height** (`compute_projection`)
   - Wall height is computed from the perpendicular distance:
     ```c
     line_height = (int)(game->screen_height / perp_wall_dist);
     ```

7. **Texture Mapping** (`compute_texture`, `get_wall_texture`, `get_door_texture`)
   - Texture coordinates are calculated based on hit position and side.

8. **Drawing** (`draw_textured_column`)
   - The column is drawn using the calculated texture and height.

9. **Minimap Rendering** (`render_minimap`, `draw_triangle_player_indicator`)
   - The minimap uses scaling and translation to show the player’s position and orientation.

---

**Sample Calculation:**

Suppose:
- `game->curr_x = 3.5`, `game->curr_y = 2.2`
- `ray->map_x = 3`, `ray->map_y = 2`
- `ray->dir_x = -0.7`, `ray->dir_y = 0.5`

Then:
```c
if (ray->dir_x == 0)
    ray->delta_x = 1e30;
else
    ray->delta_x = fabs(1.0 / -0.7); // = 1.4286

if (ray->dir_y == 0)
    ray->delta_y = 1e30;
else
    ray->delta_y = fabs(1.0 / 0.5); // = 2.0

// X direction
ray->step_x = -1
ray->side_x = (3.5 - 3) * 1.4286 = 0.7143

// Y direction
ray->step_y = 1
ray->side_y = (2 + 1.0 - 2.2) * 2.0 = 0.8 * 2.0 = 1.6
```
This means the ray will first cross the x-side after 0.7143 units, and the y-side after 1.6 units.

---

*`fabs` is a standard C library function that returns the absolute value of a floating-point number, ensuring all distances are positive regardless of direction.*

*This guide explains how the raycasting and minimap engines work, from frame setup to rendering and error handling.*
