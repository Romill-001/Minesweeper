sudo apt update
sudo apt install \
    x11-apps \
    libsfml-dev \
    libx11-dev \
    libxrandr-dev \
    libxcursor-dev \
    libudev-dev \
    libfreetype-dev \
    libopenal-dev \
    libflac-dev \
    libvorbis-dev \
    libgl1-mesa-dev \
    libegl1-mesa-dev
mkdir -p build
cd build
cmake ..
make