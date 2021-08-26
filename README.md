Final: Ocean
Nathan Howard

Run 'make' then 'ocean' to run my program.

When you open the program, you will see a water effect, and directly behind you there are three spheres which demonstrate various material properties. In this real time ray tracing program, I have implemented reflections, refractions, and roughness, in addition to the water effect.

Spheres: The red sphere is reflective with a roughness of 0, the green sphere is the same amount of reflective but with a roughness of 0.2, and the blue sphere is just blue, but it is moving above and below the water to show the waters refractiveness.

Water Effect:
This was achieved by creating 3 radial sin waves and calulating the surface normal based on the displacement of these waves. The water is actually perfectly flat, which you can see when observing the shadow of the moving sphere. However, the look of the water is mostly determined by it's reflections and refractions, so manipulating only the normal actually creates a convincing effect.

Reflections:
Reflections were fairly simple, nothing much to comment on.

Refractions:
Refractions brought a couple challenges with them. So far, the program just took a single ray and bounced it around until it stopped bouncing. If you have a material that is both reflective and refractive however, you have to create 2 rays from a single ray, one that was reflected and one that was refracted. This would be easy to do recursively, but that's not an option with GLSL. I ended up having the rays (based on the pixels per ray) alternate between reflecting and refracting. This mostly solves the issue as long as you have more than 1 ray per pixel. However, it does mean there are no refractions in reflections, because a ray is either a reflecting or a refracting ray. And if you reduce the rays per pixel to 1, you will only get reflections. Refractions also significantly reduced the fps when I first introduced them, but my solution to the previous problem helped with this, because it's no more work compared to doing only reflections with mutiple rays per pixel, just some of those reflection rays become refraction rays.

Roughness:
The roughness was somewhat of a challenge to implement. I ended using quaternions and a custom random function to create the effect of a rough surface normal. I used the random function to create two angles I wanted to rotate the vector by (as in spherical coordinates, theta and phi). I then used cross products and theta to get the axis to rotate around, and did some quaternion multiplication to get the rotated normal. This meant I could use a variable to scale the angles, and that's what you adjust with roughness. It looked terrible when I first tried it, but that was with only 1 ray per pixels, and this effect looks smoother the more rays per pixel you have because all the randomness starts to average out. I also removed time from the random function seed so you would only get a shimmering effect if there was motion, as with the water.

Note: I am currently having a bug with roughness and refraction combined where roughness doesn't affect the refracted image of something. I wasn't able to figure this out before turning it in.

Key bindings
  ESC        Exit
  arrows     Change view angle
  PgDn/PgUp  Zoom in and out
  0          Reset view angle
  r/R        Increase/decrease rays per pixel (anti-aliasing and more detail to water in the distance)
  p/P        Increase/decrease passes (bounces)
  g/G        Increase/decrease roughness of water
  i/I        Increase/decrease refractive index of water
