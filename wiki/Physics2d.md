2D Physics
==========

**hx3d** include its own 2D physics engine, greatly inspired by the *ImpulseEngine* from *RandyGaul*.

Here are the features:
  - **Colliders** (Bodies)
    - Type: Static/Dynamic/Kinematic
    - Shape: Polygon(Box) / Circle


  - **Attractors** (Gravity modifiers)
    - Point: apply a force towards the attractor center in a radius
    - Zone: apply a force towards a direction in a rectangle zone
    - Global: apply an *universal* force towards a direction. Used for the world gravity for example.


  - **Collision matrix** (category / masks)
    - Make groups of bodies which can or not collide


  - **Collision listeners** (To *hook* a collision)
    - When two bodies overlaps, it will pass to the listener, even if the masks prevent the collision.
