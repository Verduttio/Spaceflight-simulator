# Abstract-Programming-Project
[![Tests](https://github.com/Verduttio/Abstract-Programming-Project/actions/workflows/action.yml/badge.svg)](https://github.com/Verduttio/Abstract-Programming-Project/actions/workflows/action.yml)

## App info

Basic spaceflight simulator made in C++.

You can build your own rocket and launch it. During the flight you can control rocket's angle, engines power and even seperate stages. 

## Prerequisites to run on your own machine
  * docker
  
...or you can just try to compile the project and link files manually. However, I recommend running via docker because it is much simpler.

## Usage (docker)

All what you have to do is to just build the project via comand run in the project root directory:
```
sudo make
```

If all goes well, you should see the information that executable file is in `/build` directory.

So move to the `/build/` by `cd /build` and execute the generated file, it can be `AbstracProgrammingProject.out` (depends on the project's name).

Execution: 
```
./AbstracProgrammingProject.out
```

## Documentation
Extensive documentation is provided in `/documentation` directory. There are many images and one general file. 
