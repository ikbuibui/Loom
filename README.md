# Loom

A framework for generative art, weaving parallel computation threads across heterogeneous hardware and platforms to create beautiful tapestries.

Loom leverages the power of **alpaka** for abstracting over parallel accelerators (CPUs, NVIDIA GPUs, AMD GPUs, etc.), **SDL3** for low-overhead windowing and rendering, and modern **C++** for expressive, safe, and performant code.

## Key Features

-   **Heterogeneous by Design**
-   **Modern C++ Architecture**
-   **Minimalist Rendering with SDL3**

## Getting Started

### Prerequisites

-   **C++20 Compiler**
-   **CMake**: Version 3.5 or newer.
-   [**SDL3**](https://github.com/libsdl-org/SDL)
-   [**alpaka3**](https://github.com/alpaka-group/alpaka3)

### Building Loom

Loom uses a standard CMake build process.

1.  **Clone the repository:**
    ```bash
    git clone https://github.com/your-username/loom.git
    cd loom
    ```

2.  **Configure with CMake:**
    You must enable at least one alpaka backend.
    You can use ccmake to configure the build.

3.  **Build the project:**
    ```bash
    cmake --build build --config Release -j
    ```

The executable will be located in the ```build/``` directory.


## Architecture Overview

Coming soon!

## Contributing

Contributions are welcome! However, Loom is currently in its early development, so make sure to talk to us before starting work on a feature.

## License

This project is licensed under the GNU General Public License v3.0 - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

-   The **[alpaka](https://github.com/alpaka-group)** team for creating an outstanding library for performance portability.
-   The **[SDL](https://www.libsdl.org/)** developers for their continued work on a fantastic cross-platform library.
