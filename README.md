this is a project for implemnting the fast fourier transform(fft) with 8 inputs in C++. in the picture below you can see the process. there are four steps:

step 1: reoder the inputs from format of x(0), x(1), ..., x(8) to the specified format in the picture. 

step 2: calculate the fft for each pair(fft2)

step 3: calculate the fft between four of the outputs of fft2 (fft4)

step 4: calculate the fft between eight of the outputs of fft4 (fft8)
![Screenshot 2024-09-29 175644](https://github.com/user-attachments/assets/7573f972-85bc-4da9-a77a-a833a945980f)

there are three implemnation for this problem:
in
