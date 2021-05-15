//
// Created by camilo on 19/01/2021. --<33ThomasBS!!
//
#include "framework.h"


void os_post_quit();


void ns_launch_app(const char * psz, const char ** argv, int iFlags);


void ansios_sigchld_handler(int sig);


void apex_application_run(const char * pszAppName, const char * pszProgName);


namespace acme
{


   namespace macos
   {


      node::node()
      {

         m_pAcmePosix = this;

      }


      node::~node()
      {

      }


   } // namespace macos


} // namespace acme


void * get_system_mmos(void * pSystem)
{
   
   auto psystem = (class ::system *) pSystem;
   
   return psystem->m_pmmos;
   
}


void set_system_mmos(void * pSystem, void * pmmos)
{
   
   auto psystem = (class ::system *) pSystem;
   
   psystem->m_pmmos = pmmos;
   
}



