#working for motion capture data

# Introduction #

Selected BHV format instead of C3D (will need to explain why).
Rebuilding Joint system for BHV format.

~~Meshes will be calculated not with OpenGL glRotate function, but by CPU with our own formula multiplications (slower but better quality)~~ Reverted to OpenGL