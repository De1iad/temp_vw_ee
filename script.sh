#!/bin/sh
if brew update
then
	echo "brew is installed."
else
	/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
fi
brew install fftw
brew install SDL2