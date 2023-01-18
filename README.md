# Abstract-Programming-Project
[![Tests](https://github.com/Verduttio/Abstract-Programming-Project/actions/workflows/action.yml/badge.svg)](https://github.com/Verduttio/Abstract-Programming-Project/actions/workflows/action.yml)

## App info

Basic spaceflight simulator made in C++.

You can build your own rocket and launch it. During the flight you can control rocket's angle, engines power and even seperate stages. 

## Prerequisites to run on your own machine
  * docker
  
...or you can just try to compile the project and link files manually. However, I recommend running via docker because it is much simpler.

## Usage (docker)

**Make sure that your `build_tools` directory is not empty. If it is, just download these files: `https://github.com/f-squirrel/dockerized_cpp` and move them into the `build_tools` directory.** 

Run all these commands in the root of the project directory.

Firstly you have to build a docker container:
```
sudo docker build -t example/example_build:0.1 -f DockerfileBuildEnv .
```

Now just build the project:
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


![UML](https://user-images.githubusercontent.com/72033031/213248231-93cd01d8-cba7-4672-86f2-c31e93304324.jpg)


