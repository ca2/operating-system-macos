//
//  windowing.cpp
//  windowing_macos
//
//  Created by Camilo Sasuke on 2021-05-21 02:00 <3ThomasBS_!!
//
#include "framework.h"
#include "acme/parallelization/manual_reset_event.h"
#include "acme/platform/application.h"
#include "acme/platform/sequencer.h"
#include "aura/user/menu/shared.h"
#include "aura/user/user/interaction_impl.h"
#include "keyboard_hook.h"
#include "mouse_hook.h"
#include <Carbon/Carbon.h>


void ns_main_async(dispatch_block_t block);


void * ns_get_key_window();


//void os_post_quit(::element * pelementQuit);


::pointer < menu_shared > create_menu_shared(::object * pobject, const string_array & straParent, const string_array & straMenu, const string_array & straId);


void windowing_macos_application_main(void * pApplication, int argc, char *argv[]);


void ns_create_main_menu(menu_shared * pmenushared);


void os_menu_item_enable(void * pitem, bool bEnable);
void os_menu_item_check(void * pitem, bool bCheck);


namespace windowing_macos
{



   windowing::windowing()
   {
      
      m_pWindowing4 = this;
      
      m_pwindowCapture = nullptr;
       
      //m_pelementquit = nullptr;

      
   }


   windowing::~windowing()
   {
   
   }


   void windowing::initialize(::particle * pparticle)
   {
   
      //auto estatus =
      
      ::windowing::windowing::initialize(pparticle);
      
//      if(!estatus)
//      {
//
//         return estatus;
//
//      }
      
      //estatus =
      
      __construct(m_pdisplay);
      
//      if(!estatus)
//      {
//
//         return estatus;
//
//      }
//
      m_pdisplay->m_pwindowing = this;
         
      //return estatus;
      
   }


   void windowing::windowing_post(const ::procedure & procedure)
   {
      
      auto routineLocal = procedure;

      ns_main_async(^
                    {
         
         routineLocal();
         
      });
      
      //return success;

   }


   ::windowing::window * windowing::window(oswindow oswindow)
   {

      return oswindow;

   }


   ::windowing::display * windowing::display()
   {

      return m_pdisplay;

   }


   ::windowing::window * windowing::get_active_window(::thread * pthread)
   {
      
      return nullptr;
      
   }


   void windowing::release_mouse_capture()
   {
      
      auto pwindowCapture = m_pwindowCapture;

      m_pwindowCapture.release();

      if(pwindowCapture)
      {
         
         pwindowCapture->m_puserinteractionimpl->m_puserinteractionMouseCapture.release();
         
      }
   
      //return ::success;
      
   }


//   bool windowing::post_ui_message(const MESSAGE &message)
//   {
//
//      oswindow oswindow = message.oswindow;
//
//      ASSERT(oswindow != nullptr);
//
//      auto pimpl = oswindow->m_pimpl;
//
//      if(::is_null(pimpl))
//      {
//
//         return false;
//
//      }
//
//      auto pinteraction = pimpl->m_puserinteraction;
//
//      if(::is_null(pinteraction))
//      {
//
//         return false;
//
//      }
//
//      ::thread *pthread = nullptr;
//
//      if (::is_set(pinteraction))
//      {
//
//         pthread = pinteraction->m_pthreadUserInteraction;
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
//      class ::message_queue *pmq = pthread->m_pmq;
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
//
//      return true;
//
//   }


   ::windowing::window * windowing::get_keyboard_focus(::thread *)
   {
      
      void * pnswindow = ns_get_key_window();
      
      if(::is_null(pnswindow))
      {
         
         return nullptr;
         
      }
      
      auto pwindowFocus = m_nsmap[pnswindow];

      return pwindowFocus;

   }





   void windowing::_defer_dock_application(int_bool bDock)
   {

      if (bDock)
      {
   
         //if (!nsapp_activation_policy_is_regular())
         {
   
            nsapp_activation_policy_regular();
            
            ns_main_async(^()
                          {

            ProcessSerialNumber psn = { 0, kCurrentProcess };
            
            TransformProcessType(&psn, kProcessTransformToForegroundApplication);
               
            });
         }
   
      }
      else
      {
   
         //if (!nsapp_activation_policy_is_accessory())
         {
   
            nsapp_activation_policy_accessory();
            
            ns_main_async(^()
                          {
            //hide icon on Dock
            ProcessSerialNumber psn = { 0, kCurrentProcess };
            TransformProcessType(&psn, kProcessTransformToUIElementApplication);
               
            });
   
         }
   
      }

   }


   void windowing::clear_keyboard_focus(::user::element* pelementGainingFocusIfAny)
   {

   }






   void windowing::os_menu_item_enable(void * pitem, bool bEnable)
   {
    
      ::os_menu_item_enable(pitem, bEnable);
      
   }


   void windowing::os_menu_item_check(void * pitem, bool bCheck)
   {

      ::os_menu_item_check(pitem, bCheck);
      
   }


   void windowing::defer_create_main_menu(const string_array & straMenuParent, const string_array & straMenuName, const string_array & straMenuId)
   {
      
      auto pmenushared =
         create_menu_shared(
                            this,
                            straMenuParent,
                            straMenuName,
                            straMenuId
                            
                            );

      ns_create_main_menu(pmenushared);
      
      //return success;
      
   }


//   void windowing::implement(::pointer < ::acme::node > & pnode, __pointer(class ::system) & psystem)
//   {
//
//      m_pelementquit = new element_quit(pnode, psystem);
//
//      auto argc = psystem->m_argc;
//
//      auto argv = psystem->m_argv;
//
//      auto papp = psystem->m_pappStartup;
//
//      void * pApplication = (void *) (::app *) papp;
//
//      windowing_macos_application_main(pApplication, argc, argv);
//
//      //return psystem->m_estatus;
//
//   }


//   void windowing::_will_finish_launching()
//   {
//      
//      auto psystem = m_psystem->m_papexsystem;
//      
//      if(::is_null(psystem->m_htask))
//      {
//
//         ///auto estatus =
//         
//         psystem->branch_synchronously();
//
//   //         if(!estatus)
//   //         {
//   //
//   //            return estatus;
//   //
//   //         }
//         
//         // release the initial allocation from platform_create_system as
//         // task::begin_synch holds a reference to the running system task.
//         psystem->release();
//         
//      }
//      
//      m_psystem->post_initial_request();
//
//      //return ::success;
//      
//   }
//

   ::e_status windowing::is_keyboard_hook_enabled(::user::interaction * puserinteractionEnablePrompt)
   {
      
      auto estatus = ::keyboard_hook::is_enabled(false);

      if(::is_null(puserinteractionEnablePrompt) || estatus == ::success)
      {
         
         return estatus;
         
      }
      
      manual_reset_event ev;
      
      auto psequencer = puserinteractionEnablePrompt->message_box("You gonna be prompted to enable Accessibility for \""+acmeapplication()->m_strAppName+"\" to enable keyboard monitoring.",
                                                                                   "Aura Click", e_message_box_ok);
      
      psequencer->then(
                                                           [this, &ev,puserinteractionEnablePrompt](auto & sequence)
                                                           {
                        
                        auto estatus = ::keyboard_hook::is_enabled(true);
                        
                        if(estatus.succeeded())
                        {
                           
                           ev.set_event();
                           
                           return;
                            
                        }
                        else
                        {
                           
                           while(estatus == error_need_restart_application_to_activate_feature)
                           {
                              
                              ::preempt(1_s);
                              
                              estatus = ::keyboard_hook::is_enabled(false);
                              
                              //output_debug_string("todo restart application");
                              
                              //m_psystem->m_papplicationMain->_001TryCloseApplication();
                              
                           }
                              
                        }
                        
                        output_debug_string("loop ended");
                        
                        ev.set_event();
                        
                     });

      psequencer->do_synchronously(5_minute);
      //}
      
      psequencer->do_asynchronously();

      //ev.wait();
      
      estatus = ::keyboard_hook::is_enabled(false);
      
      return estatus;
      
   //      auto estatus = keyboard_hook::check_system_permission(::is_set(puserinteractionEnablePrompt));
   //
   //      if(estatus == error_need_restart_application_to_activate_feature)
   //      {
   //
   //         message_box(puserinteractionEnablePrompt, "Restart Aura Click?\n\nIf you have just enabled Accessibility and want the setting to be effective, Aura Click should be restarted.",
   //                     "Aura Click", e_message_box_yes_no).then(
   //                                                           [](auto & sequence)
   //                                                           {
   //
   //                        output_debug_string("todo restart application");
   //
   //                     });
   //
   //      }
      
   }


   void windowing::install_keyboard_hook(::matter * pmatterListener)
   {
      
      //auto estatus =
      
      ::keyboard_hook::install(pmatterListener);
      
   //      if(!estatus)
   //      {
   //
   //         return estatus;
   //
   //      }
   //
   //      return estatus;
      
   }


   void windowing::uninstall_keyboard_hook(::matter * pmatterListener)
   {

      ///auto estatus =
      
      ::keyboard_hook::uninstall(pmatterListener);

   //      if(!estatus)
   //      {
   //
   //         return estatus;
   //
   //      }
   //
   //      return estatus;
      
   }


   void windowing::install_mouse_hook(::matter * pmatterListener)
   {
      
      //auto estatus =
      
      ::mouse_hook::install(pmatterListener);
      
   //      if(!estatus)
   //      {
   //
   //         return estatus;
   //
   //      }
   //
   //      return estatus;
      
   }


   void windowing::uninstall_mouse_hook(::matter * pmatterListener)
   {

      //auto estatus =
      
      ::mouse_hook::uninstall(pmatterListener);

   //      if(!estatus)
   //      {
   //
   //         return estatus;
   //
   //      }
   //
   //      return estatus;
      
   }


//   void windowing::os_menu_item_enable(void * pitem, bool bEnable)
//   {
//
//      ::os_menu_item_enable(pitem, bEnable);
//
//   }
//
//
//   void windowing::os_menu_item_check(void * pitem, bool bCheck)
//   {
//
//      ::os_menu_item_check(pitem, bCheck);
//
//   }


//   void windowing::defer_create_main_menu(const string_array & straMenuParent, const string_array & straMenuName, const string_array & straMenuId)
//   {
//      
//      auto pmenushared =
//         create_menu_shared(
//                            
//                            straMenuParent,
//                            straMenuName,
//                            straMenuId
//                            
//                            );
//
//      ns_create_main_menu(pmenushared);
//      
//      //return success;
//      
//   }


//   ::e_status windowing::is_keyboard_hook_enabled(::user::interaction * puserinteractionEnablePrompt)
//   {
//
//      auto estatus = ::keyboard_hook::is_enabled(false);
//
//      if(::is_null(puserinteractionEnablePrompt) || estatus == ::success)
//      {
//
//         return estatus;
//
//      }
//
//      manual_reset_event ev;
//
//      puserinteractionEnablePrompt->message_box("You gonna be prompted to enable Accessibility for \""+m_psystem->m_pappMain->m_strAppName+"\" to enable keyboard monitoring.",
//                     "Aura Click", e_message_box_ok)->then(
//                                                           [this, &ev,puserinteractionEnablePrompt](auto & sequence)
//                                                           {
//
//                        auto estatus = ::keyboard_hook::is_enabled(true);
//
//                        if(estatus.succeeded())
//                        {
//
//                           ev.set_event();
//
//                           return;
//
//                        }
//                        else
//                        {
//
//                           while(estatus == error_need_restart_application_to_activate_feature)
//                           {
//
//                              ::preempt(1_s);
//
//                              estatus = ::keyboard_hook::is_enabled(false);
//
//                              //output_debug_string("todo restart application");
//
//                              //m_psystem->m_papplicationMain->_001TryCloseApplication();
//
//                           }
//
//                        }
//
//                        output_debug_string("loop ended");
//
//                        ev.set_event();
//
//                     });
//
//      //}
//
//      ev.wait();
//
//      estatus = ::keyboard_hook::is_enabled(false);
//
//      return estatus;
//
//   //      auto estatus = keyboard_hook::check_system_permission(::is_set(puserinteractionEnablePrompt));
//   //
//   //      if(estatus == error_need_restart_application_to_activate_feature)
//   //      {
//   //
//   //         message_box(puserinteractionEnablePrompt, "Restart Aura Click?\n\nIf you have just enabled Accessibility and want the setting to be effective, Aura Click should be restarted.",
//   //                     "Aura Click", e_message_box_yes_no).then(
//   //                                                           [](auto & sequence)
//   //                                                           {
//   //
//   //                        output_debug_string("todo restart application");
//   //
//   //                     });
//   //
//   //      }
//
//   }
//
//
//   void windowing::install_keyboard_hook(::matter * pmatterListener)
//   {
//
//      //auto estatus =
//
//      ::keyboard_hook::install(pmatterListener);
//
//   //      if(!estatus)
//   //      {
//   //
//   //         return estatus;
//   //
//   //      }
//   //
//   //      return estatus;
//
//   }
//
//
//   void windowing::uninstall_keyboard_hook(::matter * pmatterListener)
//   {
//
//      ///auto estatus =
//
//      ::keyboard_hook::uninstall(pmatterListener);
//
//   //      if(!estatus)
//   //      {
//   //
//   //         return estatus;
//   //
//   //      }
//   //
//   //      return estatus;
//
//   }
//
//
//   void windowing::install_mouse_hook(::matter * pmatterListener)
//   {
//
//      //auto estatus =
//
//      ::mouse_hook::install(pmatterListener);
//
//   //      if(!estatus)
//   //      {
//   //
//   //         return estatus;
//   //
//   //      }
//   //
//   //      return estatus;
//
//   }
//
//
//   void windowing::uninstall_mouse_hook(::matter * pmatterListener)
//   {
//
//      //auto estatus =
//
//      ::mouse_hook::uninstall(pmatterListener);
//
//   //      if(!estatus)
//   //      {
//   //
//   //         return estatus;
//   //
//   //      }
//   //
//   //      return estatus;
//
//   }


} // namespace windowing_macos



