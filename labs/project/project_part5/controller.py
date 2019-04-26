import pygame
import math

pygame.init()
pygame.joystick.init()
clock = pygame.time.Clock()
done = False

# -------- Main Program Loop -----------
joystick_count = pygame.joystick.get_count()
print("Number of joysticks: {}".format(joystick_count))

for i in range(joystick_count):
    joystick = pygame.joystick.Joystick(i)
    joystick.init()

print("Joystick {}".format(i) )

# Get the name from the OS for the controller/joystick
name = joystick.get_name()
print("Joystick name: {}".format(name) )

# Usually axis run in pairs, up/down for one, and left/right for
# the other.
axes = joystick.get_numaxes()
print("Number of axes: {}".format(axes) )

while done==False:
    # EVENT PROCESSING STEP
    for event in pygame.event.get(): # User did something

        # print(event)

        # quit condition
        if event.type == pygame.QUIT: # If user clicked close
            done=True # Flag that we are done so we exit this loop
        
        # Possible joystick actions: JOYAXISMOTION JOYBALLMOTION JOYBUTTONDOWN JOYBUTTONUP JOYHATMOTION
        if event.type == pygame.JOYBUTTONDOWN:
            print("Joystick button pressed.")
        if event.type == pygame.JOYBUTTONUP:
            print("Joystick button released.")

        
        if event.type == pygame.JOYAXISMOTION:  

            # left thumb, left-right
            if event.axis == 0:
                if math.isclose(event.value, 1.0, rel_tol=1e-2):
                        print("left stick: moved right")
                if math.isclose(event.value, -1.0, rel_tol=1e-2):
                        print("left stick: moved left")
                if math.isclose(event.value, 0.0, rel_tol=1e-2):
                        print("left stick: neutral")
            # right thumb, left-right
            if event.axis == 2:
                if math.isclose(event.value, 1.0, rel_tol=1e-2):
                        print("right stick: moved right")
                if math.isclose(event.value, -1.0, rel_tol=1e-2):
                        print("right stick: moved left")
                if math.isclose(event.value, 0.0, rel_tol=1e-2):
                        print("right stick: neutral")
            # right thumb, up-down
            if event.axis == 3:
                if math.isclose(event.value, 1.0, rel_tol=1e-2):
                        print("right stick: moved down")
                if math.isclose(event.value, -1.0, rel_tol=1e-2):
                        print("right stick: moved up")
                if math.isclose(event.value, 0.0, rel_tol=1e-2):
                        print("right stick: neutral")

            # print("Joystick axis ", event.joy, event.axis, event.value)
    
    # Limit to 20 frames per second
    clock.tick(20)
    
# Close the window and quit.
# If you forget this line, the program will 'hang'
# on exit if running from IDLE.
pygame.quit ()
