# Ray Tracing Engine

A comprehensive C++ ray tracing engine that renders 3D scenes with realistic lighting, materials, and textures. This project implements a full-featured ray tracer with support for various geometric objects, advanced materials, texture mapping, normal mapping, and procedural noise generation.

## Features

- **Multiple Geometric Objects**: Spheres, cubes, cylinders, cones, planes, and composite objects
- **Ray Marching**: Support for complex implicit surfaces using signed distance functions
- **Advanced Materials**: Simple materials, refractive materials with realistic light refraction
- **Texture Mapping**: Multiple texture types including flat colors, checker patterns, image textures, marble, stone, and noise-based textures
- **Normal Mapping**: Support for normal maps to add surface detail
- **Lighting System**: Point lights with realistic light calculations
- **Procedural Noise**: Value noise and gradient noise for procedural texture generation
- **SDL2 Integration**: Real-time rendering and display using SDL2

## Prerequisites

Before building and running this project, you need to install the following dependencies:

### System Dependencies

#### Ubuntu/Debian
```bash
sudo apt update
sudo apt install -y build-essential cmake libsdl2-dev git
```

#### macOS (using Homebrew)
```bash
brew install cmake sdl2
```

#### Windows
- Install [Visual Studio](https://visualstudio.microsoft.com/) with C++ support
- Install [CMake](https://cmake.org/download/)
- Download [SDL2 development libraries](https://www.libsdl.org/download-2.0.php)

### Linear Algebra Library (qbLinAlg)

This project depends on the QuantitativeBytes Linear Algebra library. You need to clone it to your include directory:

```bash
cd include/
git clone https://github.com/QuantitativeBytes/qbLinAlg.git
```

## Building the Project

1. **Clone the repository**:
   ```bash
   git clone https://github.com/TheCrypted/RayTracing.git
   cd RayTracing
   ```

2. **Install the required linear algebra library**:
   ```bash
   cd include/
   git clone https://github.com/QuantitativeBytes/qbLinAlg.git
   cd ..
   ```

3. **Create a build directory**:
   ```bash
   mkdir build
   cd build
   ```

4. **Configure with CMake**:
   ```bash
   cmake ..
   ```

5. **Build the project**:
   ```bash
   make
   ```
   
   On Windows with Visual Studio:
   ```bash
   cmake --build . --config Release
   ```

## Running the Ray Tracer

After successful compilation, run the executable:

### Linux/macOS
```bash
./RayTracing
```

### Windows
```bash
RayTracing.exe
```

The application will open a window (1280x720 pixels) and start rendering a ray-traced scene. The current scene is configured in the source code and includes various objects with different materials and textures.

## Project Structure

```
RayTracing/
├── assets/                 # Texture assets and images
│   ├── Voronoi.bmp        # Voronoi texture
│   └── Voronoi_normal.bmp # Normal map for Voronoi
├── include/               # Header files
│   ├── qbLinAlg/         # Linear algebra library (to be cloned)
│   ├── CApp.h            # Main application class
│   ├── scene.h           # Scene management
│   ├── camera.h          # Camera implementation
│   ├── ray.h             # Ray definition
│   ├── object.h          # Base object class
│   ├── material.h        # Material system
│   └── ...               # Other headers
├── objects/               # Geometric object implementations
├── materials/            # Material implementations
├── textures/             # Texture implementations
├── lights/               # Lighting system
├── normals/              # Normal mapping
├── noise/                # Procedural noise generation
├── raymarch/             # Ray marching for implicit surfaces
├── cmake_modules/        # CMake find modules
├── main.cpp              # Entry point
├── CMakeLists.txt        # Build configuration
└── README.md             # This file
```

## Key Components

### Core Engine
- **CApp**: Main application class handling SDL2 window management and rendering loop
- **Scene**: Manages the 3D scene with objects, lights, and camera
- **Camera**: Implements perspective projection and ray generation
- **Ray**: Basic ray structure for ray-object intersection testing

### Objects
- **Object**: Base class for all renderable objects
- **objSphere**: Sphere primitive
- **objCube**: Cube primitive  
- **objectPlane**: Infinite plane
- **objectCylinder**: Cylinder primitive
- **objCone**: Cone primitive
- **composite**: Composite objects made from multiple primitives

### Materials and Textures
- **Material**: Base material class with lighting calculations
- **simpleMaterial**: Basic Phong shading material
- **simpleRefractive**: Refractive material for glass-like objects
- **Texture**: Various texture types (flat, checker, image, procedural)

### Advanced Features
- **Ray Marching**: Render implicit surfaces using signed distance functions
- **Normal Mapping**: Add surface detail without additional geometry
- **Procedural Noise**: Generate natural-looking textures

## Customizing the Scene

The scene is currently defined in the source code. To modify the rendered scene:

1. Open `scene.cpp` 
2. Modify the scene setup in the Scene class constructor
3. Add/remove objects, change materials, adjust lighting
4. Recompile and run

## Dependencies

- **CMake 3.28+**: Build system
- **C++ 17**: Language standard
- **SDL2**: Graphics and windowing
- **qbLinAlg**: Linear algebra operations (vectors, matrices)

## Troubleshooting

### Build Issues

**Error: `qbLinAlg/qbVector.h: No such file or directory`**
- Make sure you've cloned the qbLinAlg library to `include/qbLinAlg/`

**SDL2 not found**
- Install SDL2 development libraries for your platform
- On Windows, you may need to set the SDL2_PATH in CMakeLists.txt

### Runtime Issues

**Window doesn't appear**
- Check that your system supports SDL2
- Try running from command line to see error messages

**Slow rendering**
- The ray tracer is CPU-based and may be slow for complex scenes
- Reduce scene complexity or image resolution for faster rendering

## License

This project is provided as-is for educational purposes. Check individual component licenses, especially for the qbLinAlg dependency.

## Contributing

Feel free to submit issues and enhancement requests!