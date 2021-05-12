# Misc
- [x] Spilt up rendering entirely into seperate files
- [ ] Rewrite/reorganize the code to be cleaner
- [x] Split header files into source files when needed
- [x] Come up with a title no one has came up with before (possible ideas: EmreTechCraft, TechCraft)

# Textures
- [x] Make a texture atlas and create a function that can find the texture coordinates for a texture

# World
## Block
- [x] Make a block class that represents a single block with a few properties
## Chunks
- [ ] Make a layer class that represents one layer in a chunk (stores 16 * 16 * 1 blocks)
- [ ] Make a chunk class that stores blocks in a 16 * 16 * 16 area by using layers
- [ ] Optimize chunks to not render invisible block faces
## Enhancements
- [ ] Lighting
- [ ] Biomes
- [ ] Map generation (with an optional seed)

# UI
- [ ] An UI system
- [ ] Main menu and pause menu

# Bugs
- [x] Controlling the camera with the mouse is slightly broken
- [x] Textures might be rotated on the side faces
- [x] Texture atlas system doesn't show correctly (line in the middle)
- [ ] You can see a bit of the background if you look carefully into the blocks

# Also
- Any comments in the code that starts with TODO, FIXME, or BUG.
