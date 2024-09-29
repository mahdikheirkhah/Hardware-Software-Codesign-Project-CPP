This is a project for implementing the fast fourier transform(fft) with 8 inputs in C++. In the picture below you can see the process. There are four steps:

Step 1: reorder the inputs from the format of x(0), x(1), ..., x(8) to the specified format in the picture. 

Step 2: calculate the fft for each pair(fft2)

Step 3: calculate the fft between four of the outputs of fft2 (fft4)

Step 4: calculate the fft between eight of the outputs of fft4 (fft8)
![Screenshot 2024-09-29 175644](https://github.com/user-attachments/assets/7573f972-85bc-4da9-a77a-a833a945980f)

there are three implemnations and the goal is to find the execution time of each implemtion and compare them:

fft8-inline: there is a class complex for complex numbers(https://github.com/mahdikheirkhah/advanced-programming-with-CPP). the w_cal method used for calculating the W which has been refered to in the bottom of picture above. then in the main func it will first cin the input from the user then do all the 4 steps.

fft8-dynamic: beside the complex class this implemtion use class "fifo_t" to make a queue (first in first out). and there is a structure "actiro" which use four in and out queue because each of the four step has an input and output. and each step become as a function.

fft8-multithread: it almost like fft8-dynamic but instead of thread it will use four threads. and each function is using one thread and in all of this function we should make sure that there are enough inputs from the output of last function(4 steps). 


