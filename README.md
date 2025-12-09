# 42 fdf (Fil de Fer)

![Language](https://img.shields.io/badge/Language-C-blue)
![Score](https://img.shields.io/badge/Score-120%2F100-brightgreen)

---

## Table of Contents
- [Overview](#overview)
- [Matrix Library & Homogeneous Coordinates](#matrix-library--homogeneous-coordinates)
- [Isometric Projection](#isometric-projection)
- [Bresenham's Algorithm](#bresenhams-algorithm)
- [Controls](#controls)
- [Map Structure](#map-structure)
- [Installation](#installation)
- [Usage](#usage)
- [Features](#features)
- [Gallery](#gallery)
- [Author](#author)

---

## Overview

**FdF** is a project from the 42 curriculum that focuses on creating a simple 3D wireframe model representation of a landscape. By parsing a map file containing coordinates (x, y, z), the program renders a graphical projection linking these points using the **MiniLibX** library.

## Matrix Library & Homogeneous Coordinates

To handle 3D transformations efficiently, I implemented a custom matrix library included in the `libft` directory. In computer graphics, **homogeneous coordinates** allow us to represent affine transformations (linear transformations plus translation) using a single matrix multiplication.

A 3D point $(x, y, z)$ is represented as a 4-component vector $(x, y, z, w)$. For standard points in 3D space, $w = 1$.

$$
\mathbf{v} = \begin{bmatrix}
x \\
y \\
z \\
1
\end{bmatrix}
$$


This setup allows us to combine rotation, scaling, and translation into one $4\times4$ transformation matrix. For example, a translation matrix looks like this:

$$\begin{bmatrix} x' \\
y' \\
z' \\
1 \end{bmatrix} = \begin{bmatrix} 1 & 0 & 0 & t_x \\
0 & 1 & 0 & t_y \\
0 & 0 & 1 & t_z \\
0 & 0 & 0 & 1
\end{bmatrix} \cdot
\begin{bmatrix} x \\
y \\
z \\
1
\end{bmatrix}$$

## Isometric Projection

Isometric projection is a method for visually representing three-dimensional objects in two dimensions. It is an axonometric projection in which the three coordinate axes appear equally foreshortened and the angle between any two of them is $120^\circ$.

<div align="center">
<img width="799" height="312" alt="image" src="https://github.com/user-attachments/assets/b98b9111-bd9b-448e-aa26-a91217ae4f49" />
</div>


To achieve this in **FdF**, the grid is transformed by applying two specific rotations:
1.  **Rotation around the Z-axis:** typically $45^\circ$ ($\pi/4$ radians).
2.  **Rotation around the X-axis:** typically $\approx 35.264^\circ$ ($arcsin(tan(30^\circ$))).

After applying the rotation matrices, the z-coordinate is dropped to project the 3D data onto the 2D screen.

## Bresenham's Algorithm

To render the wireframe, points must be connected by lines. I implemented **Bresenham's line algorithm** to handle this. It is an incremental error algorithm that determines which pixels in a raster grid should be selected to form a close approximation of a straight line between two points.

The algorithm is highly efficient because it uses only integer arithmetic (addition, subtraction, and bit shifting), avoiding expensive floating-point operations during the rendering loop.

<div align="center">
<img width="542" height="460" alt="image" src="https://github.com/user-attachments/assets/a326c1ce-b296-457c-a1df-b2d39ab237c5" />
</div>

## Controls

| Key | Action |
| :--- | :--- |
| `ESC` | Close the window |
| `Arrows` | Move the map (Translate) |
| `+` / `-` | Zoom in / Zoom out |
| `W` / `S` | Rotate around X-axis |
| `A` / `D` | Rotate around Y-axis |
| `Q` / `E` | Rotate around Z-axis |
| `P` | Switch Projection (Isometric / Cabinet) |

## Map Structure

The program reads files with the `.fdf` extension. The file format is a grid of integers where each number represents the **altitude (z-value)** at that specific coordinate.

Example `42.fdf`:
```text
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0 10 10  0  0 10 10  0  0  0 10 10 10 10 10  0  0  0
0  0 10 10  0  0 10 10  0  0  0  0  0  0  0 10 10  0  0
0  0 10 10  0  0 10 10  0  0  0  0  0  0  0 10 10  0  0
0  0 10 10 10 10 10 10  0  0  0  0 10 10 10 10  0  0  0
0  0  0 10 10 10 10 10  0  0  0 10 10  0  0  0  0  0  0
0  0  0  0  0  0 10 10  0  0  0 10 10  0  0  0  0  0  0
0  0  0  0  0  0 10 10  0  0  0 10 10 10 10 10 10  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
```

Which looks like this

<img width="1948" height="1146" alt="Screenshot from 2025-12-09 21-04-00" src="https://github.com/user-attachments/assets/6e588a6a-dbdf-4c91-ae7c-a5157ce1ecf3" />

## Installation

To compile the project, run the following command in the root directory:

```bash
make
```

## Usage

Execute the program by providing a map file as an argument:

```bash
./fdf test_maps/42.fdf
```

## Features

* **Graphics:** Smooth isometric and cabinet rendering using MiniLibX.
* **Transformations:** Translation, Rotation, and Zoom support.
* **Events:** Full keyboard hook integration.
* **Parsing:** robust reading of `.fdf` formatted maps with variable line lengths.

## Gallery
<img width="1948" height="1146" alt="Screenshot from 2025-12-09 21-22-59" src="https://github.com/user-attachments/assets/e6c8fd3d-503a-4eab-b435-b066acf5db43" />
<img width="1948" height="1146" alt="Screenshot from 2025-12-09 21-23-32" src="https://github.com/user-attachments/assets/33f8284f-1d66-4d22-9d7b-b344a354acbf" />
<img width="1948" height="1146" alt="Screenshot from 2025-12-09 21-21-56" src="https://github.com/user-attachments/assets/0721cc2c-0570-45a8-853d-4d3281bf467b" />
<img width="1948" height="1146" alt="Screenshot from 2025-12-09 21-21-15" src="https://github.com/user-attachments/assets/8673cdad-3e9f-4115-b1a6-61938059520f" />

## Author
- **Name:** Daniel Zamora
- **GitHub:** [tekuron](https://github.com/tekuron)
- **42 Intra:** [danzamor](https://profile-v3.intra.42.fr/users/danzamor)
- **School:** 42
