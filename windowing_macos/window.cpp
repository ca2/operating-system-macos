//
//  macos_window.cpp
//  aura
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2013-09-17.
//
//

#include "framework.h"
#include "window_impl.h"
#include "acme/constant/message.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/parallelization/synchronous_lock.h"
#include "aura/user/user/interaction_prodevian.h"
#include "aura/user/user/interaction_impl.h"
#include "aura/user/user/box.h"
#include "aura/message/user.h"
#include "aura_macos/interaction_impl.h"
#include "acme/parallelization/message_queue.h"
#include "aura/graphics/graphics/graphics.h"
//#include "aura/graphics/graphics/_graphics.h"
#include "aura/graphics/image/drawing.h"
#include "aura/platform/session.h"
#include "aura/user/user/user.h"
#include "aura/message/user.h"
#include <CoreGraphics/CoreGraphics.h>


bool macos_get_cursor_position(POINT_I32 * ppointCursor);


void ns_main_async(dispatch_block_t block);

void ns_set_cursor(::windowing::cursor * pwindowingcursor);
::windowing::cursor * ns_get_cached_cursor();

#define WHEEL_DELTA 120

void * new_macos_window(macos_window * papexwindow, CGRect rect, unsigned int uStyle);


namespace windowing_macos
{


   window::window()
   {
      
      m_pWindow4 = this;
      m_pmacoswindowing = nullptr;
      m_pNSCursorLast = nullptr;
      m_pwindowCapture = nullptr;
      
   }


   window::~window()
   {
      
      
   }


   void window::on_message_create(::message::message * pmessage)
   {
      
      
      
   }


   void window::on_message_destroy(::message::message * pmessage)
   {
      
      ns_main_sync(^{
         
         
         ::macos_window::macos_window_hide();
         
         ::macos_window::macos_window_destroy();
         
         
      });
      
      
   }


   void window::install_message_routing(channel * pchannel)
   {

      ::windowing::window::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_create, pchannel, this, &window::on_message_create);

      auto puserinteraction = m_puserinteractionimpl->m_puserinteraction;

      auto pimpl = m_puserinteractionimpl.m_p;

      if (!puserinteraction->m_bMessageWindow)
      {

         //MESSAGE_LINK(e_message_redraw, pchannel, pimpl, &::user::interaction_impl::_001OnRedraw);
         //MESSAGE_LINK(e_message_apply_visual, pchannel, pimpl, &::user::interaction_impl::_001OnApplyVisual);


         //#ifndef LINUX
         //MESSAGE_LINK(e_message_reposition, pchannel, this, &window::_001OnMove);
         //MESSAGE_LINK(e_message_size, pchannel, this, &window::_001OnSize);
         //#endif


         //MESSAGE_LINK(e_message_show_window, pchannel, this, &window::_001OnShowWindow);
         //MESSAGE_LINK(e_message_kill_focus, pchannel, this, &window::_001OnKillFocus);
         //MESSAGE_LINK(e_message_set_focus, pchannel, this, &window::_001OnSetFocus);
         //MESSAGE_LINK(e_message_set_cursor, pchannel, this, &window::_001OnSetCursor);

      }

      //MESSAGE_LINK(e_message_destroy_window, pchannel, pimpl, &::user::interaction_impl::_001OnDestroyWindow);

   //   MESSAGE_LINK(WM_ACTIVATE, pchannel, this, &window::_001OnActivate);
     // MESSAGE_LINK(WM_DWMNCRENDERINGCHANGED, pchannel, this, &window::_001OnDwmNcRenderingChanged);

      pimpl->install_message_routing(pchannel);


      MESSAGE_LINK(e_message_destroy, pchannel, this, &window::on_message_destroy);

      //MESSAGE_LINK(e_message_create, pchannel, pimpl, &::user::interaction_impl::_001OnPrioCreate);

   }


   void window::create_window(::user::interaction_impl * pimpl)
   {

      //if (::is_window(get_handle()))
      //{

      //   DestroyWindow();

      //}

      //      ASSERT(lpszClassName == nullptr || __is_valid_string(lpszClassName) ||
      //       __is_valid_atom(lpszClassName));
   //      ENSURE_ARG(pusersystem->m_createstruct.lpszName == nullptr || __is_valid_string(pusersystem->m_createstruct.lpszName));

      // allow modification of several common create parameters
      //::user::system createstruct;
      //      pusersystem->m_createstruct.hwndParent = hWndParent;
      //   pusersystem->m_createstruct.hMenu = hWndParent == nullptr ? nullptr : nIDorHMenu;
      
      auto puserinteraction = pimpl->m_puserinteraction;
      
      auto pusersystem = puserinteraction->m_pusersystem;
      
      //pusersystem->m_createstruct.hMenu = nullptr;
      //      pusersystem->m_createstruct.hInstance = ::aura::get_system()->m_hInstance;
      //pusersystem->m_createstruct.lpCreateParams = lpParam;

      if (!puserinteraction->pre_create_window(pusersystem))
      {

         throw ::exception(error_failed);

      }

      //hook_window_create(puserinteraction);

      //CGRect rectangle_i32;

      rectangle_i32 rectParam;

   //      rectParam.left = m_pusersystem->m_createstruct.x;
   //      rectParam.top = pusersystem->m_createstruct.y;
   //      rectParam.right = pusersystem->m_createstruct.x + pusersystem->m_createstruct.cx;
   //      rectParam.bottom = pusersystem->m_createstruct.y + pusersystem->m_createstruct.cy;

   //      copy(rectangle, rectParam);
   //
   //      if (pusersystem->m_createstruct.hwndParent == MESSAGE_WINDOW_PARENT)
   //      {
   //
   //         return true;
   //
   //      }
   //      else
   //      {

         unsigned uStyle = 0;

         if(puserinteraction->m_ewindowflag & ::e_window_flag_miniaturizable)
         {

   #define NSWindowStyleMaskMiniaturizable (1 << 2)

            uStyle |= NSWindowStyleMaskMiniaturizable;

         }
      
         auto rectangle = puserinteraction-> window_rectangle();
      
         CGRect cgrect;
      
         copy(cgrect, rectangle);
      
         //__todo?
         //windowing()->copy(cgrect, rectangle);
         //or
         //display()->copy(cgrect, rectangle);
         //because rectangle origin is top-left
         //and because cgrect origin is bottom-left and,
         //the origin of screen is at bottom.
      
      m_puserinteractionimpl = pimpl;
      
      puserinteraction->m_puserinteractionTopLevel = puserinteraction;
      
      puserinteraction->m_pwindow = this;
      
      pimpl->m_pwindow = this;
      
      install_message_routing(puserinteraction);

      
      auto psession = m_pcontext->m_pacmesession->m_paurasession;

      auto puser = psession->user();

      auto pwindowing = (::windowing_macos::windowing *) puser->windowing()->m_pWindowing4;
      
      m_pmacoswindowing = dynamic_cast < class windowing * >(pwindowing);
      
      m_pwindowing = pwindowing;
      
      pimpl->m_pwindowing = pwindowing;

         auto pNSWindow = new_macos_window(this, cgrect, uStyle);
      
         set_os_data(pNSWindow);
      
      set_oswindow(this);

      pwindowing->m_nsmap[m_pnswindow] = this;
      
         puserinteraction->set_position(::top_left(rectParam), ::user::e_layout_window);

         puserinteraction->set_size(::size_i32(rectParam), ::user::e_layout_window);

         puserinteraction->m_pthreadUserInteraction = ::get_task();

         //puserinteraction->place(rectParam);



         //oswindow_assign(m_oswindow, this);

      //}

      auto lresult = puserinteraction->send_message(e_message_create); //
      //, 0, //(lparam)&cs);

      bool bOk = true;

      //if (!unhook_window_create() || lresult == -1)
      if (lresult == -1)
      {

         bOk = false;
         
         set_finish();

         //children_post_quit();

         //children_wait_quit(one_minute());

         //PostNcDestroy();        // cleanup if CreateWindowEx fails too soon
         
         throw exception(error_resource);

      }

      //if(pusersystem->m_createstruct.style & WS_VISIBLE)
      //if(pusersystem->m_.style & WS_VISIBLE)
      if(puserinteraction->const_layout().design().is_screen_visible())
      {

         puserinteraction->display();

         puserinteraction->set_need_redraw();

         puserinteraction->post_redraw();

         //;//macos_window_show();

      }

      puserinteraction->set_need_layout();

      puserinteraction->increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_P_NOTE(this, "native_create_window"));

      puserinteraction->m_ewindowflag |= e_window_flag_window_created;
      
      if(!bOk)
      {
         
         throw ::exception(error_resource);
         
      }

   }


   //// for child windows
   //bool interaction_impl::pre_create_window(::user::system * pusersystem)
   //{
   //   /*      if (pusersystem->m_createstruct.lpszClass == nullptr)
   //    {
   ///xcore/app/aura/node/macos/macos_interaction_impl.cpp:712:44: No member named 'window_rectangle' in 'user::interaction_impl'       // make sure the default user::interaction class is registered
   //    VERIFY(__end_defer_register_class(__WND_REG, &pusersystem->m_createstruct.lpszClass));
   //
   //    // no WNDCLASS provided - use child user::interaction default
   //    ASSERT(pusersystem->m_createstruct.style & WS_CHILD);
   //    }*/
   //   return true;
   //}

   void window::macos_window_add_ref()
   {

      increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_P_NOTE(this, "macos_window_add_ref"));
      
      auto puserinteraction = m_puserinteractionimpl->m_puserinteraction;

      puserinteraction->increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_P_NOTE(this, "macos_window_add_ref"));

   }


   void window::macos_window_dec_ref()
   {
      
      auto puserinteraction = m_puserinteractionimpl->m_puserinteraction;

      puserinteraction->decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_P_NOTE(this, "macos_window_dec_ref"));

      decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_P_NOTE(this, "macos_window_dec_ref"));

   }


   void window::set_keyboard_focus()
   {

      macos_window_make_first_responder();

      //return ::success;

   }


   void window::set_active_window()
   {

      macos_window_make_key_window_and_order_front();
      
      auto pwindowing = (::windowing_macos::windowing *) m_pwindowing->m_pWindowing4;
      
      pwindowing->m_pwindowActive = this;

      //return ::success;

   }


   void window::set_tool_window(bool bSet)
   {
      
      auto pwindowing = (::windowing_macos::windowing *) m_pwindowing->m_pWindowing4;
      
      pwindowing->_defer_dock_application(!bSet);

      //return ::success;
      
   }


   void window::set_foreground_window()
   {
      
      macos_window_order_front();
      
      //return ::success;
      
   }


   bool window::is_active_window() const
   {

      return macos_window_is_key_window();

   }

   
   bool window::has_keyboard_focus() const
   {
      
      bool bHasKeyboardFocus = macos_window_is_key_window();
   
      return bHasKeyboardFocus;
   
   }


   void window::window_show()
   {
      
      //macos_window_show();
      
      ::windowing::window::window_show();
      
   }


   void window::show_window(const ::e_display &edisplay, const ::e_activation &eactivation)
   {

      //windowing_output_debug_string("\n::windowing_macos::window::show_window 1");
      
      if(edisplay == e_display_iconic)
      {
       
         macos_window_miniaturize();
         
      }
      else if(edisplay == e_display_restore)
      {
         
         macos_window_show();
       
         macos_window_make_key_window_and_order_front();
         
         macos_window_make_main_window();
         
         nsapp_activate_ignoring_other_apps(1);
         
      }
      else if(edisplay == e_display_restored)
      {
         
         macos_window_show();
       
         macos_window_make_key_window_and_order_front();
         
         macos_window_make_main_window();
         
         nsapp_activate_ignoring_other_apps(1);
         
      }
      else if(edisplay == e_display_none || edisplay == e_display_hide)
      {
         
         macos_window_resign_key();
         macos_window_hide();
         
      }

      //return ::success;

   }


   void window::set_mouse_cursor(::windowing::cursor * pcursorParam)
   {
      
      ::pointer < ::windowing::cursor > pcursor = pcursorParam;

      if (::is_null(pcursor))
      {

         throw exception(error_invalid_parameter);

      }
      
      if(pcursor == m_pcursor)
      {
         
         return;
         
      }

      auto pcursorMacos = pcursor.cast < cursor >();

      if (::is_null(pcursorMacos))
      {

         throw exception(error_invalid_parameter);

      }
      
      if(::is_null(pcursorMacos->m_pNSCursor)
         && (pcursorMacos->m_pimage
             || pcursor->m_ecursor != e_cursor_none))
      {
         
         pcursorMacos->_create_os_cursor();
         
      }
      
      if (ns_get_cached_cursor() == pcursor)
      {

         return;

      }

      ns_set_cursor(pcursor);

   }


   ::point_i32 window::get_mouse_cursor_position()
   {
      
      return m_pointMouseCursor;
      
   }
   

   bool window::set_window_position(const class ::zorder& zorder, i32 x, i32 y, i32 cx, i32 cy, const ::e_activation& eactivation, bool bNoZorder, bool bNoMove, bool bNoSize, bool bShow, bool bHide)
   {
      
      ns_main_async(^(){
         
         CGRect r;

         macos_window_get_frame(&r);
         
         if(!bNoMove)
         {
            
            r.origin.x = x;
            
            r.origin.y = y;
            
         }
         
         if(!bNoSize)
         {
         
            r.size.width = cx;
         
            r.size.height = cy;
            
         }
            
         macos_window_set_frame(r);
         
         if(bShow)
         {
          
            macos_window_defer_show();
            
         }

      }
                    
      );

      return true;

   }


   void window::set_mouse_capture()
   {

      auto pwindowing = (class windowing *) windowing()->m_pWindowing4;
      
      if(!pwindowing)
      {
         
         throw exception(error_wrong_state);
         
      }
      
      pwindowing->m_pwindowCapture = this;

      //return ::success;

   }


   void window::update_screen()
   {
      
      macos_window_redraw();
      
   }



   void window::macos_window_draw(CGContextRef cgc, CGSize sizeWindowParam)
   {

      ::size_i32 sizeWindow(sizeWindowParam.width, sizeWindowParam.height);

      #ifdef EXTRALOG

      static int s_iLastExact = -1;

      string str;

      string strFormat;

      strFormat.Format("|-> window size_i32 %d, %d", sizeWindow.cx, sizeWindow.cy);

      string strSize;

      if(sizeLast != sizeWindow)
      {

         sizeLast = sizeWindow;

         strSize = strFormat;

      }

      str += strFormat;

      rectangle_i32 rect1 = puserinteraction->window_rectangle();

      if(rect1.size() != rectLast.size())
      {

         rectLast = rect1;

         // xxxlog output_debug_string("different window rectangle_i32 size_i32 (1)");

      }

   #endif

      auto tickNow = ::time::now();

      auto tickEllapsed = tickNow - m_puserinteractionimpl->m_timeLastDeviceDraw;

      if(tickEllapsed < 12_ms)
      {

         // xxxlog
         //output_debug_string("\n\nwarning: macos_window_draw more than 80FPS!!! Ellapsed: " + str::from(tickEllapsed) + "ms.\n\n");

      }

      m_puserinteractionimpl->m_timeLastDeviceDraw = tickNow;

      ::user::device_draw_life_time devicedrawlifetime(m_puserinteractionimpl);

      critical_section_lock slDisplay(m_puserinteractionimpl->cs_display());

      ::pointer < ::graphics::graphics > pbuffer = m_puserinteractionimpl->m_pgraphics;

      if(!pbuffer)
      {

         return;

      }
      
      auto puserinteraction = m_puserinteractionimpl->m_puserinteraction;
      
      if(!puserinteraction)
      {
      
         return;

      }
         
      auto g = __create < ::draw2d::graphics >();

      g->attach(cgc);
      
      //auto rectClient = puserinteraction->client_rectangle();

      g->set_alpha_mode(::draw2d::e_alpha_mode_set);

      synchronous_lock slGraphics(pbuffer->synchronization());
      
      synchronous_lock sl1(pbuffer->get_screen_sync());

      ::image_pointer & imageBuffer2 = pbuffer->get_screen_image();

      if (!imageBuffer2)
      {

         output_debug_string("NOT DRAWING? <<---- search and bp here !imageBuffer2 ");

         return;

      }
      
      slGraphics.unlock();

   #ifdef EXTRALOG

      if(strSize.has_char())
      {

         s_iLastExact = -1;

      }

      if(s_iLastExact > 0)
      {


         if(s_iLastExact % 10 == 0)
         {

            str = "\n.";

         }
         else
         {

            str = ".";

         }
         
         strFormat.Format("%d", iAge);

         str += strFormat;
         
         output_debug_string(str);
         
      }
      else
      {
         
         INFO(str);
         
      }
      
   #endif

      ::size_i32 sizeMin = imageBuffer2->size().minimum(sizeWindow);
      
      ::rectangle_f64 rectangleSource(sizeMin);
      
      image_source imagesource(imageBuffer2, rectangleSource);
      
      ::rectangle_f64 rectangleTarget(sizeMin);
      
      image_drawing_options imagedrawingoptions(rectangleTarget);
      
      image_drawing imagedrawing(imagedrawingoptions, imagesource);

      g->draw(imagedrawing);
      
      m_puserinteractionimpl->m_bPendingRedraw = false;
      
      m_puserinteractionimpl->m_timeLastRedraw.Now();

   }


//   bool window::macos_window_key_down(unsigned int uiKeyCode)
//   {
//
//      auto puserinteraction = m_puserinteractionimpl->m_puserinteraction;
//
//      if(puserinteraction == nullptr)
//      {
//
//         return false;
//
//      }
//
//      auto pkey  = __create_new < ::message::key >();
//
//      pkey->m_id = e_message_key_down;
//
//      pkey->m_strText = pszUtf8;
//
//      pkey->m_nChar = uiKeyCode;
//
//      puserinteraction->send(pkey);
//
//      return true;
//
//   }
//
//
//   bool window::macos_window_key_up(unsigned int uiKeyCode)
//   {
//
//      ::pointer < ::user::message > spbase;
//
//      auto pkey  = __new(::message::key);
//
//      pkey->m_id = e_message_key_up;
//
//      pkey->m_nChar = uiKeyCode;
//
//      spbase = pkey;
//
//      auto puserinteraction = m_puserinteractionimpl->m_puserinteraction;
//
//      if(puserinteraction == nullptr)
//      {
//
//         return false;
//
//      }
//
//      puserinteraction->send(spbase);
//
//      return spbase->m_bRet;
//
//   }

#define _NEW_MESSAGE(pmessage, type, emessage) \
auto pmessage = __create_new < type >(); \
pmessage->m_oswindow = m_oswindow; \
pmessage->m_pwindow = this; \
pmessage->m_atom = emessage

   bool window::macos_window_key_down(unsigned int virtualKey, unsigned int scanCode, const char * pszUtf8)
   {
      
      _NEW_MESSAGE(pkey, ::message::key, e_message_key_down);

      pkey->m_iVirtualKey = virtualKey;
      pkey->m_nScanCode = scanCode;

      if(::is_set(pszUtf8) && ansi_len(pszUtf8) > 0)
      {

         pkey->m_strText = pszUtf8;
      
      }
       
      if(pkey->m_strText.length() == 1)
      {
          
          auto character = pkey->m_strText[0];
          
          if(character >= 'a' && character <= 'z')
          {
              
              pkey->m_ekey = (::user::enum_key) ((int)::user::e_key_a + character - 'a');
              
          }
          else if(character >= 'A' && character <= 'Z')
          {
              
              pkey->m_ekey = (::user::enum_key) ((int) ::user::e_key_a + character - 'A');
              
          }
          else if(character >= '0' && character <= 'Z')
          {
              
              pkey->m_ekey = (::user::enum_key) ((int) ::user::e_key_0 + character - '0');
              
          }

      }

      post_message(pkey);
    
       const char * psz = pszUtf8;
       
       if(::is_set(psz))
       {
          
       while(true)
       {
           
           auto len = utf8_len(psz);
           
           string strChar(psz, len);
           
           psz += len;
           
           auto codepoint = unicode_index(strChar);
           
          _NEW_MESSAGE(pkey, ::message::key, e_message_char);
          
          pkey->m_nChar = codepoint;
           
           post_message(pkey);

           if(!*psz)
           {
               
               break;
           }
           
       }
           
       }
    
      return true;

   }


   bool window::macos_window_key_up(unsigned int vk, unsigned int scan)
   {

      auto puserinteraction = m_puserinteractionimpl->m_puserinteraction;

      if(puserinteraction == nullptr)
      {

         return false;

      }

      _NEW_MESSAGE(pkey, ::message::key, e_message_key_up);

      pkey->m_iVirtualKey = vk;
      pkey->m_nScanCode = scan;

      puserinteraction->send(pkey);

      return true;

   }


   void window::macos_window_mouse_down(int iButton, double x, double y)
   {
      
      m_pointMouseCursor.x = x;
      
      m_pointMouseCursor.y = y;

      //::pointer < ::user::message > spbase;

      if (!this->is_active_window())
      {

         try
         {

            _NEW_MESSAGE(pmouseactivate, ::message::mouse_activate, e_message_mouse_activate);

            pmouseactivate->m_wparam = 0;
            pmouseactivate->m_lparam = 0;

            send_message(pmouseactivate);

            if (pmouseactivate->m_lresult == e_mouse_activate || pmouseactivate->m_lresult == e_mouse_activate_no_activate_and_eat)
            {

               _NEW_MESSAGE(pactivate, ::message::activate, e_message_activate);

               pactivate->m_wparam = __MAKE_LONG(e_activate_click_active, 0);
               pactivate->m_lparam = 0;

               post_message(pactivate);

            }

         }
         catch (...)
         {

         }

      }

      {

//         auto pmouse = __create_new < ::message::mouse > ();

//         ::atom id;
         
         if (iButton == 1)
         {
            
            _NEW_MESSAGE(pmouse, ::message::mouse, e_message_right_button_down);
            pmouse->m_point.x = x;
            pmouse->m_point.y = y;
            post_message(pmouse);

         }
         else
         {

            _NEW_MESSAGE(pmouse, ::message::mouse, e_message_left_button_down);
            pmouse->m_point.x = x;
            pmouse->m_point.y = y;
            post_message(pmouse);
         }
         
//         pmouse->set(this, this, id, 0, __MAKE_LPARAM(x, y));


      }

   }


   void window::macos_window_mouse_up(int iButton, double x, double y)
   {
      
      m_pointMouseCursor.x = x;
      
      m_pointMouseCursor.y = y;
      
      //auto pmouse = __create_new < ::message::mouse >();

      //::atom id;

      if (iButton == 1)
      {

         _NEW_MESSAGE(pmouse, ::message::mouse, e_message_right_button_up);
         pmouse->m_point.x = x;
         pmouse->m_point.y = y;
         post_message(pmouse);

      }
      else
      {

         _NEW_MESSAGE(pmouse, ::message::mouse, e_message_left_button_up);
         pmouse->m_point.x = x;
         pmouse->m_point.y = y;
         post_message(pmouse);


      }
      
//      pmouse->set(this, this, id, (wparam) 0, __MAKE_LPARAM(x, y));
//
//      post_message(pmouse);

   }


   void window::macos_window_double_click(int iButton, double x, double y)
   {

      //auto pmouse = __create_new < ::message::mouse >();
      
      //::atom id;

      if (iButton == 1)
      {

         _NEW_MESSAGE(pmouse, ::message::mouse, e_message_right_button_double_click);
         pmouse->m_point.x = x;
         pmouse->m_point.y = y;
         post_message(pmouse);

         //id = e_message_right_button_double_click;

      }
      else
      {

         _NEW_MESSAGE(pmouse, ::message::mouse, e_message_left_button_double_click);
         pmouse->m_point.x = x;
         pmouse->m_point.y = y;
         post_message(pmouse);
         //id = e_message_left_button_double_click;

      }

//      pmouse->set(this, this, id, (wparam) 0, __MAKE_LPARAM(x, y));
//
//      post_message(pmouse);

   }


   void window::macos_window_mouse_moved(double x, double y, unsigned long ulAppleMouseButton)
   {
      
//      if(is_destroying())
//      {
//
//         return;
//
//      }
      
      m_pointMouseCursor.x = x;
      
      m_pointMouseCursor.y = y;
      
      bool bOk = true;

      auto puserinteraction = m_puserinteractionimpl->m_puserinteraction;

      if(!puserinteraction)
      {

         return;

      }
      
      if(puserinteraction->m_timeMouseMove.elapsed() < puserinteraction->m_timeMouseMoveIgnore)
      {
         
         //printf("mouse_move_ignored %f, %f\n", x, y);

         bOk = false;

      }

      if(bOk)
      {

//            printf("mouse_move_\"accepted\" %f, %f\n", x, y);

         puserinteraction->m_timeMouseMove.Now();

         puserinteraction->m_pointMouseMove.x = x;

         puserinteraction->m_pointMouseMove.y = y;

//            if(false)
//            {
//
//               if(pinteraction->m_millisMouseMovePeriod > 0)
//               {
//
//                  ::size_i32 sizeDistance((pinteraction->m_pointMouseMoveSkip.x - pinteraction->m_pointMouseMove.x),
//                     (pinteraction->m_pointMouseMoveSkip.y - pinteraction->m_pointMouseMove.y));
//
//                  if(!pinteraction->m_millisMouseMoveSkip.timeout(pinteraction->m_millisMouseMovePeriod)
//                     && sizeDistance.cx * sizeDistance.cx + sizeDistance.cy * sizeDistance.cy < pinteraction->m_iMouseMoveSkipSquareDistance)
//                  {
//
//                     pinteraction->m_iMouseMoveSkipCount++;
//
//                     pinteraction->m_bMouseMovePending = true;
//
//                     if(pinteraction->m_iMouseMoveSkipCount == 2)
//                     {
//
//                        //output_debug_string("\nmmv>skip 2!");
//
//                     }
//                     else if(pinteraction->m_iMouseMoveSkipCount == 5)
//                     {
//
//                        //output_debug_string("\nmmv>Skip 5!!!");
//
//                     }
//                     else if(pinteraction->m_iMouseMoveSkipCount == 10)
//                     {
//
//                        //output_debug_string("\nmmv>SKIP 10 !!!!!!!!!");
//
//                     }
//
//                     return true;
//
//                  }
//
//                  pinteraction->m_iMouseMoveSkipCount = 0;
//
//                  pinteraction->m_pointMouseMoveSkip = pinteraction->m_pointMouseMove;
//
//               }
//
//            }

      }

      if(!bOk)
      {

         return;

      }
      
      
      _NEW_MESSAGE(pmouse, ::message::mouse, e_message_mouse_move);
      pmouse->m_point.x = x;
      pmouse->m_point.y = y;
      
      //::atom id = e_message_mouse_move;
      
      //wparam wparam = 0;
      
      //lparam lparam = __MAKE_LPARAM(x, y);
      
      if(ulAppleMouseButton & 1)
      {

         pmouse->m_nFlags |= ::user::e_button_state_left;

      }

      if(ulAppleMouseButton & 2)
      {

         pmouse->m_nFlags |= ::user::e_button_state_right;

      }
      
//      auto pmouse = __create_new < ::message::mouse >();
//
//      pmouse->set(this, this, id, wparam, lparam);

      post_message(pmouse);
      
   }


   void window::macos_window_mouse_dragged(double x, double y, unsigned long ulAppleMouseButton)
   {
      
      _NEW_MESSAGE(pmouse, ::message::mouse, e_message_mouse_move);
      pmouse->m_point.x = x;
      pmouse->m_point.y = y;

      
//      atom id = e_message_mouse_move;

  //    wparam wparam = 0;

    //  lparam lparam = __MAKE_LPARAM(x, y);

      if(ulAppleMouseButton & 1)
      {

         pmouse->m_nFlags |= ::user::e_button_state_left;

      }

      if(ulAppleMouseButton & 2)
      {

         pmouse->m_nFlags |= ::user::e_button_state_right;

      }
//
//      auto pmouse = __create_new < ::message::mouse >();
//
//      pmouse->set(this, this, id, wparam, lparam);

      post_message(pmouse);

   }


   void window::macos_window_mouse_wheel(double deltaY, double x, double y)
   {

      
      _NEW_MESSAGE(pwheel, ::message::mouse_wheel, e_message_mouse_wheel);
      pwheel->m_point.x = x;
      pwheel->m_point.y = y;

      //atom id = e_message_mouse_wheel;

      pwheel->m_Δ = deltaY * WHEEL_DELTA / 3.0;

      //wparam wparam = pwheel-delta << 16;

      //lparam lparam = __MAKE_LPARAM(x, y);

      //auto pwheel  = __create_new < ::message::mouse_wheel > ();
      
      //pwheel->set(this, this, id, wparam, lparam);

      post_message(pwheel);

   }


   void window::macos_window_resized(CGRect rectangle)
   {
      
      {
      
         _NEW_MESSAGE(preposition, ::message::reposition, e_message_reposition);
         preposition->m_point.x = rectangle.origin.x;
         preposition->m_point.y = rectangle.origin.y;

         
//         atom id = e_message_reposition;
//
//         wparam wparam = 0;
//
//         lparam lparam = __MAKE_LPARAM(rectangle.origin.x, rectangle.origin.y);
//
//         auto pmove  = __create_new < ::message::reposition > ();
//
//         pmove->set(this, this, id, wparam, lparam);

         post_message(preposition);
         
      }
      
      {

         _NEW_MESSAGE(psize, ::message::size, e_message_size);
         psize->m_size.cx = rectangle.size.width;
         psize->m_size.cy = rectangle.size.height;

//         atom id = e_message_size;
//
//         wparam wparam = 0;
//
//         lparam lparam = __MAKE_LPARAM(rectangle.size.width, rectangle.size.height);
//
//         auto psize  = __create_new < ::message::size > ();
//
//         psize->set(this, this, id, wparam, lparam);

         post_message(psize);
         
      }

      //return;

   //      if(puserinteraction == nullptr)
   //      {
   //
   //         return;
   //
   //      }
   //
   //      //
   //      if(puserinteraction->window_state().m_point != rectangle.origin)
   //      {
   //
   //         puserinteraction->window_state().m_point = rectangle.origin;
   //
   //         TRACE("window::macos_window_resized effective position is different from requested position");
   //
   //         puserinteraction->post_message(e_message_reposition, 0, puserinteraction->window_state().m_point.lparam());
   //
   //      }
   //
   //      if(puserinteraction->m_sizeRequest != rectangle.size_i32)
   //      {
   //
   //         puserinteraction->m_sizeRequest = rectangle.size_i32;
   //
   //         TRACE("window::macos_window_resized effective position is different from requested position");
   //
   //         puserinteraction->post_message(e_message_size, 0, puserinteraction->m_sizeRequest.lparam());
   //
   //      }
   //
   //      puserinteraction->m_point = rectangle.origin;
   //
   //      puserinteraction->m_size = rectangle.size_i32;
   //
   ////      ::size_i32 sz;
   ////
   ////      point_i64 pt(rectangle.origin.x, rectangle.origin.y);
   ////
   ////      bool bMove = false;
   ////
   ////      {
   ////
   ////         synchronous_lock synchronouslock(puserinteraction->mutex());
   ////
   ////         if (pt != puserinteraction->m_rectParentClient.top_left())
   ////         {
   ////
   ////            bMove = true;
   ////
   ////         }
   ////
   ////         puserinteraction->m_rectParentClient.move_to(point);
   ////
   ////         puserinteraction->set_size(rectangle.size_i32);
   ////
   ////         sz = puserinteraction->m_rectParentClient.size();
   ////
   ////      }
   ////
   ////      if(puserinteraction == nullptr)
   ////      {
   ////
   ////         return;
   ////
   ////      }
   ////
   ////      puserinteraction->post_message(e_message_size, 0, sz.lparam());
   ////
   ////      if (bMove)
   ////      {
   ////
   ////         puserinteraction->post_message(e_message_reposition, 0, pt.lparam());
   ////
   ////      }

   //      if (puserinteraction->m_eflagLayouting)
   //      {
   //
   //         //pmessage->m_bRet = true;
   //
   //         return;
   //
   //      }
   //
   //      ::rectangle_i32 rectSize;
   //
   //      copy(rectSize, rectangle);
   //
   //      if(puserinteraction->window_state().rectangle_i32() != rectSize)
   //      {
   //
   //         puserinteraction->window_state().m_point = rectSize.origin();
   //
   //         puserinteraction->window_state().m_size = rectSize.size();
   //
   //      }
   //
   //
   //      if (puserinteraction->layout().sketch().rectangle_i32() != rectSize)
   //      {
   //
   //         puserinteraction->place(rectSize);
   //
   //         if (puserinteraction->layout().design().display() != e_display_normal)
   //         {
   //
   //            puserinteraction->display();
   //
   //         }
   //
   //         puserinteraction->set_need_layout();
   //
   //         puserinteraction->set_need_redraw();
   //
   //      }

   }


   void window::macos_window_moved(CGPoint point)
   {
      
      
      if(m_puserinteractionimpl->m_bEatMoveEvent)
      {
         
         m_puserinteractionimpl->m_bEatMoveEvent = false;
         
         return;
         
      }

      {

         _NEW_MESSAGE(preposition, ::message::reposition, e_message_reposition);
         preposition->m_point.x = point.x;
         preposition->m_point.y = point.y;

//         atom id = e_message_reposition;
//
//         wparam wparam = 0;
//
//         lparam lparam = __MAKE_LPARAM(point.x, point.y);
//
//         auto pmove  = __create_new < ::message::reposition > ();
//
//         pmove->set(this, this, id, wparam, lparam);

         post_message(preposition);
         
      }
   //      if(puserinteraction == nullptr)
   //      {
   //
   //         return;
   //
   //      }
   //
   //
   //      ::point_i32 pointMove;
   //
   //      copy(pointMove, point);
   //
   //      if (puserinteraction->m_eflagLayouting)
   //      {
   //
   //         //pmessage->m_bRet = true;
   //
   //         return;
   //
   //      }
   //
   //      ///::pointer < ::message::move > pmove(pmessage);
   //
   //      if (puserinteraction->layout().sketch().m_point != pointMove)
   //      {
   //
   //         puserinteraction->move_to(pointMove);
   //
   //         if (puserinteraction->layout().design().display() != e_display_normal)
   //         {
   //
   //            puserinteraction->display();
   //
   //         }
   //
   //         puserinteraction->set_reposition();
   //
   //         puserinteraction->set_need_redraw();
   //
   //      }
   //
   //
   ////      if(puserinteraction->m_pointRequest != point_i32)
   ////      {
   ////
   ////         puserinteraction->m_pointRequest = point;
   ////
   ////         TRACE("window::macos_window_resized effective position is different from requested position");
   ////
   ////      }
   ////
   ////      puserinteraction->m_point = point;

   }


   void window::macos_window_did_become_key()
   {

//      if(is_destroying())
//      {
//
//         return;
//
//      }
      
      m_puserinteractionimpl->m_timeLastExposureAddUp.Now();

   }


   void window::macos_window_on_activate()
   {
      
      if(is_destroying())
      {
         
         return;
         
      }
      
      //this->set_active_window();

      auto puserinteraction = m_puserinteractionimpl->m_puserinteraction;

      if(::is_null(puserinteraction))
      {

         return;

      }

//      puserinteraction->set_need_redraw();
      puserinteraction->send_message(e_message_activate, 1);

   }


   void window::macos_window_on_deactivate()
   {

      if(is_destroying())
      {
         
         //return;
         
         output_debug_string("destroying");
         
      }
      
      auto pwindowing = m_pwindowing;
      
      auto puserinteraction = m_puserinteractionimpl->m_puserinteraction;
      
//      auto pwindowActive = pwindowing->get_active_window(puserinteraction->m_pthreadUserInteraction);
//
//      if(::is_null(pwindowActive))
//      {
//
//         return;
//
//      }
//
//      if(pwindowActive != this)
//      {
//
//         return;
//
//      }
//
//      pwindowing->clear_active_window(puserinteraction->m_pthreadUserInteraction);
      
      //::deactivate_window(get_handle());

   //      if(puserinteraction == nullptr)
   //      {
   //
   //         return;
   //
   //      }
      
      puserinteraction->send_message(e_message_activate, 0);

//      if(!is_destroying())
//      {
//
//         puserinteraction->set_need_redraw();
//
//      }

   }


   void * window::macos_window_get_mouse_cursor()
   {
      
      if(::is_null(m_pcursor))
      {
         
         return nullptr;
         
      }
      
      auto poscursor = m_pcursor->get_os_data();
      
      if(::is_null(poscursor))
      {
       
         return nullptr;
         
      }
      
      return poscursor;
      
   }

   
   void window::profiling_on_start_draw_rectangle()
   {
      
      auto pimpl = m_puserinteractionimpl;
      
      if(::is_null(pimpl))
      {
       
         return;
         
      }

      auto pimpl2 = pimpl->m_pImpl2;

      if(::is_null(pimpl2))
      {
       
         return;
         
      }
      
      auto pprodevian = pimpl2->m_pprodevian;
      
      if(::is_null(pprodevian))
      {
       
         return;
         
      }
      
      pprodevian->profiling_on_before_update_screen();

   }


   void window::profiling_on_end_draw_rectangle()
   {
      
      auto pimpl = m_puserinteractionimpl;
      
      if(::is_null(pimpl))
      {
       
         return;
         
      }

      auto pimpl2 = pimpl->m_pImpl2;

      if(::is_null(pimpl2))
      {
       
         return;
         
      }
      
      auto pprodevian = pimpl2->m_pprodevian;
      
      if(::is_null(pprodevian))
      {
       
         return;
         
      }
      
      pprodevian->profiling_on_after_update_screen();
      
   }


   void window::macos_window_iconified()
   {

      if(is_destroying())
      {
         
         return;
         
      }
      
      auto puserinteraction = m_puserinteractionimpl->m_puserinteraction;

      if(::is_null(puserinteraction))
      {

         return;

      }
      
      if(m_puserinteractionimpl->m_puserbox != nullptr)
      {

         m_puserinteractionimpl->m_puserbox->m_windowrectangle.m_edisplayPrevious = m_puserinteractionimpl->m_puserbox->m_windowrectangle.m_edisplay;
         
      }

      puserinteraction->set_display(::e_display_iconic, ::user::e_layout_window);

   }


   void window::macos_window_deiconified()
   {

      if(is_destroying())
      {
         
         return;
         
      }
      
      auto puserinteraction = m_puserinteractionimpl->m_puserinteraction;

      if(puserinteraction == nullptr)
      {

         return;

      }
      
      if(m_puserinteractionimpl->m_puserbox)
      {

         if(m_puserinteractionimpl->m_puserbox->m_windowrectangle.m_edisplayPrevious == ::e_display_iconic)
         {

            m_puserinteractionimpl->m_puserbox->m_windowrectangle.m_edisplayPrevious = ::e_display_restored;

         }
         
         puserinteraction->_001OnDeiconify(m_puserinteractionimpl->m_puserbox->m_windowrectangle.m_edisplayPrevious);
         
      }

   }


   void window::macos_window_on_show()
   {

      if(is_destroying())
      {
         
         return;
         
      }
      
      auto puserinteraction = m_puserinteractionimpl->m_puserinteraction;

      if(puserinteraction == nullptr)
      {

         return;

      }

      m_puserinteractionimpl->m_timeLastExposureAddUp.Now();

      puserinteraction->send_message(e_message_show_window, 1);

      //puserinteraction->user_interaction_update_visibility_cache(true);

   //      if(!(puserinteraction->m_ewindowflag & window_flag_miniaturizable))
   //      {
   //
   //         if(puserinteraction->layout().sketch().display() == e_display_iconic)
   //         {
   //
   //            puserinteraction->m_windowState3
   //
   //         }
   //
   //      }

      puserinteraction->set_need_layout();

      puserinteraction->set_need_redraw();

      puserinteraction->post_redraw();

   }


   void window::macos_window_on_hide()
   {

   //      if(is_destroying())
   //      {
   //
   //         return;
   //
   //      }
      
      INFORMATION("macos::window::macos_window_on_hide");

      auto puserinteraction = m_puserinteractionimpl->m_puserinteraction;

      if(::is_null(puserinteraction))
      {

         WARNING("macos::window::macos_window_on_hide (2) puserinteraction == nullptr");

         return;

      }
      
      if(puserinteraction->has_destroying_flag())
      {
         
         return;
         
      }
      
      if(puserinteraction->const_layout().window().is_screen_visible())
      {

         puserinteraction->hide();

      }
      
      puserinteraction->message_call(e_message_show_window, 0);

   }


   void window::macos_window_on_miniaturize()
   {

      if(is_destroying())
      {
         
         return;
         
      }
      
      auto puserinteraction = m_puserinteractionimpl->m_puserinteraction;

      if(::is_null(puserinteraction))
      {

         return;

      }

      //puserinteraction->message_call(e_message_show_window, 0);

      //puserinteraction->user_interaction_update_visibility_cache(false);

   }


   void window::frame_toggle_restore()
{
      
      ns_main_async(^()
                     {
         
         auto puserinteraction = m_puserinteractionimpl->m_puserinteraction;

      if(puserinteraction->get_parent() == nullptr && puserinteraction->get_owner() == nullptr)
      {

         if(!puserinteraction->is_window_visible()
            || (!(puserinteraction->m_ewindowflag & e_window_flag_miniaturizable)
                && !puserinteraction->is_window_screen_visible()))
         {

            puserinteraction->display_previous_restore();

         }
         else if(puserinteraction->_001GetTopLeftWeightedOccludedOpaqueRate()  > 0.025)
         {

            puserinteraction->order(::e_zorder_top);

            puserinteraction->display(e_display_default, e_activation_set_foreground);

         }
         else if(puserinteraction->m_pinteractionimpl && puserinteraction->m_pinteractionimpl->m_timeLastExposureAddUp.elapsed() < 300_ms)
         {

            INFORMATION("Ignored minituarize request (by toggle intent) because of recent full exposure.");

         }
         else
         {

            puserinteraction->display(e_display_iconic, e_activation_no_activate);

         }

         puserinteraction->set_need_redraw();

         puserinteraction->post_redraw();

      }

      });

      //return ::success;
      
   }


   void window::non_top_most_upper_window_rects(::rectangle_i32_array & recta)
   {
      
      
      recta = cg_get_window_rect_list_intersect_above(ns_get_window_id(m_pnswindow));
      
      
   }


   bool window::post_message(::message::message * pmessage)
   {

//      oswindow oswindow = message.oswindow;
//
//      ASSERT(oswindow != nullptr);
//
//      auto pimpl = oswindow->m_puserinteractionimpl;
//
//      if(::is_null(pimpl))
//      {
//
//         return false;
//
//      }

      auto puserinteraction = m_puserinteractionimpl->m_puserinteraction;

      if(::is_null(puserinteraction))
      {

         return false;

      }
      
      puserinteraction->post(pmessage);

      //::thread * pthread = nullptr;

//      if (::is_set(puserinteraction))
//      {
//
//         pthread = puserinteraction->m_pthreadUserInteraction;
//
//      }
//
//      if (::is_null(pthread))
//      {
//
//         return false;
//
//      }
//
//      class ::message_queue * pmq = pthread->m_pmq;
//
//      if (pmq == nullptr)
//      {
//
//         if (message.m_id == e_message_quit)
//         {
//
//            return false;
//
//         }
//
//         pmq = pthread->get_message_queue();
//
//      }
//
//      if (pmq == nullptr)
//      {
//
//         return false;
//
//      }
//
//      synchronous_lock ml(pmq->mutex());
//
//      if (message.m_id == e_message_quit)
//      {
//
//         output_debug_string("e_message_quit thread");
//
//      }
//
//      if (message.m_id == e_message_left_button_down)
//      {
//
//         output_debug_string("post_ui_message::e_message_left_button_down\n");
//
//      }
//      else if (message.m_id == e_message_left_button_up)
//      {
//
//         output_debug_string("post_ui_message::e_message_left_button_up\n");
//
//      }
//
//      pmq->m_messagea.add(message);
//
//      pmq->m_eventNewMessage.set_event();

      return true;

   }


   bool window::send_message(::message::message * pmessage)
   {

   //      oswindow oswindow = message.oswindow;
   //
   //      ASSERT(oswindow != nullptr);
   //
   //      auto pimpl = oswindow->m_puserinteractionimpl;
   //
   //      if(::is_null(pimpl))
   //      {
   //
   //         return false;
   //
   //      }

      auto puserinteraction = m_puserinteractionimpl->m_puserinteraction;

      if(::is_null(puserinteraction))
      {

         return false;

      }
      
      puserinteraction->send(pmessage);

      //::thread * pthread = nullptr;

   //      if (::is_set(puserinteraction))
   //      {
   //
   //         pthread = puserinteraction->m_pthreadUserInteraction;
   //
   //      }
   //
   //      if (::is_null(pthread))
   //      {
   //
   //         return false;
   //
   //      }
   //
   //      class ::message_queue * pmq = pthread->m_pmq;
   //
   //      if (pmq == nullptr)
   //      {
   //
   //         if (message.m_id == e_message_quit)
   //         {
   //
   //            return false;
   //
   //         }
   //
   //         pmq = pthread->get_message_queue();
   //
   //      }
   //
   //      if (pmq == nullptr)
   //      {
   //
   //         return false;
   //
   //      }
   //
   //      synchronous_lock ml(pmq->mutex());
   //
   //      if (message.m_id == e_message_quit)
   //      {
   //
   //         output_debug_string("e_message_quit thread");
   //
   //      }
   //
   //      if (message.m_id == e_message_left_button_down)
   //      {
   //
   //         output_debug_string("post_ui_message::e_message_left_button_down\n");
   //
   //      }
   //      else if (message.m_id == e_message_left_button_up)
   //      {
   //
   //         output_debug_string("post_ui_message::e_message_left_button_up\n");
   //
   //      }
   //
   //      pmq->m_messagea.add(message);
   //
   //      pmq->m_eventNewMessage.set_event();

      return true;

   }


   void window::destroy_window()
   {

      ::pointer < ::user::primitive_impl > pimplThis = m_puserinteractionimpl;

      ::pointer < ::user::interaction > puiThis = pimplThis->m_puserinteraction;

      try
      {

         puiThis->send_message(e_message_destroy);

      }
      catch (...)
      {

      }

      try
      {

         puiThis->send_message(e_message_non_client_destroy);

      }
      catch (...)
      {

      }

      //return ::success;

   }


   void window::bring_to_front()
   {

      macos_window_order_front();

      //return ::success;

   }


   void window::get_cursor_position(POINT_I32 * ppoint)
   {
      
      macos_get_cursor_position(ppoint);
      
   }


} // namespace windowing_macos


struct NSWindow;

NSWindow * __nswindow(oswindow oswindow)
{

   return (NSWindow *) oswindow->get_os_data();

}


