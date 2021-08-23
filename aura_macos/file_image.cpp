//
//  file_image.cpp
//  aura_macos
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 22/08/21.
//  Copyright © 2021 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//
#include "framework.h"


bool mm1_get_file_image(unsigned int * pcr, int cx, int cy, int iScan, const char * pszFilePath);
bool mm1_get_file_image_by_type_identifier(unsigned int * pcr, int cx, int cy, int iScan, const char * pszTypeIdentifier);


bool macos1_get_file_image(unsigned int * pcr, int cx, int cy, int iScan, const char * pszFilePath)
{

   static ::mutex * pmutex = nullptr;

   if(pmutex == nullptr)
   {

      pmutex = new ::mutex();

   }

   synchronous_lock synchronouslock(pmutex);


   return mm1_get_file_image(pcr, cx, cy, iScan, pszFilePath);


}


bool macos1_get_file_image_by_type_identifier(unsigned int * pcr, int cx, int cy, int iScan, const char * pszTypeIdentifier)
{

   static ::mutex * pmutex = nullptr;

   if(pmutex == nullptr)
   {

      pmutex = new ::mutex();

   }

   synchronous_lock synchronouslock(pmutex);


   return mm1_get_file_image_by_type_identifier(pcr, cx, cy, iScan, pszTypeIdentifier);

}


bool macos_get_file_image(::image * pimage, const char * pszFilePath)
{

   pimage->map();

   if(!macos1_get_file_image(pimage->get_data(), pimage->width(), pimage->height(), pimage->scan_size(), pszFilePath))
   {

      return false;

   }

   return true;

}


bool macos_get_file_image_by_type_identifier(::image * pimage, const char * pszTypeIdentifier)
{

   pimage->map();

   if(!macos1_get_file_image_by_type_identifier(pimage->get_data(), pimage->width(), pimage->height(), pimage->scan_size(), pszTypeIdentifier))
   {

      return false;

   }

   return true;

}

