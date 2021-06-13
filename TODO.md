# General
- Add modding support by moving certain hardcoded parts of code to Lua (for example, moving defining block types to Lua code)

# Camera
- Add the option for the camera to be independently controlled

# Player
- Player model
- Render player model only when the player is in first-person mode

# World
- World class, which manages all chunks
- Add chunk updates, where if a block is placed/replaced/removed, we add the need to be updated Chunk Section and its position to a map, and update it later.
- Store both loaded and unloaded chunks in seperate maps
- Compress chunks before unloading them, then decompress the compressed chunk before reloading (to save memory)
## Chunks
- Build an optimized chunk mesh where if a solid block is facing an air block or liquid block (for example, water), we build a face at that direction. Otherwise, we don't build a face.
- Split chunk meshes into the solid mesh, liquid mesh, and flora (plant) mesh. This will allow for certain meshes to be rendered differently 

# UI
- Add an UI System (use a library, or make it myself)
- Main menu
- Pause menu
- Add a HUD (crosshair, inventory, stats about the game when enabled)
- Allow Lua to control the UI

# Also
- Any comments in the code that starts with TODO, FIXME, or BUG.
