//
//  windowing.hpp
//  windowing_macos
//
//  Created by Camilo Sasuke on 2021-05-21 01:59 <3ThomasBS_!!
//
#pragma once


namespace windowing_macos
{


   class CLASS_DECL_WINDOWING_MACOS windowing :
   virtual public ::windowing::windowing
   {
   public:


//      class element_quit :
//      virtual public ::element
//      {
//      public:
//
//         __pointer(::acme::node) & m_pnode;
//         __pointer(class ::system) & m_psystem;
//
//         element_quit(__pointer(::acme::node) & pnode,__pointer(class ::system) & psystem
//               
//               ) :
//         m_pnode(pnode),m_psystem(psystem)
//         {
//
//         }
//
//         void run() override;
//
//
//      };


      __pointer(::windowing::display)           m_pdisplay;

      __pointer(class window)                   m_pwindowActive;

      __pointer(class window)                   m_pwindowCapture;

      map < void *, __pointer(class window) >   m_nsmap;

      //__pointer(element_quit)                   m_pelementquit;

      windowing();
      ~windowing() override;


      void initialize(::object * pobject) override;

      void windowing_post(const ::procedure & procedure) override;

      ::windowing::window * window(oswindow oswindow) override;

      ::windowing::display * display() override;

      ::windowing::window * get_active_window(::thread * pthread) override;

      //virtual bool post_ui_message(::message::base * pbase);

      void release_mouse_capture() override;

      ::windowing::window * get_keyboard_focus(::thread *) override;


      //void get_cursor_position(POINT_I32 * ppoint) override;

      void _defer_dock_application(int_bool bDock);


      void clear_keyboard_focus(::user::element* pelementGainingFocusIfAny) override;


      void os_menu_item_enable(void * pitem, bool bEnable) override;
      void os_menu_item_check(void * pitem, bool bCheck) override;

      void defer_create_main_menu(const string_array & straParent, const string_array & straMenu, const string_array & straId) override;

//      void _will_finish_launching() override;
//
//      void element_quit_post_quit() override;

      ::e_status is_keyboard_hook_enabled(::user::interaction * puserinteractionEnablePrompt) override;


      void install_keyboard_hook(::matter * pmatterListener) override;
      void uninstall_keyboard_hook(::matter * pmatterListener) override;

      void install_mouse_hook(::matter * pmatterListener) override;
      void uninstall_mouse_hook(::matter * pmatterListener) override;

   };
      

} // namespace windowing_macos




