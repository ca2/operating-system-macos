//
//  windowing.m
//  windowing_macos
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 01/03/22.
//
#include "framework.h"

#import <Cocoa/Cocoa.h>

//NSWindow * __nswindow(oswindow oswindow);


//NSWindow * get_os_window_ns_window(oswindow hwnd);


//NSWindow * get_os_window_ns_window(oswindow hwnd)
//{
//
//   return __nswindow(hwnd);
//
//}


CGWindowID nswindow_window_number(NSWindow * window)
{

   if(window == NULL)
   {

      return 0;

   }

   return (CGWindowID)[window windowNumber];
   
}




