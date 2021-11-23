// Create on 2021-03-21 20:00 <3ThomasBS_ // for Linux(question)
// Recreated on 2021-05-16 15:05 <3ThomasBS_ // for macOS
#include "framework.h"
#include "acme/filesystem/filesystem/acme_dir.h"
#include "acme/filesystem/filesystem/acme_path.h"
#include "acme_dir.h"



namespace macos
{

   
   acme_dir::acme_dir()
   {

      m_pplatformdir = this;

   }


   acme_dir::~acme_dir()
   {


   }


   string acme_dir::dir_root()
   {

      return home() / ".config/ca2";

   }


   ::file::path acme_dir::get_memory_map_base_folder_path() 
   {

      return home() / ".config/ca2/memory_map";

   }


//   ::file::path acme_dir::home()
//   {
//
//      return getenv("HOME");
//
//   }


   ::file::path acme_dir::program_data()
   {

      return home() / "application";

   }


   ::file::path acme_dir::roaming()
   {

      return home() / "Library/Application Support";

   }


   ::file::path acme_dir::appdata()
   {

      return ca2roaming() / "appdata" / app_relative();

   }


   ::file::path acme_dir::public_system()
   {

      return public_root() / "system";

   }


   ::file::path acme_dir::system()
   {

      return ca2roaming() / "system";

   }


   ::file::path acme_dir::config()
   {

      return ca2roaming() / "config";

   }


   ::file::path acme_dir::local()
   {

      return ca2roaming() / "local";

   }


   ::file::path acme_dir::sensitive()
   {

   #ifdef LINUX

      return "C:\\sensitive\\sensitive";

   #else

      return "/sensitive/sensitive";

   #endif

   }







   string acme_dir::system_short_name()
   {

   #ifdef _UWP

      return "metro";

   #else

      ::file::path pathSystemShortName = localconfig() / "system_short_name.txt";

      return m_pacmefile->as_string(pathSystemShortName).trimmed();

   #endif

   }


   ::file::path acme_dir::relative(::file::path path)
   {

      path.replace(":", "");

      ::str::ends_eat_ci(path, ".exe");

      return path;

   }

   #ifdef _UWP


   ::file::path acme_dir::app_relative()
   {

      return "";

   }


   #else


   ::file::path acme_dir::app_relative()
   {

      ::file::path path = m_psystem->m_pacmefile->module();

      path = relative(path);

      return path;

   }


   #endif



   ::file::path acme_dir::inplace_install(string strAppId, string strPlatform, string strConfiguration)
   {

   #ifdef LINUX_DESKTOP

      ::file::path path;

      string strFolder;

      strsize iFind = strAppId.find('/');

      if (strPlatform.compare_ci("win32") == 0 || strPlatform.compare_ci("x86") == 0)
      {

         path = program_files_x86();

      }
      else
      {
         path = program_files_x86();


         path = program_files();

      }

      if (iFind < 0)
      {

         path /= strAppId;

      }
      else
      {

         path /= strAppId.Left(iFind);

         path /= strAppId.Mid(iFind + 1);

      }

      return path;

   #elif defined(ANDROID)

      return pacmedir->roaming();

   #else

      return m_psystem->m_pacmefile->module().folder(4);

   #endif

   }


   ::file::path acme_dir::inplace_matter_install(string strAppId, string strPlatform, string strConfiguration)
   {

   #ifdef LINUX_DESKTOP

      ::file::path path;

      string strFolder;

      strsize iFind = strAppId.find('/');

      path = ca2roaming();

      path /= "_matter";

      return path;

   #elif defined(ANDROID)

      return pacmedir->roaming();

   #else

      return m_psystem->m_pacmefile->module().folder(4);

   #endif


   }


   ::file::path acme_dir::install()
   {

      if (m_pathInstallFolder == nullptr || m_pathInstallFolder.is_empty())
      {

         return default_install();

      }

      return m_pathInstallFolder;

   }


   ::file::path acme_dir::default_install()
   {

   #ifdef ANDROID

      return pacmedir->roaming();

   #elif defined(__APPLE__)

      return m_psystem->m_pacmefile->module().folder(3);

   #else

      return m_psystem->m_pacmepath->app_module().folder(4);

   #endif

   }


   ::file::path acme_dir::beforeca2()
   {

      return file_path_folder(install());

   }






   #ifdef LINUX_DESKTOP


   #include <Shlobj.h>


   ::file::path acme_dir::program_files_x86()
   {

      wstring wstrModuleFolder(get_buffer, sizeof(unichar) * 8);

      wstring wstrModuleFilePath(get_buffer, sizeof(unichar) * 8);

      wcscpy(wstrModuleFilePath, _wgetenv(L"PROGRAMFILES(X86)"));

      if (wcslen(wstrModuleFilePath) == 0)
      {

         SHGetSpecialFolderPathW(nullptr, wstrModuleFilePath, CSIDL_PROGRAM_FILES, false);

      }

      wstrModuleFilePath.trim_right(L"\\/");

      wcscpy(wstrModuleFolder, wstrModuleFilePath);

      return string(wstrModuleFolder);

   }


   ::file::path acme_dir::program_files()
   {

      wstring wstrModuleFolder(get_buffer, sizeof(unichar) * 8);

      wstring wstrModuleFilePath(get_buffer, sizeof(unichar) * 8);

      wcscpy(wstrModuleFilePath, _wgetenv(L"PROGRAMW6432"));

      if (wcslen(wstrModuleFilePath) == 0)
      {

         SHGetSpecialFolderPathW(nullptr, wstrModuleFilePath, CSIDL_PROGRAM_FILES, false);

      }

      wstrModuleFilePath.trim_right(L"\\/");

      wstrModuleFolder = wstrModuleFilePath;

      return string(wstrModuleFolder);



   }


   #else


   ::file::path acme_dir::program_files_x86()
   {

      ::file::path path("/opt/ca2");

      return path;

   }


   ::file::path acme_dir::program_files()
   {

      ::file::path path("/opt/ca2");

      return path;

   }


   #endif


   ::file::path acme_dir::stage(string strAppId, string strPlatform, string strConfiguration)
   {

      return inplace_install(strAppId, strPlatform, strConfiguration) / "time" / time_binary_platform(strPlatform) / strConfiguration;

   }


//   #ifdef LINUX


   ::file::path acme_dir::home()
   {

      return getenv("HOME");

   }


//   #endif


   #if defined(_UWP) || defined(__APPLE__) || defined(LINUX) || defined(ANDROID)


//   ::file::path acme_dir::bookmark()
//   {
//
//      auto psystem = m_psystem;
//
//      auto pacmedir = psystem->m_pacmedir;
//
//      return pacmedir->localconfig() / "bookmark";
//
//   }


   #endif


   #ifdef _UWP


   ::file::path acme_dir::home()
   {

      return "";

   }


   #endif




   void acme_dir::set_path_install_folder(const ::string & strPath)
   {

      m_pathInstallFolder = strPath;

   }


   ::file::path acme_dir::bookmark()
   {

      return localconfig() / "bookmark";

   }





   ::file::path acme_dir::sys_temp()
   {

      return appdata() / "time";

   }


   //::string acme_dir::dir_root()
   //{

   //   return "";

   //}


   //::file::path acme_dir::home()
   //{

   //   return "";

   //}


   //::file::path acme_dir::program_data()
   //{

   //   return "";

   //}


   ::file::path acme_dir::ca2appdata()
   {

      return ca2roaming() / "appdata";

   }



   ::file::path acme_dir::public_root()
   {

      return program_data() / "ca2";

   }

   ::file::path acme_dir::ca2roaming()
   {

      return roaming() / "ca2";

   }


   ::file::path acme_dir::localconfig()
   {

      return ca2roaming() / "localconfig";

   }


   ::file::path acme_dir::module()
   {

      return ::acme_dir::module();

   }

   //
   //::file::path acme_dir::base_module()
   //{
   //
   //   return "";
   //
   //}
   //

   //::file::path acme_dir::ca2_module()
   //{
   //
   //   return "";
   //
   //}
   //
   ::file::path acme_dir::archive()
   {

      return "";

   }



   ::file::path acme_dir::tool()
   {

      return "";

   }


   //::file::path acme_dir::roaming()
   //{

   //   return "";

   //}


   ::file::path acme_dir::pathfind(const string& pszEnv, const string& pszTopic, const string& pszMode)
   {

      ::file::patha stra;

      stra.add_tokens(pszEnv, ":", false);

      string strCandidate;

      for (i32 i = 0; i < stra.get_count(); i++)
      {

         strCandidate = stra[i] / pszTopic;

         //if (m_pcontext->m_papexcontext->file().exists(strCandidate))
         if (file_exists(strCandidate))
         {

            return strCandidate;

         }

      }

      return "";

   }


   //::file::path acme_dir::get_memory_map_base_folder_path()
   //{

   //   return "";

   //}


   ::file::path acme_dir::user_appdata_local()
   {

      //return _shell_get_special_folder_path(CSIDL_LOCAL_APPDATA);

      return home() / ".config";

   }


} // namespace macos



   
