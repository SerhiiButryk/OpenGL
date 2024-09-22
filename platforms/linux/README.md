This is a script for linux target

On linux it's required to install dependencies before building the project.

$ sudo apt-get install libglew-dev
$ sudo apt-get install libglfw3-dev
$ sudo apt install libglfw3

Then you should have include files listed in '/usr/include/GL/' or '/usr/include/GLFW/'.
If it's not the case then you haven't correctly installed the dependencies.
You might try to install it again.

Check if you have them on the system:

$ ls -l /usr/include/GL/
$ ls -l /usr/include/GLFW/

After that you can build the project