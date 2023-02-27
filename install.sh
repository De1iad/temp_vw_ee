#!/bin/sh
GREEN='\033[0;32m'
RESET='\033[0m'
os="$(uname -s)"
if [ $os == Darwin ]
then
	if brew update
	then
		echo "brew is installed."
	else
		/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
	fi
	brew install SDL2
	brew install fftw
else
	sudo apt-get install libfftw3-dev libfftw3-doc
	sudo apt-get install libsdl2
	sudo apt-get install libsdl2-dev
	sudo apt-get install libxrender-dev
fi

echo -e "${GREEN}Script complete.${RESET}"