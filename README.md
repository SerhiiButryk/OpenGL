# OpenGL

This is a project with basic payground for OpenGL APIs.

# Project dependencies

1) GLFW

This is a library which implements some common platform dependent tasks for you like window creation.

Ref: https://www.glfw.org/

2) Glew

This is a library which provides an access to platform dependent OpenGL APIs and features.
It is responsible for locating & loading correct OpenGL library or functions.

Ref: https://glew.sourceforge.net/

# Platforms

This is a Visual Studio project for windows platform

# Some notes

1) OpenGL Initialization

This is a platform dependent process. It has 2 steps:

	1. The creation of an OpenGL Context
	2. Loading all the necessary functions to use OpenGL.

	The 2 step is handled by Glew library.

# Get started

https://www.khronos.org/opengl/wiki/Getting_Started#Tutorials_and_How_To_Guides

# OpenGL docs

https://docs.gl/