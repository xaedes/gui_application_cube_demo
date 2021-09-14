
#include <iostream>
#include "gui_application/version.h"
#include "simple_draw_gl/version.h"
#include "gui_application_cube_demo/version.h"

#include "gui_application_cube_demo/cube_demo.h"



int main()
{
    std::cout << "gui_application::Version " << gui_application::VersionMajor << "." << gui_application::VersionMinor << "." << gui_application::VersionPatch << std::endl;
    std::cout << "simple_draw_gl::Version " << simple_draw_gl::VersionMajor << "." << simple_draw_gl::VersionMinor << "." << simple_draw_gl::VersionPatch << std::endl;
    std::cout << "gui_application_cube_demo::Version " << gui_application_cube_demo::VersionMajor << "." << gui_application_cube_demo::VersionMinor << "." << gui_application_cube_demo::VersionPatch << std::endl;
    gui_application_cube_demo::CubeDemo app;
    return app.run();
}

