// created by Camilo 2021-02-04 00:58 BRT CamiloSasuke<3ThomasBorregaardSoerensen
#pragma once


namespace windowing_macos
{


   class CLASS_DECL_WINDOWING_MACOS keyboard :
      virtual public ::windowing::keyboard
   {
   public:


      keyboard();
      ~keyboard() override;
      
      
      ::user::enum_key wparam_to_userkey(wparam wparam) override;


   };


} // namespace windowing_macos





