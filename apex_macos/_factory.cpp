#include "framework.h"
#include "apex/platform/launcher.h"
#include "launcher.h"
#include "FileSystemEvents/watcher.h"


extern "C"
void apex_apple_factory(::factory::factory * pfactory);


extern "C"
void acme_macos_factory(::factory::factory * pfactory);


extern "C"
void apex_macos_factory(::factory::factory * pfactory)
{
   

   apex_apple_factory(pfactory);
   
   acme_macos_factory(pfactory);

   pfactory->add_factory_item < ::apex_macos::node, ::acme::node > ();

   pfactory->add_factory_item < ::FileSystemEvents::watcher, ::file::watcher > ();

   pfactory->add_factory_item < ::FileSystemEvents::watch, ::file::watch > ();

   pfactory->add_factory_item < ::apex_macos::file_context, ::file_context > ();
   pfactory->add_factory_item < ::apex_macos::dir_context, ::dir_context > ();
   pfactory->add_factory_item < ::apex_macos::file_system, ::file_system > ();
   pfactory->add_factory_item < ::apex_macos::dir_system, ::dir_system > ();

   pfactory->add_factory_item < ::apex_macos::os_context, ::os_context > ();
   
   pfactory->add_factory_item < ::apex_macos::interprocess_base, ::interprocess::base >();
   pfactory->add_factory_item < ::apex_macos::interprocess_target, ::interprocess::target >();
   pfactory->add_factory_item < ::apex_macos::interprocess_caller, ::interprocess::caller >();
//   pfactory->add_factory_item < ::macos::launcher, ::launcher > ();
//   pfactory->add_factory_item < ::macos::shell_launcher, ::shell_launcher > ();


}



