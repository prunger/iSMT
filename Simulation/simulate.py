import numpy as np
import time

interval = 10 # in seconds

# Loop forever
#while True:
    
# RAMP UP
real_ramp_up_time = 900 # in seconds

neutral = 80 # this is the starting point +/- noise

setpoint = 160 # this is the end point +/- noise

outputs_per_ramp = real_ramp_up_time / interval # this is how many outputs we get per ramp
# according to the real data it takes 0.25 hour to ramp up to ~160 degrees F from ~80 degrees F
# real_ramp_up_time = 900 sec
# interval = 10 sec
# ramp_time = time / interval = 90



ramp = np.linspace(neutral, setpoint, int(outputs_per_ramp))

ramp_noise = np.random.normal(0, 1, int(outputs_per_ramp))

ramp_up = [x + y for x, y in zip(ramp, ramp_noise)]



for item in ramp_up:
    
    # wait for 1 interval
    time.sleep(interval)
    
    # write the item to text file here
    print(item)
    try:
        f = open("simulated.txt", "w")
        f.write(str(item))
    except Exception as e:
        print(str(e))
    
    
    
'''
# STAY STEADY FOR A PERIOD
line_time = 10 # this is the period in seconds signal is steady

line = np.linspace(setpoint, setpoint, line_time)

steady_line = [x + y for x, y in zip(line, ramp_noise)]



for item in steady_line:
    
    # wait for 1 second
    time.sleep(1)
    
    # write the item to text file here
    print(item)
    
'''

# RAMP DOWN
real_ramp_down_time = 3600

neutral = 160 # this is the starting point +/- noise

setpoint = 80 # this is the end point +/- noise

outputs_per_ramp = real_ramp_down_time / interval # this is how many outputs we get per ramp
# according to the real data it takes 1 hour to ramp down to ~80 degrees F from ~160 degrees F
# real_ramp_up_time = 3600 sec
# interval = 10 sec
# ramp_time = time / interval = 360


ramp = np.linspace(neutral, setpoint, int(outputs_per_ramp))

ramp_noise = np.random.normal(0, 1, int(outputs_per_ramp))

ramp_down = [x + y for x, y in zip(ramp, ramp_noise)]



for item in ramp_down:
    
    # wait for 1 interval
    time.sleep(interval)
    
    # write the item to text file here
    print(item)
    try:
        f = open("simulated.txt", "w")
        f.write(str(item))
    except Exception as e:
        print(str(e))
        
        

# DONE WRITE SOME ZEROS TO STOP SIMULATION
zeros = 5
while zeros:

    # wait for 1 interval
    time.sleep(interval)

    print(str(0))
    try:
        f = open("simulated.txt", "w")
        f.write(str(0))
    except Exception as e:
        print(str(e))
        
    zeros = zeros - 1

