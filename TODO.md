# Misc
- [x] Spilt up rendering entirely into seperate files
- [ ] Rewrite/reorganize the code to be cleaner
- [x] Split header files into source files when needed
- [x] Come up with a title no one has came up with before (possible ideas: EmreTechCraft, TechCraft)

# Textures
- [x] Make a texture atlas and create a function that can find the texture coordinates for a texture

# World
- [ ] Make a world class that manages all chunks in the world
- [x] Height-map generation
- [ ] Infinite world generation!
- [x] Compress and decompress chunk data
## Block
- [x] Make a block class that represents a single block with a few properties
## Chunks
- [x] Make a chunk section that represents 16 * 16 * 16 amount of blocks
- [x] Make a chunk class that stores chunk sections in an Infinite manner
- [x] Optimize chunks to not render invisible block faces
- [ ] Optimize chunks to not render faces invisible by other chunks (causes an overlap)
## Enhancements
- [ ] Lighting
- [ ] Biomes

# Player
- [ ] Make a player class that represents the player, and the camera is linked to it
- [x] Implement raycasting for breaking/placing blocks

# UI
- [ ] An UI system
- [ ] Main menu and pause menu

# Bugs
- [x] Controlling the camera with the mouse is slightly broken
- [x] Textures might be rotated on the side faces
- [x] Texture atlas system doesn't show correctly (line in the middle)

# Also
- Any comments in the code that starts with TODO, FIXME, or BUG.
