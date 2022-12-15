# SDL_SpaceShooter

This is my assignment submission for the Data-Oriented Space Shooter.

I worked with c++ and SDL. 

My first approach to save some performance was to check the objects only once by looping through my collider list starting at `i = 0` and `j = i + 1`, then I check for box intersections using AABB before executing collision callbacks. I hardcoded the tag check between player and projectiles because I was taking way too long into designing a good architecture for my collision class, and I believe that is the only actual exception for my game idea, so I decided that I was over-engineering it and discarded the test code for that.

My projectiles are pooled into an array with a capacity of 20, I decided to go for a relatively low number because I was going to implement a better cooldown on the autofire, effectively restricting the number of projectiles visible toa very low count, but I thought to invest more time into the core ideas that would benefit performance instead of gameplay aspects. So currently it is possible to hit the projectile cap, but upon reaching the cap, the system will stop spawning more instances.

Controls: WSAD for movement, space to shoot.
I also included as a debug feature the ability to spawn more asteroids by pressing "p".
