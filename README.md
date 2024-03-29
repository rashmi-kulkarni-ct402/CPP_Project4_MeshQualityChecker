# Mesh Quality Checker Project

MeshQualityChecker is a C++ library designed to analyze the quality of 3D triangular meshes. It provides various metrics to evaluate the mesh quality, including surface area, mesh density, aspect ratio, and aspect ratio skewness. The library also categorizes triangles into good and bad based on their quality.

## Features

- Calculate the total surface area of a triangular mesh.
- Compute the mesh density, which indicates the distribution of triangles in the mesh.
- Evaluate the aspect ratio of triangles to determine their elongation.
- Calculate the aspect ratio skewness to assess the uniformity of triangle shapes.
- Categorize triangles into good and bad based on their aspect ratios.

## Classes

- [Point3D](Point3D.h): Class representing a 3D point.
- [Triangle](Triangle.h): Class representing a triangle in a 3D mesh.
- [Triangulation](Triangulation.h): Class representing the triangulation of a 3D mesh.
- [StlReader](StlReader.h): Class for reading STL files and populating the Triangulation object.
- [TxtWriter](TxtWriter.h): Class for writing the results of the mesh quality analysis to text files.
- [FileTypeChecker](FileTypeChecker.h): Class for checking the file type of the input mesh file.

## Usage

1. Create a `Triangulation` object and populate it with the mesh data using the `StlReader` class.
2. Instantiate a `MeshQualityChecker` object with the triangulation.
3. Call the various calculation methods to evaluate the mesh quality.
4. Use the `categorizeTriangles` method to classify triangles into good and bad categories.
5. Optionally, use the `TxtWriter` class to write the results to text files.
