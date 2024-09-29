This is a project for implementing the fast fourier transform(fft) with 8 inputs in C++. In the picture below you can see the process. There are four steps:

Step 1: reorder the inputs from the format of x(0), x(1), ..., x(8) to the specified format in the picture. 

Step 2: calculate the fft for each pair(fft2)

Step 3: calculate the fft between four of the outputs of fft2 (fft4)

Step 4: calculate the fft between eight of the outputs of fft4 (fft8)
![Screenshot 2024-09-29 175644](https://github.com/user-attachments/assets/7573f972-85bc-4da9-a77a-a833a945980f)

There are three implementations and the goal is to find the execution time of each implication and compare them:

fft8-inline: there is a class complex for complex numbers(https://github.com/mahdikheirkhah/advanced-programming-with-CPP). The w_cal method used for calculating the W is referred to at the bottom of the picture above. Then, in the main function, it will first cin the input from the user then do all the 4 steps.

fft8-dynamic: besides the complex class, this imposition uses class "fifo_t" to make a queue (first in, first out), And there is a structure that uses "actiro" which uses four in and out queues. Each of the four steps becomes an input and output and each step becomes a function.

fft8-multithread: it is almost like fft8-dynamic, but instead of threads it will use four threads. And each function is using one thread and in all of these functions we should make sure that there are enough inputs from the output of the last function(4 steps). 
