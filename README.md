# OpenCV + VTK + QT
*Integrating VTK and OpenCV into a single Qt widget-based application*

This project shows two widgets in a [QT] application:
1. On left side, a VTK rendering, using [QVTK], of the [hello world example](https://lorensen.github.io/VTKExamples/site/Cxx/Rendering/CylinderRenderingProperties/) from the VTK's webpage 
2. On the right side, the morphology operation [erode](https://docs.opencv.org/2.4/doc/tutorials/imgproc/erosion_dilatation/erosion_dilatation.html) using [OpenCV], with the OpenGL-based widget [QTOpenCvViewerGl Widget] created by @Myzhar

The image presented is a frame capture (actually extracted) from the VTK rendering. For that, a time is created in order to capture a frame each **k** milliseconds.

### Considerations

* Initially, the project was created using QT Creator. However, I am not fan of that IDE/environment, however there is a `.pro` file
* Next the **QT Designer** was used it just to stick the QVTKWidget and the QTOpenCvViewerGl widget
* Project was thinking to work using **Visual Studio**. Then a [CMake] file is created manually
* Files `mainview.*` are related to the graphical interface
* Folders `src/` and `include/` contains source codes and headers respectively
* A class called `CAppManager` controls the required variables 
* Majority of code is using C++ 11

    | Tools         | Version |
    |---------------|---------|
    | CMake         | 3.10    |
    | Qt            | 5.10    |
    | VTK           | 8.01    |
    | Visual Studio | 2017    |

###### If you want to contribute? Great!

[QT]: <https://www.qt.io/>
[QVTK]: <https://www.vtk.org/doc/nightly/html/classQVTKWidget.html>
[CMake]: <https://cmake.org/>
[QTOpenCvViewerGl Widget]:<https://github.com/Myzhar/QtOpenCVViewerGl>
[OpenCV]: <https://opencv.org/>