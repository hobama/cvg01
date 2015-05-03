# Introduction #

Add your content here.


# Details #

The model consists of 15 joints: back\_root (root joint), chest, neck, left\_shoulder, left\_elbow, left\_wrist, right\_shoulder, right\_elbow, right\_wrist, left\_hip, left\_knee, left\_ankle, right\_hip, right\_knee, right\_ankle. These joints allow our model to be correctly animated in 3D scene, although we don't achieve much detail like the movement of finger or toes. Each joint has a mesh applied to it, which is not affected by the animation data, except being rotated or translated in the scene. The connection between the meshes (the space around the joint itself) is being done automatically by the program. The algorithm for doing that is:
1. find two vertices belonging to the mesh and the parent mesh, which has the shortest distance of all the vertices, belonging to mesh and its parent.
2. Determine some threshold value, which can be just user defined. (for example 5%) which determines the longest distance between vertices belonging to mesh and it's parent.
3. Find all other vertices, needed to connect, by calculating the distance between each of them. (If the distance is between the shortest distance and the distance, calculated from the threshold value), then those two vertices need to be connected.

Each connection between the meshes vertex and parent meshes vertex has its subvertices. This is necessary for joints rotations to look smooth. (The more subvertices we have, the smoother the rotation looks). To find positions of subvertices on the connecting line, we apply basic mathematics of function, determining the line, and  vectors. Any line function can be written as: L(t) = C + b\*t, where C is the starting point of a line, b is a vector, determining the direction of a line and t is just some value.
Since we have the position of first connecting vertex (which is letter C in the above defined function) and the second one (let's mark it's position as letter B), we can find the direction vector b: B - C.  Now taking t from (0 to 1) we get the position of a point, which is between B and C. In fact if we took t=0, from the line function we get the position of C, and if we took t=1, we get the position of point B. So to determine the position of the first subvertex on the line, we need to set t = 1/number\_of\_subvertices. To determine the position of the second subvertex on the line, set t = 2 **1/number\_of\_subvertices. The n'th subvertex on the line: t = n** 1/number\_of\_subvertices, where n is from (0 to number\_of\_subvertices).

Now to calculate the position of subvertices after rotation, we apply linear blend skinning, what means that each subvertex has some weight (let's mark it as w), which influences the degree it has to be rotated. Of course, each subvertices weight could be determined manually, but we found that it is pretty easy to determine it automatically and the overall result is really good. Let's consider that we have n vertices on the connecting line. The joint is being rotated by A degrees.  Each vertex weight w is being determined by it's position on the connecting  line: w = position\_on\_the\_connecting\_line **1/total\_number\_of\_vertices\_on\_the\_line. So the first vertex on the line has the weight w = 1** 1/n, while the last vertex on the line has the weight w = n **1/n = 1. Now considering the degree each vertex is being rotated, the first one is rotated by (A** 1 **1/n) degrees, while the last one is being rotated by ( A** n 