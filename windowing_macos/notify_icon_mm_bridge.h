//
//  user_notify_icon_mm_bridge.h
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 3/17/16.
//  Copyright © 2016 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//
//
#pragma once


class user_notify_icon_bridge;


class user_notify_icon_mm_bridge
{
public:


   void *                              m_pnotifyicon;
   ::user_notify_icon_bridge *         m_pnotifyiconbridge;
   

   virtual void notify_icon_mm_initialize(const char * pszIconFile);
   
   
   virtual void notify_icon_mm_finalize();


};



