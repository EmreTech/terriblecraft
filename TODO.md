# Misc
- [] Spilt up rendering entirely into seperate files
- [] Rewrite/reorganize the code to be cleaner
- [x] Split header files into source files when needed
- [] Come up with a title no one has came up with before (possible ideas: EmreTechCraft, TechCraft)

# Textures
- [x] Make a texture atlas and create a function that can find the texture coordinates for a texture

# World
- [x] Make a block class that represents a single block with a few properties, including a pointer to the parent chunk that owns the block
- [] Make a chunk class that stores blocks in a 16 * 16 * 16 area (just like Minecraft)
- [] Optimize chunks to not render invisible block faces
- [] Lighting
- [] Biomes
- [] Map generation (with an optional seed)

# UI
- [] An UI system
- [] Main menu and pause menu

# Bugs
- [x] Controlling the camera with the mouse is slightly broken
- [x] Textures might be rotated on the side faces
- [x] Texture atlas system doesn't show correctly (line in the middle)

# Also
- Any comments in the code that starts with TODO, FIXME, or BUG.