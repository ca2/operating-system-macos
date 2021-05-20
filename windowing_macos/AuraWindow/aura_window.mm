//
//  aura_window.cpp
//  os
//
//  Created by Camilo Sasuke Tsumanuma on 6/8/13.
//  Copyright (c) 2013 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//
#include "framework.h"



void * new_aura_window(aura_window * paurawindow, CGRect rect, unsigned int uStyle)
{
   
   // rect.origin.x        = 0;
   
   rect.origin.y           = (int) [[NSScreen mainScreen]frame].size.height - (rect.origin.y + rect.size.height);
   
   // rect.size.width      = 0;
   // rect.size.height     = 0;
   
/* 
 
   rect.origin.x           = 100;
   rect.origin.y           = 100;
   rect.size.width         = 800;
   rect.size.height        = 500;
 
*/
   
   AuraWindow * pAuraWindow = [AuraWindow alloc];
   
   NSWindow * pNSWindow = pAuraWindow;
   
   paurawindow->m_paurawindow = pAuraWindow;
   
   paurawindow->m_paurawindow->m_paurawindow = paurawindow;
   
   //__block RoundWindow * proundwindow;
   
   ns_main_sync(^()
   {
                   
      auto id = [paurawindow->m_paurawindow initWithContentRect : rect styleMask : uStyle backing : NSBackingStoreBuffered defer : YES];
      
      if(!id)
      {
         
         NSLog(@"window wasn't created");
      
      }
                   
   });
   
   return (__bridge_retained void *) pNSWindow;
   
}


aura_window::aura_window()
{
   
   m_bDirty = false;
   
   m_bDestroying = false;
   
}


aura_window::~aura_window()
{
   
   m_paurawindow = nullptr;
   
}


void aura_window::aura_window_set_title(const char * pszTitle)
{
   
   if(m_bDestroying)
   {
      
      return;
      
   }
   
   char *pszText = strdup(pszTitle);
   
   ns_main_async(^
                 {
   
   NSString * str = [NSString stringWithUTF8String:pszText];
   
   [m_paurawindow setTitle:str];
                    ::free((void *)pszText);
                    
                 });
   
}


void aura_window::aura_window_get_title(char * pszTitle, int iSize)
{
   
   if(m_bDestroying)
   {
      
      return;
      
   }
   
   ns_main_sync(^
                {
                   
                  NSString * str = [m_paurawindow title];
                  
                  strncpy(pszTitle, [str UTF8String], iSize);
                   
                });
                
   
}


void aura_window::aura_window_destroy()
{
   
   if(m_paurawindow == NULL)
   {
      
      return;
      
   }
   
   [[NSNotificationCenter defaultCenter] removeObserver: m_paurawindow];

   [m_paurawindow setReleasedWhenClosed: YES];
   
   m_paurawindow->m_paurawindow = NULL;
   
   [m_paurawindow close];

}


void aura_window::aura_window_show()
{
   
   if(m_bDestroying)
   {
      
      return;
      
   }
   
   ns_main_async(^
   {
      
      [m_paurawindow->m_pwindowcontroller showWindow : m_paurawindow];
      
      [m_paurawindow windowDidExpose];

   });
   
}


void aura_window::aura_window_hide()
{
   
//   if(m_bDestroying)
//   {
//      
//      return;
//      
//   }

   ns_main_async(^
              {
                 
                 if(m_paurawindow)
                 {
                 
                    [m_paurawindow orderOut : nil];
                    
                 }
                 
                 if(m_paurawindow)
                 {
                    
                    aura_window_on_hide();
                    
                 }
                 
              });
   
}


void aura_window::aura_window_miniaturize()
{
 
   if(m_bDestroying)
   {
      
      return;
      
   }
   
   ns_main_async(^
                 {
                    
                    if([m_paurawindow styleMask] & NSWindowStyleMaskMiniaturizable)
                    {
                    
                       [m_paurawindow performMiniaturize: nil];
                       
                    }
                    else
                    {
                     
                       [m_paurawindow orderOut : nil];
                       
                       aura_window_iconified();
                       
                    }
                    
                    if(m_paurawindow->m_paurawindow == NULL)
                    {
                       
                       return;
                       
                    }
                    
                    //aura_window_on_miniaturize();
                    
                 });
   
}



void aura_window::aura_window_order_front()
{
   
   if(m_bDestroying)
   {
      
      return;
      
   }
   
   ns_main_async(^
              {
                 
                 [m_paurawindow orderFront : m_paurawindow];
                 
              });
   
}


void aura_window::aura_window_make_key_window()
{

   if(m_bDestroying)
   {
      
      return;
      
   }
   
   ns_main_async(^
              {
                 
                 [m_paurawindow makeKeyWindow];
                 
              });
   
}


void aura_window::aura_window_make_key_window_and_order_front()
{
   
   if(m_bDestroying)
   {
      
      return;
      
   }
   
   ns_main_async(^
              {
                 
                 [m_paurawindow makeKeyAndOrderFront: m_paurawindow];
                 
              });
   
}


void aura_window::aura_window_make_main_window()
{
   
   if(m_bDestroying)
   {
      
      return;
      
   }
   
   ns_main_async(^
              {
                 
                 [m_paurawindow makeMainWindow];
                 
              });
   
}


void aura_window::aura_window_redraw()
{
   
   if(m_bDestroying)
   {
      
      return;
      
   }
   
   auto proundwindow = m_paurawindow;
   
   if(proundwindow)
   {

   ns_main_async(^
                 {
                    
                   // m_bDirty = true;
                    
                    if(proundwindow)
                    {
                    
                       [proundwindow->m_pviewChildContent setNeedsDisplay:TRUE];
                       
                    }
   
                 });
      
   }
   
}


void aura_window::aura_window_redraw_sync()
{
   
   if(m_bDestroying)
   {
      
      return;
      
   }
   
   ns_main_sync(^
                 {
                    
                    [m_paurawindow display];
                    
                 });
   
}



void aura_window::aura_window_set_frame(CGRect r)
{
   
   if(m_bDestroying)
   {
      
      return;
      
   }
   
   ns_main_async(^
   {
      
      NSRect rect;
      
      NSRect rectScreen = [[[NSScreen screens] objectAtIndex:0] frame];
      
      rect.origin.x     = r.origin.x;
      rect.origin.y     = rectScreen.size.height    -     r.origin.y - r.size.height;
      rect.size   = r.size;
      
      [m_paurawindow setFrame : rect display: TRUE];

   });
   
}


void aura_window::aura_window_invalidate()
{
  
   if(m_bDestroying)
   {
      
      return;
      
   }
   
   ns_main_async(^
   {
      
      [m_paurawindow setViewsNeedDisplay : TRUE];
      
   });
   
}


//NSWindow * get_os_window_ns_window(oswindow hwnd)
//{
//   
//   return __nswindow(hwnd);
//   
//}



