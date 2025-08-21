# Pano360
360Pano is a C++ application for creating 360-degree panoramic images by stitching six cube map photos into a seamless equirectangular panorama. It utilizes OpenCV for advanced image processing and is designed for high-resolution output, suitable for VR and immersive media applications.

# Features
Converts six cube map face images (front, back, left, right, top, bottom) into a high-quality 360 panorama.

Uses OpenCV C++ libraries for image processing, transformations, and stitching.

Includes seam blending between adjacent cube faces for smooth panoramic results.

Provides a command-line executable for easy use and integration.

Supports high-resolution outputs optimized for 4K displays.

# Getting Started

# Prerequisites

C++ compiler supporting C++17 or higher (tested with MSVC in Visual Studio 2022)

OpenCV (version 4.x recommended) built and installed for your platform

# Building the Project

Clone the repository and open the solution in Visual Studio or your preferred IDE.

Configure OpenCV paths in the project settings for includes and libraries.

Build the project for your target platform (e.g., Release x64).

Run the generated executable.

# Usage

Prepare six cube face images named as follows and place them alongside the executable (all .jpg):

File_0.jpg (Bottom)

File_1.jpg (Top)

File_2.jpg (Right)

File_3.jpg (Left)

File_4.jpg (Back)

File_5.jpg (Front)

Execute the program (e.g., 360Pano.exe).

The program will output a stitched panoramic image, typically saved in the executable directory.

# How It Works

Loads input cube face images.

Performs necessary rotations, flips, and transforms to align images.

Blends seams between adjacent faces to minimize visible transitions.

Converts cube map to a 360 equirectangular projection.

Saves and optionally displays the resulting panorama.

# Future Enhancements

Add a graphical user interface (GUI) for easier interaction.

Support command-line arguments for flexible input/output options.

Improve performance with multithreading or GPU acceleration.

Add input validation and error handling.

Extend to support other panorama formats and resolutions.

# License

This project is open source and available under the MIT License.