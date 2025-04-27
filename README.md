# OpenGL

This is a project with basic payground for OpenGL APIs.

# Platforms

1) Windows (Visual Studio 2022 build system). Check out 'window' project folder
2) Linux (CMake build system). Check out 'linux' project folder

# Repository structure

- dependencies/ - project dependencies
- engine/ - common OpenGL code
- windows/ - windows platform files and code
- linux/ - linux platform files and code
- tests/ - ui test & unit tests & test application

# Some dependencies

1) GLFW

This is a library which implements some common platform dependent tasks for you like window creation.

Ref: https://www.glfw.org/

2) Glew

This is a library which provides an access to platform dependent OpenGL APIs and features.
It is responsible for locating & loading correct OpenGL library or functions.

Ref: https://glew.sourceforge.net/

# Some other notes

1) OpenGL Initialization

This is a platform dependent process. It has 2 steps:

	1. The creation of OpenGL context and attaching it to the window.
	2. Loading all the necessary OpenGL APIs during runtime.

	The 2 step is handled by Glew library and the 1 step is managed by GLFW library.

# OpenGL docs & refs

- https://www.khronos.org/opengl/wiki/Getting_Started#Tutorials_and_How_To_Guides
- https://docs.gl/

- https://www.opengl.org/
- https://www.khronos.org/opengl/wiki/Getting_Started

- https://github.com/dbeyda/OpenGLRenderer
- https://github.com/htmlboss/OpenGL-Renderer
- https://learnopengl.com/Getting-started/Hello-Window
