#include "framework.h"
#include "windowing_system.h"


IMPLEMENT_FACTORY(windowing_system_appkit)
{

   pfactory->add_factory_item < ::windowing_system_appkit::windowing_system, ::windowing_system::windowing_system >();

}


