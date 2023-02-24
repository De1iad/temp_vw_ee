
## Dependencies

- sdl2 library - for the sound hardware interface
	- sudo apt-get install libsdl2-dev


- fftw3 for laplace transform
	https://www.linuxfromscratch.org/blfs/view/svn/general/fftw.html


LIBFLAGS_STATIC = -L/usr/lib/x86_64-linux-gnu/ -lSDL2 -lm -lfftw3
INCLUDES = -I./ -I/usr/include/SDL2/ -I 


## sources
https://www.youtube.com/watch?v=6IX6873J1Y8&list=PLEETnX-uPtBVpZvp-R2daNfy9k3-L-Q3u&index=3


sudo apt-get install libfftw3-dev libfftw3-doc
