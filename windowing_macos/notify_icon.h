#pragma once


namespace windowing_macos
{


   class CLASS_DECL_WINDOWING_MACOS notify_icon :
      virtual public ::user::notify_icon,
      virtual public ::user_notify_icon_mm_bridge
   {
   public:


      notify_icon();
      virtual ~notify_icon();


      ::e_status add_hidden_window(::user::interaction * puserinteraction) override;


      virtual bool DestroyWindow();


      bool ModifyIcon(__pointer(::draw2d::icon) picon, bool bForce = false);


      ::e_status create_notify_icon(const ::id & id, ::user::interaction * puserinteractionNotify, ::windowing::icon * picon) override;

      //DECL_GEN_SIGNAL(_001OnNotifyIconMessage);
      //DECL_GEN_SIGNAL(_001OnDestroy);

      ::e_status step() override;
      //virtual void notify_icon_play(const char * action) override;

      
   };


} // namespace windowing_macos


