# General
- Add modding support by moving certain hardcoded parts of code to Lua (for example, moving defining block types to Lua code)
- Allow configuration support for certain options (mostly for window stuff/rendering). Format will either be a text file, json file, or Lua file.
- Switch over from using Sol2 (as a wrapper for the C Lua api) to my own wrapper for the C Lua api (hopefully less template metaprogramming)

# Camera
- Add an entity that can be used to simulate a third-person camera

# Player
- Player model
- Render player model only when the player is in third-person mode

# World
- World class, which manages all chunks
- Add chunk updates, where "updates" means regenerating the mesh
- Save unloaded chunks to a file, delete this file when the chunk is reloaded, and delete all files when the game exits
## Blocks
- Allow Lua code to add block types
## Chunks
- Split chunk meshes into the solid mesh, liquid mesh, and flora (plant) mesh. This will allow for certain meshes to be rendered differently 

# UI
- Add an UI System (use a library, or make it myself)
- Menus, including a main menu (with submenus) and a pause menu
- Add a HUD (crosshair, inventory, debug stats)
- Allow Lua to control the UI

# Also
- Any comments in the code that starts with TODO, FIXME, or BUG.
