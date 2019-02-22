/*
 * @filename Config.hpp
 * @author   James Metcalfe <p4112379@tees.ac.uk>
 * @date		 February 2019
 * @version  1.0
 *
 * @section DESCRIPTION
 *
 * Compilation configuration settings for the PWGL API.
*/

#pragma once
#ifndef __PWGL_CONFIG__
#define __PWGL_CONFIG__

#define PWGL_MAJOR_VERSION 1
#define PWGL_MINOR_VERSION 0

#ifndef PWGL_API_TYPE
#define PWGL_API_TYPE
#endif // !PWGL_API_TYPE

#ifndef PWGL_API_CLASS
#ifdef PWGL_EXPORTS
#define PWGL_API_CLASS __declspec(dllexport)
#else
#define PWGL_API_CLASS __declspec(dllimport)
#endif // PWGL_EXPORTS
#endif // !PWGL_API_CLASS

#ifndef PWGL_API_FUNC
#ifdef PWGL_EXPORTS
#define PWGL_API_FUNC extern "C" __declspec(dllexport)
#else
#define PWGL_API_FUNC extern "C" __declspec(dllimport)
#endif // PWGL_EXPORTS
#endif // !PWGL_API_FUNC

#endif // !__PWGL_CONFIG__
