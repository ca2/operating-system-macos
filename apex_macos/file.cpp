#include "framework.h"
#include "_.h"


#include <fcntl.h>


#include <dlfcn.h>
#include <sys/stat.h>


int translate_unix_error(int error)
{

   switch(error)
   {
   case 0:
      return 0;
   case ENOENT:
      return ERROR_FILE_NOT_FOUND;
   default:
      return -1;
   }

}


namespace macos
{


   bool file_get_status(::file::file_status & status, const ::file::path & path)
   {

      struct ::stat st;
   
      if(stat(path, &st) == -1)
      {
      
         return false;
      
      }

      status.m_attribute = 0;

      status.m_size = st.st_size;

      status.m_ctime = ::datetime::time(st.st_mtime);
      status.m_atime = ::datetime::time(st.st_atime);
      status.m_mtime = ::datetime::time(st.st_ctime);

      if (status.m_ctime.get_time() == 0)
      {
      
         status.m_ctime = status.m_mtime;
      
      }

      if (status.m_atime.get_time() == 0)
      {
      
         status.m_atime = status.m_mtime;
      
      }

      return true;
   
   }


   file::file()
   {

      m_iFile = (::u32) hFileNull;

   }


   file::~file()
   {

      if (m_iFile != hFileNull)
      {
         
         close();
         
      }

   }


   ::extended::status file::open(const ::file::path & lpszFileName, const ::file::e_open & efileopenParam)
   {
      
      ::file::e_open eopen(efileopenParam);

      if(m_iFile != hFileNull)
      {
       
         close();
         
      }

      ASSERT_VALID(this);
      
      ASSERT(__is_valid_string(lpszFileName));

      eopen &= ~::file::e_open_binary;

      if ((eopen & ::file::e_open_defer_create_directory) && (eopen & ::file::e_open_write))
      {
         
         pcontext->m_papexcontext->dir().mk(::file::path(lpszFileName).folder());
         
      }

      m_iFile = (::u32)hFileNull;
      
      m_strFileName.Empty();

      m_strFileName     = lpszFileName;

      ASSERT(sizeof(HANDLE) == sizeof(uptr));
      ASSERT(::file::e_open_share_compat == 0);

      // ::collection::map read/write mode
      ASSERT((::file::e_open_read|::file::e_open_write|::file::e_open_read_write) == 3);
      
      ::u32 dwFlags =  0;
      
      switch (eopen & 3)
      {
      case ::file::e_open_read:
         dwFlags |=  O_RDONLY;
         break;
      case ::file::e_open_write:
         dwFlags |=  O_WRONLY ;
         break;
      case ::file::e_open_read_write:
         dwFlags |=  O_RDWR;
         break;
      default:
         dwFlags |=  O_RDONLY;
         break;
      }

      switch (eopen & 0x70)    // ::collection::map compatibility mode to exclusive
      {
      default:
         ASSERT(false);  // invalid share mode?
      case ::file::e_open_share_compat:
      case ::file::e_open_share_exclusive:
         break;
      case ::file::e_open_share_deny_write:
         break;
      case ::file::e_open_share_deny_read:
         break;
      case ::file::e_open_share_deny_none:
         break;
      }

      if (eopen & ::file::e_open_create)
      {
         
         dwFlags |= O_CREAT;
         
         if(!(eopen & ::file::e_open_no_truncate))
         {
            
            dwFlags |= O_TRUNC;
            
         }
         
      }

      ::u32 dwPermission = 0;

      dwPermission |= S_IRUSR | S_IWUSR | S_IXUSR;
      dwPermission |= S_IRGRP | S_IWGRP | S_IXGRP;
      dwPermission |= S_IROTH | S_IXOTH;

      i32 hFile;

      hFile = ::open(m_strFileName, dwFlags, dwPermission);

      if(hFile == hFileNull)
      {

         ::u32 dwLastError = translate_unix_error(errno);

         if(dwLastError != ERROR_FILE_NOT_FOUND && dwLastError != ERROR_PATH_NOT_FOUND)
         {

            return ::error_io;

         }

         if (hFile == -1)
         {

            ::u32 dwLastError = ::get_last_error();

            return ::error_io;

         }

      }

      m_iFile = (i32)hFile;

      return ::success;

   }


   memsize file::read(void * lpBuf, memsize nCount)
   {
      
      ASSERT_VALID(this);
      
      ASSERT(m_iFile != (::u32)hFileNull);

      if (nCount == 0)
      {
         
         return 0;   // avoid Win32 "null-read"
         
      }

      ASSERT(lpBuf != nullptr);
      
      ASSERT(__is_valid_address(lpBuf, nCount));

      memsize pos = 0;
      
      memsize sizeRead = 0;
      
      memsize readNow;
      
      while(nCount > 0)
      {

         readNow = (size_t) minimum(0x7fffffff, nCount);

         size_t iRead = ::read(m_iFile, &((byte *)lpBuf)[pos], readNow);

         if(iRead == ::numeric_info<size_t>::get_allset_value ())
         {

            i32 iError = errno;

            if(iError == EAGAIN)
            {

            }

            ::file::throw_errno(errno, m_strFileName);

         }
         else if(iRead == 0)
         {
            
            break;
            
         }
         
         if(iRead > nCount)
         {
            
            nCount = 0;
            
         }
         else
         {
            
            nCount -= iRead;
            
         }
         
         pos += iRead;
         
         sizeRead += iRead;
         
      }

      return sizeRead;
      
   }


   void file::write(const void * lpBuf, memsize nCount)
   {
      
      ASSERT_VALID(this);
      
      ASSERT(m_iFile != (::u32)hFileNull);

      if (nCount == 0)
      {

         return;

      }

      ASSERT(lpBuf != nullptr);
      
      ASSERT(__is_valid_address(lpBuf, nCount, false));

      memsize pos = 0;
      
      while(nCount > 0)
      {
         
         size_t iWrite = ::write(m_iFile, &((const byte *)lpBuf)[pos], (size_t) minimum(0x7fffffff, nCount));
         
         if(iWrite == ::numeric_info<size_t>::get_allset_value ())
         {
            
            ::file::throw_errno(errno, m_strFileName);
            
         }
         
         nCount -= iWrite;
         
         pos += iWrite;
         
      }

   }


   filesize file::seek(filesize lOff, ::file::e_seek nFrom)
   {

      if(m_iFile == (::u32)hFileNull)
      {
         
         ::file::throw_errno(errno, m_strFileName);
         
      }

      ASSERT_VALID(this);
      
      ASSERT(m_iFile != (::u32)hFileNull);
      
      ASSERT(nFrom == ::file::seek_begin || nFrom == ::file::seek_end || nFrom == ::file::seek_current);
      
      ASSERT(::file::seek_begin == SEEK_SET && ::file::seek_end == SEEK_END && ::file::seek_current == SEEK_CUR);

      ::i32 lLoOffset = lOff & 0xffffffff;

      filesize posNew = ::lseek(m_iFile, lLoOffset, (::u32)nFrom);

      if(posNew  == (filesize)-1)
      {
         
         ::file::throw_errno(errno, m_strFileName);
         
      }

      return posNew;
      
   }


   filesize file::get_position() const
   {

      ASSERT_VALID(this);

      ASSERT(m_iFile != (::u32)hFileNull);

      ::i32 lLoOffset = 0;

      filesize pos = ::lseek(m_iFile, lLoOffset, SEEK_CUR);

      if(pos  == (filesize)-1)
      {
         
         ::file::throw_errno(errno, m_strFileName);
         
      }

      return pos;
      
   }


   void file::flush()
   {

   }


   void file::close()
   {
      
      ASSERT_VALID(this);
      
      ASSERT(m_iFile != (::u32)hFileNull);

      bool bError = false;
      
      if (m_iFile != (::u32)hFileNull)
      {
         
         bError = ::close(m_iFile) != 0;
         
      }

      m_iFile = (::u32) hFileNull;
      
      m_strFileName.Empty();

      if (bError)
      {
         
         ::file::throw_errno(errno, m_strFileName);
         
      }
      
   }


   void file::lock(filesize dwPos, filesize dwCount)
   {
      
      ASSERT_VALID(this);

      ASSERT(m_iFile != (::u32)hFileNull);

   }


   void file::unlock(filesize dwPos, filesize dwCount)
   {
      
      ASSERT_VALID(this);

      ASSERT(m_iFile != (::u32)hFileNull);

   }


   void file::set_size(filesize dwNewLen)
   {

      ASSERT_VALID(this);

      ASSERT(m_iFile != (::u32)hFileNull);

      if (::ftruncate(m_iFile, dwNewLen) == -1)
      {
         
         ::file::throw_errno(errno, m_strFileName);
         
      }
      
   }


   filesize file::get_size() const
   {

      ASSERT_VALID(this);

      filesize dwLen, dwCur;

      // seek is a non const operation
      file * pFile = (file*)this;
      
      dwCur = pFile->seek(0L, ::file::seek_current);
      
      dwLen = pFile->seek_to_end();
      
      if(dwCur != (u64)pFile->seek((filesize) dwCur, ::file::seek_begin))
      {

         __throw(io_exception("failed to seek back to the original position on get_length"));

      }

      return (filesize) dwLen;
      
   }


   void file::assert_valid() const
   {

      ::file::file::assert_valid();

   }


   void file::dump(dump_context & dumpcontext) const
   {

      ::file::file::dump(dumpcontext);

      dumpcontext << "with handle " << (::u32)m_iFile;
      dumpcontext << " and name \"" << m_strFileName << "\"";
      dumpcontext << "\n";

   }


   static const char * rgszFileExceptionCause[] =
   {
      
      "none",
      "matter",
      "fileNotFound",
      "badPath",
      "tooManyOpenFiles",
      "accessDenied",
      "invalidFile",
      "eraseCurrentDir",
      "directoryFull",
      "badSeek",
      "hardIO",
      "sharingViolation",
      "lockViolation",
      "diskFull",
      "endOfFile",
      
   };


   static const char szUnknown[] = "unknown";


   ::file::path file::get_file_path() const
   {
      
      ASSERT_VALID(this);

      return m_strFileName;

   }


   bool file::get_status(::file::file_status& rStatus) const
   {

      ASSERT_VALID(this);

      rStatus.m_strFullName = m_strFileName;

      if (m_iFile != hFileNull)
      {

         struct ::stat st;

         if(fstat(m_iFile, &st) == -1)
         {
            
            return false;
            
         }

         rStatus.m_size = st.st_size;

         rStatus.m_attribute = 0;

         rStatus.m_ctime = ::datetime::time(st.st_mtime);
         rStatus.m_atime = ::datetime::time(st.st_atime);
         rStatus.m_mtime = ::datetime::time(st.st_ctime);

         if (rStatus.m_ctime.get_time() == 0)
         {
            
            rStatus.m_ctime = rStatus.m_mtime;
            
         }

         if (rStatus.m_atime.get_time() == 0)
         {
            
            rStatus.m_atime = rStatus.m_mtime;
            
         }
         
      }
      
      return true;
      
   }


   bool file::is_opened() const
   {

      return m_iFile != hFileNull;
      
   }


   void file::set_file_path(const ::file::path & path)
   {
      
      ASSERT_VALID(this);
      
      ASSERT(__is_valid_string(path));
      
      m_strFileName = path;
      
   }


} // namespace win


#define _wcsdec(_cpc1, _cpc2) ((_cpc1)>=(_cpc2) ? nullptr : (_cpc2)-1)


#define _wcsinc(_pc) ((_pc)+1)


bool CLASS_DECL_APEX vfxFullPath(wstring & wstrFullPath, const wstring & wstrPath)
{

   wstrFullPath = wstrPath;

   return true;

}


CLASS_DECL_APEX void vfxGetModuleShortFileName(HINSTANCE hInst, string& strShortName)
{

   __throw(todo);

}


CLASS_DECL_APEX bool vfxResolveShortcut(string & strTarget, const char * pszSource, ::user::primitive * puiMessageParentOptional)
{

   char realname[_POSIX_PATH_MAX * 4];

   if(realpath(pszSource, realname) == 0)
   {
      
      return false;
      
   }

   strTarget = realname;

   return true;

}



