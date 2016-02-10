# VLSICAD-placement
VLSI CAD course expeiment.

IC Layout Placement for CAD tools like Cadence.

In a 2D grid space

Given some anchors and some nodes. They are connected to each other by customer definition.

Object: Find the positions of node to place so that the total manhattan distance of all connection is minimized.

Methode -- Like Gradient descent but in a 2D grid space. 
Start the nodes position with zero or randomly, constantly move them in each epoch by solving quadratic matrix equation




