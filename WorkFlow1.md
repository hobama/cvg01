#Problems we face trying to start animating human model/mesh

# What we have #

We have a human model loaded to OpenGL with Cpp.

# Ideas #

We slice human model to different parts, so we create many .obj files for each human body part (arm, elbow, head etc.).
We have defined where we have joints, these joints are responsible for rotating human body, after rotating one joint, other children joints of this one should also be rotated/translated in the world.

Solutions either we create joint system associated to each other, so from parent joint we should calculate coordinates to child joint not from (0,0) world coords but assuming that (0,0) is our parent joint. Problem is that if we recalculate first time, using rotate and translate, we also need to have new coordinates in the system, but OpenGL do it automatically.
Other solution would be to create joints form world coord (0,0), but then we need to do translations and rotations for every child joint by ourselves (by using opengl translation and rotation functions, it would be done automatically, but as mentioned above, we cant get point coordinates in the world then).

Mesh rotations depends on joint positions and are redrawn every time (our main problem now is joints and we assume that at the moment mesh redrawing can be done without any big troubles)