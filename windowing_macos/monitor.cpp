//
//  monitor.cpp
//  windowing_macos
//
//  Created by Camilo Sasuke on 27/05/21 19:48 BRT <3ThomasBS_!!
//
#include "framework.h"

void ns_monitor_cgrect(int i, CGRect * p);
void ns_workspace_cgrect(int i, CGRect * p);


namespace windowing_macos
{


   monitor::monitor()
   {

      //m_pMonitor2 = this;
   
   }


   monitor::~monitor()
   {
      

   }


::e_status monitor::get_monitor_rectangle(::RECTANGLE_I32 * prectangle)
{
   
   CGRect r;
   
   ns_monitor_cgrect((int) m_iIndex, &r);
   
   __copy(prectangle, r);
   
   return ::success;
   
}


::e_status monitor::get_workspace_rectangle(::RECTANGLE_I32 * prectangle)
{
   
   CGRect rectWorkspace;
   
   ns_workspace_cgrect((int) m_iIndex, &rectWorkspace);
   
   __copy(prectangle, rectWorkspace);
   
   return ::success;
   
}


} // namespace windowing_macos





void ns_main_monitor_cgrect(CGRect * p);



int GetMainScreenRect(RECTANGLE_I32 * pr)
{
   
   CGRect r;
   
   ns_main_monitor_cgrect(&r);
   
   __copy(pr, r);
   
   return true;
   
}
