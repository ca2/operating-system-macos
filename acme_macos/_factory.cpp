#include "framework.h"
#include "acme/filesystem/filesystem/acme_dir.h"
#include "acme_dir.h"
#include "acme/filesystem/filesystem/acme_path.h"
#include "acme_path.h"
//#include "copydesk.h"
//#include "file_os_watcher.h"
//#include "acme/node/posix/pipe.h"
//#include "acme/node/apple/process.h"
//#include "acme/node/macos/shell_macos.h"
//#include "acme/node/unix/process.h"


//namespace macos
//{
//
//   factory_exchange::factory_exchange()
//   {
//
//
//
//   }
//
//
//   factory_exchange::~factory_exchange()
//   {
//
//   }
//
//
//} // namespace macos


__FACTORY_EXPORT void acme_apple_factory(::factory::factory * pfactory);


__FACTORY_EXPORT void acme_macos_factory(::factory::factory * pfactory)
{
   
   acme_apple_factory(pfactory);

   pfactory->add_factory_item < ::macos::stdio_file, ::file::text_file > ();
   pfactory->add_factory_item < ::macos::file, ::file::file > ();
   
   pfactory->add_factory_item < ::macos::acme_dir, ::acme_dir > ();
   pfactory->add_factory_item < ::macos::acme_path, ::acme_path > ();

   //create_factory < ::macos::os_context         , ::os_context       > ();
   //create_factory < ::apple::process            , ::process::process > ();
   
  pfactory->add_factory_item < ::posix::pipe               , ::operating_system::pipe    > ();
   
   //create_factory < ::macos::dir_system         , ::dir_system       > ();
   //create_factory < ::macos::file_system        , ::file_system      > ();
   //create_factory < ::macos::dir_context        , ::dir_context      > ();
   //create_factory < ::macos::file_context       , ::file_context     > ();
   //create_factory < ::macos::interaction_impl   , ::user::interaction_impl > ();
   
   //create_factory < ::macos::copydesk           , ::user::copydesk > ();

   //create_factory < ::file::os_watcher          , ::file::watcher    > ();
   //create_factory < ::file::os_watch            , ::file::watch      > ();
   
   
   //create_factory < ::macos::shell   , ::user::shell > ();

}



