/**
*
* This file should have all public library APIs. Should be included by the client code.
* So we can use one include to access all available APIs potentially.
*
*/
#pragma once

#include <app/Application.h>
#include <ui/UIComponent.h>
#include <ui/Widgets.h>

#include <common/Log.h>

#include <imgui/imgui.h>

#include <opengl/render/Renderer.h>
#include <opengl/render/RenderGL.h>
#include <opengl/render/RenderGLBase.h>
#include <opengl/shapes/Line.h>
#include <opengl/shapes/Rectangle.h>
#include <opengl/shapes/Triangle.h>

#include <window/input/Input.h>

#include <glm/gtc/type_ptr.hpp>