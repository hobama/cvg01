#Creating joint system

# Introduction #

What's the primary idea of the joint system and how we implemented it.


# Details #

We have decided to create joints without a bone system, just placing joints into a proper place in a human model mesh.
Every joint have it's parent (except back\_root) and it may have children, so in this way we now which joints must be influenced after rotations. All this joint data is kept in a special text-file, with each coordinates and hierarchy.