#!/bin/sh
if brew update
then
	echo "brew is installed."
else
	/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
fi
brew install SDL2
wget http://fftw.org/pub/fftw/fftw-3.2.2.tar.gz
tar -xf fftw-3.2.2.tar.gz
cd fftw-3.2.2
./configure
make
make install