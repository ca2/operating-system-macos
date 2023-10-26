//
//  RoundWindowApp.m
//  axis
//
//  Created by Camilo Sasuke Tsumanuma on 27/09/14.
//
//

#include "framework.h"
#include "macOSApp.h"
#include "acme/constant/id.h"
#include "aura/_.h"
#include "apex/user/menu/menu.h"
//#include "aura/user/menu/shared.h"
#include "aura_macos/_c_mm.h"
#include "acme/operating_system/argcargv.h"


bool application_get_bool(void * pApplication, const char * pszItem);

void ns_main_async(dispatch_block_t block);


NSMenu * ns_create_menu(::apex::menu * pmenu, bool bMainMenu);

void ns_create_menu(NSMenu * menu, ::apex::menu * pmenu, bool bMainMenu);

NSString * __nsstring(const char * psz);
//#include "apex/user/menu_shared.h"

//void on_start_system(void * pSystem);

//void macos_calc_dark_mode();
void os_system_start();
int file_put_contents(const char * path, const char * contents);
void file_add_contents_raw(const char * path, const char * psz);

void application_on_menu_action(void * pApplication, const char * pszCommand);
void * application_system(void * pApplication);


void system_id_update(void* pSystem, ::i64 iUpdate, ::i64 iPayload);


//void ns_application_update(::i64 iUpdate, void * p);

void node_will_finish_launching(void * pSystem);
void system_on_open_untitled_file(void * pSystem);
void system_on_open_file(void * pSystem, const char * pszFile);


//void system_call_update_app_activated();
void macos_on_app_changed_occlusion_state();

void set_apex_system_as_thread();


@implementation macOSApp


//@synthesize windowcontroller;
- (id)initWithMainMenu:(::apex::menu *) pmenuMain
{

   self = [super init];
   
   m_pmenuMain = pmenuMain;
   
   //[ self application_menu_update ];
   


//
//   [[[NSWorkspace sharedWorkspace] notificationCenter]
//    addObserver:self
//    selector:@selector(applicationDidChangeOcclusionState:)
//    name:NSApplicationDidChangeOcclusionStateNotification
//    object:nil];
   return self;
}

-(void)dealloc
{
   
   
   
}


-(void)application_handle: (long long) l withPointer :(void *) p
{
   
   if(l == id_application_menu_update)
   {
      
      [self application_menu_update ];
      
   }
   
}


-(void)application_menu_update
{
   
   m_menu = [ NSApp mainMenu ];
   
   [ m_menu removeAllItems ];
   
   ns_create_menu(m_menu, m_pmenuMain, true);
      
//   [ NSApp setMainMenu: m_menu];
   
//   m_menu = [[NSMenu alloc] initWithTitle:@"menubar_menu"];
//   m_menuitema = [[NSMutableArray alloc] init];
//   
//   m_menuida = [[NSMutableArray alloc] init];
//   
//   // Monitor menu/dock theme changes...
//   //   [NSDistributedNotificationCenter.defaultCenter addObserver:self selector:@selector(themeChanged:) name:@"AppleInterfaceThemeChangedNotification" object: nil];
//   
//   //int iCount = pbridge->_get_notification_area_action_count();
//   
//   //int iCount = 1;
//   
//   for(int i = 0; i < m_papplicationmenu->get_count(); i++)
//   {
//      
//      //      char * pszName = NULL;
//      //      char * pszId = NULL;
//      //      char * pszLabel = NULL;
//      //      char * pszAccelerator = NULL;
//      //      char * pszDescription = NULL;
//      //
//      //      pbridge->_get_notification_area_action_info(&pszName, &pszId, &pszLabel, &pszAccelerator, &pszDescription, i);
//      
//      auto & menuitem = m_papplicationmenu->element_at(i);
//      
//      char * pszName = strdup(menuitem.m_strName);
//      char * pszId = strdup(menuitem.m_strId);
//      char * pszLabel = strdup(menuitem.m_strName);
//      char * pszAccelerator = strdup(menuitem.m_strMacosAccelerator);
//      char * pszDescription = strdup(menuitem.m_strDescription);
//      NSString * strTitle = NULL;
//      
//      NSString * strId = NULL;
//      
//      NSMenuItem * item = NULL;
//      
//      if(strcasecmp(pszName, "separator") == 0)
//      {
//         
//         strTitle = [[NSString alloc] initWithUTF8String: pszName];
//         
//         strId = [[NSString alloc] initWithUTF8String: pszName];
//         
//         item = [NSMenuItem separatorItem];
//         
//      }
//      else
//      {
//         
//         strTitle = [[NSString alloc] initWithUTF8String: pszName];
//         
//         strId = [[NSString alloc] initWithUTF8String: pszId];
//         
//         item = [[NSMenuItem alloc] initWithTitle:  strTitle action: @selector(on_os_menu_item:) keyEquivalent:@"" ];
//         
//      }
//      
//      [item setTarget:self];
//      
//      [m_menu addItem:item];
//      
//      [m_menuitema addObject: item];
//      
//      [m_menuida addObject: strId];
//      
//      if(pszName) free(pszName);
//      if(pszId) free(pszId);
//      if(pszLabel) free(pszLabel);
//      if(pszAccelerator) free(pszAccelerator);
//      if(pszDescription) free(pszDescription);
//   }
//   
//   [m_menu setDelegate:self];
//   
//   [ NSApp setMainMenu: m_menu];

      [[[NSWorkspace sharedWorkspace] notificationCenter]
       addObserver:self
       selector:@selector(applicationActivity:)
       name:NSWorkspaceActiveSpaceDidChangeNotification
       object:nil];

}

-(void)continueInitialization
{
 
   [ super continueInitialization ];
   
   bool bNoDock = application_get_bool(m_pApplication, "no_dock");
   
   if(bNoDock)
   {
      
      nsapp_activation_policy_accessory();
      
   }

   [NSApp activateIgnoringOtherApps:YES];

   
}


-(void)applicationActivity:(NSNotification *)notification
{
   
   NSRunningApplication *app = [[notification userInfo] objectForKey:@"NSWorkspaceApplicationKey"];
   
   NSString * strName = app.localizedName;
   //if([ isEqualToString:@"ScreenSaverEngine"])
   {
      printf("NOTIFICATION: %s", [strName UTF8String]);

      // Your code here
   }
}


- (void)on_os_menu_item:(id)sender
{
   
   NSMenuItem * pitem = (NSMenuItem *) sender;
   
   for(int i = 0; i < [m_menuitema count]; i++)
   {
      
      if(pitem == [m_menuitema objectAtIndex:i])
      {
         
         const char * psz = [[m_menuida objectAtIndex:i] UTF8String];
         
         //m_pbridge->notification_area_action(psz);
         
         application_on_menu_action(m_pApplication, psz);
         
         return;
         
      }
      
   }
   
}


- (void)on_command:(id)sender
{
   
   NSMenuItem * pitem = (NSMenuItem *) sender;
   
   NSString * str = (NSString *)[pitem representedObject];
   
   if(str != nil)
   {
         
      const char * psz = [str UTF8String];
         
      application_on_menu_action(m_pApplication, psz);
         
   }
   
}


- (void)applicationWillFinishLaunching:(NSNotification *)notification
{
   
   //macos_calc_dark_mode();
   
   [ self application_menu_update ];
   
   
   [ super applicationWillFinishLaunching: notification];
   
//   node_will_finish_launching(application_system(m_pApplication));
//
//   NSAppleEventManager *appleEventManager = [NSAppleEventManager sharedAppleEventManager];
//
//   [appleEventManager setEventHandler:self andSelector:@selector(handleGetURLEvent:withReplyEvent:) forEventClass:kInternetEventClass andEventID:kAEGetURL];
   
}


- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
   
   //set_apex_system_as_thread();
   //MessageBox(NULL, "applicationDidFinishLaunching", "applicationDidFinishLaunching", e_message_box_ok);
   
   //defer_run_system();
   
}


- (BOOL)applicationShouldHandleReopen:(NSApplication *)sender hasVisibleWindows:(BOOL)flag
{
   
   //MessageBox(NULL, "applicationShouldHandleReopen", "applicationShouldHandleReopen", e_message_box_ok);
   
   system_id_update(application_system(m_pApplication), id_app_activated, 0);

   return NO;
   
}

- (void)applicationDidChangeOcclusionState:(NSNotification *)notification
{
   
   //macos_on_app_changed_occlusion_state();
   
}


- (BOOL)applicationOpenUntitledFile:(NSApplication *)sender
{
   
   //file_put_contents("/eco/001.txt", "applicationOpenUntitledFile");
   
   system_on_open_untitled_file(application_system(m_pApplication));
   
   return YES;
   
}



- (BOOL)application:(NSApplication *)sender openFile:(NSString *)filename
{
   
   //file_put_contents("/Users/camilo/debug/open_file.txt", [filename UTF8String]);

   system_on_open_file(application_system(m_pApplication), [filename UTF8String]);
   
   return true;
   
}



- (void)application:(NSApplication *)sender openFiles:(NSArray<NSString *> *)filenames
{
   
   
   //file_put_contents("/Users/camilo/debug/open_files.txt", "");

   unsigned long ulCount = [filenames count];
   
   if(ulCount <= 0)
   {
      
      return;
      
   }
   
   //char ** psza = (char **) malloc(ulCount * sizeof(char*));
   
   for(unsigned long ul = 0; ul < ulCount; ul++)
   {
      
      const char * psz = [[filenames objectAtIndex:ul] UTF8String];
      
      system_on_open_file(application_system(m_pApplication), psz);
      
      //psza[ul] = psz;
      
   }
   
//   defer_run_system(psza, (int) ulCount);
//
//
}


- (void)application:(NSApplication *)application open:(NSURL * )url
{
   
   
   //file_put_contents("/Users/camilo/debug/open(url).txt", [[url absoluteString] UTF8String]);

   //file_put_contents("/eco/006.txt", "open");
   //file_add_contents_raw("/eco/006.txt", [[url absoluteString] UTF8String]);
   
   //MessageBox(NULL, "application: openFile", "application: openFile", e_message_box_ok);
   
   system_on_open_file(application_system(m_pApplication), [[url absoluteString] UTF8String]);
   
}


- (BOOL)application:(id)sender
  openFileWithoutUI:(NSString *)filename;
{
   
   
   //file_put_contents("/Users/camilo/debug/openFileWithoutUI(url).txt", [filename UTF8String]);

   //file_put_contents("/eco/007.txt", "openFileWithoutUI");
   //file_add_contents_raw("/eco/007.txt", [filename UTF8String]);
   
   
   
   //MessageBox(NULL, "application: openFile", "application: openFile", e_message_box_ok);
   
   system_on_open_file(application_system(m_pApplication), [filename UTF8String]);
   
   return TRUE;
   
}

- (void)application:(NSApplication *)application openURLs:(NSArray<NSURL *> *)urls
{
   
   
   //file_put_contents("/Users/camilo/debug/open_urls.txt", "");

   unsigned long ulCount = [urls count];
   
   if(ulCount <= 0)
   {
      
      return;
      
   }
   
   //char ** psza = (char **) malloc(ulCount * sizeof(char*));
   
   for(unsigned long ul = 0; ul < ulCount; ul++)
   {
      
      const char * psz = [[[urls objectAtIndex:ul] absoluteString] UTF8String];
      
      //psza[ul] = psz;
      
      //file_add_contents_raw("/Users/camilo/debug/open_urls.txt", psz);
      //file_add_contents_raw("/Users/camilo/debug/open_urls.txt", "\n");
      system_on_open_file(application_system(m_pApplication), psz);
      
      //free
      
   }
   
   //defer_run_system(psza, (int) ulCount);
   
   

}



- (void)applicationWillTerminate:(NSNotification *)notification
{
   
   
   
}



//- (void)sendEvent:(NSEvent *)theEvent
//{
//
//   /*
//
//   char szEvent[128];
//
//   ·zero(szEvent);
//
//   if([theEvent type] == NSLeftMouseDown)
//   {
//
//      strcpy(szEvent, "NSLeftMouseDown");
//
//   }
//   else if([theEvent type] == NSLeftMouseUp)
//   {
//
//      strcpy(szEvent, "NSLeftMouseUp");
//
//   }
//
//   if(strlen(szEvent) > 0)
//   {
//
//      char szEventCopy[128];
//
//      strcpy(szEventCopy, szEvent);
//
//      printf("\n%s", szEventCopy);
//
//   }
//
//   */
//
//   [super sendEvent:theEvent];
//
//}
- (void)handleGetURLEvent:(NSAppleEventDescriptor *)event
           withReplyEvent:(NSAppleEventDescriptor *)replyEvent {
   
   
   // Extract the URL from the Apple event and handle it here.
   NSString* url = [[event paramDescriptorForKeyword:keyDirectObject] stringValue];
   
   
   //file_put_contents("/Users/camilo/debug/handleGetURLEvent.txt", [url  UTF8String]);


   system_on_open_file(application_system(m_pApplication), [url UTF8String]);
   
}


-(NSMenu *) applicationDockMenu:(NSApplication*)sender
{

   return m_menu;
   
}
//
//
//- (void) ns_add_menu :(NSMenu *) menuParent withParent: (const char *) pszParent  withSharedMenu : (menu_shared *) pmenushared
//{
//   
//   if(!pmenushared)
//   {
//      
//      return;
//      
//   }
//
//      for(int i = 0; i < pmenushared->m_iCount; i++)
//      {
//
//         if(!strcmp("separator", pmenushared->m_ppszId[i]))
//         {
//            
//            NSMenuItem * menuitem = [NSMenuItem separatorItem];
//            
//            [menuParent addItem: menuitem];
//
//         }
//         else if(!strcmp(pszParent, pmenushared->m_ppszParent[i]))
//         {
//         
//            NSString * strTitle = [[NSString alloc] initWithUTF8String:pmenushared->m_ppszMenu[i]];
//
//            NSMenuItem * menuitem = [[NSMenuItem alloc] initWithTitle:strTitle action:@selector(on_command:) keyEquivalent:@""];
//      
//            NSString * strId = [[NSString alloc] initWithUTF8String:pmenushared->m_ppszId[i]];
//
//            pmenushared->m_ositema[i] = (__bridge void * )menuitem;
//            
//            [menuitem setTarget: self];
//
//            [menuitem setRepresentedObject: strId];
//         
//            [menuParent addItem: menuitem];
//
//         }
//
//      }
//
//
//}


- (void)play:(id)sender
{
   
   NSMenuItem * pitem = (NSMenuItem *) sender;
   
   for(int i = 0; i < [m_menuitema count]; i++)
   {
      
      if(pitem == [m_menuitema objectAtIndex:i])
      {
         
         const char * psz = [[m_menuida objectAtIndex:i] UTF8String];
         
         //m_pbridge->notification_area_action(psz);
         
         application_on_menu_action(m_pApplication, psz);
         
         return;
         
      }
      
   }
   
}





//-(void) fetch_dark_mode
//{
//   NSString *interfaceStyle = [NSUserDefaults.standardUserDefaults valueForKey:@"AppleInterfaceStyle"];
//   int iDarkMode = [interfaceStyle isEqualToString:@"Dark"];
//
//   system_id_update(application_system(m_pApplication), id_set_dark_mode, iDarkMode);
//
//}


@end


void os_menu_item_enable(void * pitem, bool bEnable)
{

   NSMenuItem * pmenuitem = (__bridge NSMenuItem *) pitem;

   ns_main_async(^()
   {

      [pmenuitem setEnabled: bEnable];

   });

}


void os_menu_item_check(void * pitem, bool bCheck)
{

   NSMenuItem * pmenuitem = (__bridge NSMenuItem *) pitem;

   ns_main_async(^()
   {
      
      if(bCheck)
      {

         [pmenuitem setState: NSControlStateValueOn];
         
      }
      else
      {
         
         [pmenuitem setState: NSControlStateValueOff];
         
      }

   });

}


//NSMenu * _ns_create_main_menu(menu_shared * pmenushared)
//{
//   
//   id menuMain = [NSMenu alloc];
//   
//   macOSApp * papp = (macOSApp *) [[NSApplication sharedApplication] delegate ];
//   
//   {
//      
//      id menuitemApp = [NSMenuItem alloc];
//      
//      [menuMain addItem: menuitemApp];
//      
//      id strAppName = __nsstring(pmenushared->application_name());
//      
//      id menuApp = [[NSMenu alloc] initWithTitle: strAppName];
//      
//      [menuitemApp setSubmenu: menuApp];
//      
//      id strQuitTitle = __nsstring("Quit " +  pmenushared->application_name());
//      
//      id menuitemQuit = [[NSMenuItem alloc] initWithTitle:strQuitTitle
//                                                   action:@selector(terminate:) keyEquivalent:@"q"];
//
//      [ papp ns_add_menu : menuApp withParent: "" withSharedMenu: pmenushared];
//
//      [menuApp addItem: menuitemQuit];
//      
//   }
//   
//   {
//      
//      id menuitemView = [NSMenuItem alloc];
//      
//      [menuMain addItem: menuitemView];
//      
//      id menuView = [[NSMenu alloc] initWithTitle:__nsstring("View")];
//      
//      [menuView setDelegate: [ [NSApplication sharedApplication] delegate ] ];
//      
//      [menuitemView setSubmenu: menuView];
//      
//      id strFxxTitle = __nsstring("Transparent Frame");
//      
//      NSMenuItem * menuitemFxx = [[NSMenuItem alloc] initWithTitle:strFxxTitle
//                                                            action:@selector(on_command:) keyEquivalent:@"f"];
//      
//      [ papp ns_add_menu : menuView withParent: "view" withSharedMenu: pmenushared];
//
//      [menuitemFxx setRepresentedObject: @"transparent_frame"];
//      
//      [menuView addItem: menuitemFxx];
//      
//   }
//
//   return menuMain;
//   
//}
//
//
//void ns_create_main_menu(menu_shared * pmenushared)
//{
//
//   menu_shared_increment_reference_count(pmenushared);
//
//   ns_main_async(
//   ^{
//      
//      NSMenu * menuMain = _ns_create_main_menu(pmenushared);
//   
//      [NSApp setMainMenu:menuMain];
//      
//      menu_shared_release(pmenushared);
//      
//   });
//   
//}


void os_begin_system();


void ns_app_run();

void ns_apple_set_application_delegate(void * pApplication, macos_app * pappdelegate);
void * apple_get_application_delegate(void * pApplication);

void defer_create_windowing_application_delegate(void * pApplication, ::apex::menu * pmenuMain)
{
   
   macos_app * pappdelegate = (__bridge macos_app *) apple_get_application_delegate(pApplication);
   
   if(pappdelegate == nullptr)
   {
      
      pappdelegate = [ [ macOSApp alloc] initWithMainMenu: pmenuMain];
      
      ns_apple_set_application_delegate(pApplication, pappdelegate);
      
   }
   
}
   
//}
//
//void windowing_macos_application_main(void * pApplication, int argc, char *argv[])
//{
   
//   NSApplication * application = [NSApplication sharedApplication];
//
//
//
//   appDelegate->m_pApplication = pApplication;
//
//   [ application setDelegate:appDelegate];
//
//   [ appDelegate continueInitialization ];
//
//   [appDelegate fetch_dark_mode];
   
   //[m_statusitem setEnabled:YES];
   
   //[NSApplication sharedApplication];
   
   
   
   //[NSApp run];
   
//}


//-(void)applicationActivity:(NSNotification *)notification
//{
//   NSRunningApplication *app = [[notification userInfo] objectForKey:@"NSWorkspaceApplicationKey"];
//   
//   NSString * strName = app.localizedName;
//   //if([ isEqualToString:@"ScreenSaverEngine"])
//   {
//      printf("NOTIFICATION: %s", [strName UTF8String]);
//
//      // Your code here
//   }
//}
//
//
//
//- (void)on_command:(id)sender
//{
//   
//   NSMenuItem * pitem = (NSMenuItem *) sender;
//   
//   NSString * str = (NSString *)[pitem representedObject];
//if(str != nil)
//{
//         const char * psz = [str UTF8String];
//         
//         //m_pbridge->notification_area_action(psz);
//         
//         on_application_menu_action(psz);
//         
//         return;
//         
//      //}
//      
//   }
//   
//}
//- (void)applicationWillFinishLaunching:(NSNotification *)notification
//{
//NSAppleEventManager *appleEventManager = [NSAppleEventManager sharedAppleEventManager];// 1
//[appleEventManager setEventHandler:self andSelector:@selector(handleGetURLEvent:withReplyEvent:) forEventClass:kInternetEventClass andEventID:kAEGetURL];
//   
//}
//
//- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
//{
//   
//   set_apex_system_as_thread();
//   //MessageBox(NULL, "applicationDidFinishLaunching", "applicationDidFinishLaunching", e_message_box_ok);
//   
//   defer_run_system();
//   
//}
//
//
//- (BOOL)applicationShouldHandleReopen:(NSApplication *)sender hasVisibleWindows:(BOOL)flag
//{
//   
//   //MessageBox(NULL, "applicationShouldHandleReopen", "applicationShouldHandleReopen", e_message_box_ok);
//   
//   system_call_update_app_activated();
//
//   return NO;
//   
//}
//
//- (void)applicationDidChangeOcclusionState:(NSNotification *)notification
//{
//   
//   //macos_on_app_changed_occlusion_state();
//   
//}
//
//
//- (BOOL)applicationOpenUntitledFile:(NSApplication *)sender
//{
//   
//   file_put_contents("/eco/001.txt", "applicationOpenUntitledFile");
//   //MessageBox(NULL, "applicationOpenUntitledFile", "applicationOpenUntitledFile", e_message_box_ok);
//   
//   defer_run_system();
//   
//   //__start_system_with_file(NULL);
//   
//   return YES;
//   
//}
//
//
//
//- (BOOL)application:(NSApplication *)sender openFile:(NSString *)filename
//{
//   
//   file_put_contents("/eco/002.txt", "applicationOpenFile");
//   file_put_contents("/eco/003.txt", [filename UTF8String]);
//
//   //MessageBox(NULL, "application: openFile", "application: openFile", e_message_box_ok);
//   
//   defer_run_system([filename UTF8String]);
//   
//   return true;
//   
//}
//
//
//
//- (void)application:(NSApplication *)sender openFiles:(NSArray<NSString *> *)filenames
//{
//   
//   unsigned long ulCount = [filenames count];
//   
//   if(ulCount <= 0)
//   {
//      
//      return;
//      
//   }
//   
//   char ** psza = (char **) malloc(ulCount * sizeof(char*));
//   
//   for(unsigned long ul = 0; ul < ulCount; ul++)
//   {
//      
//      char * psz = strdup([[filenames objectAtIndex:ul] UTF8String]);
//      
//      psza[ul] = psz;
//      
//   }
//   
//   defer_run_system(psza, (int) ulCount);
//   
//   
//}
//- (void)application:(NSApplication *)application open:(NSURL * )url
//{
//   file_put_contents("/eco/006.txt", "open");
//   file_add_contents_raw("/eco/006.txt", [[url absoluteString] UTF8String]);
//   
//   //MessageBox(NULL, "application: openFile", "application: openFile", e_message_box_ok);
//   
//   defer_run_system([[url absoluteString] UTF8String]);
//}
//
//- (BOOL)application:(id)sender
//  openFileWithoutUI:(NSString *)filename;
//{
//   file_put_contents("/eco/007.txt", "openFileWithoutUI");
//   file_add_contents_raw("/eco/007.txt", [filename UTF8String]);
//   
//   //MessageBox(NULL, "application: openFile", "application: openFile", e_message_box_ok);
//   
//   defer_run_system([filename UTF8String]);
//}
//
//- (void)application:(NSApplication *)application openURLs:(NSArray<NSURL *> *)urls
//{
//   unsigned long ulCount = [urls count];
//   
//   if(ulCount <= 0)
//   {
//      
//      return;
//      
//   }
//   
//   char ** psza = (char **) malloc(ulCount * sizeof(char*));
//   
//   for(unsigned long ul = 0; ul < ulCount; ul++)
//   {
//      
//      char * psz = strdup([[[urls objectAtIndex:ul] absoluteString] UTF8String]);
//      
//      psza[ul] = psz;
//      
//   }
//   
//   defer_run_system(psza, (int) ulCount);
//   
//   
//
//}
//
//
////- (void)sendEvent:(NSEvent *)theEvent
////{
////
////   /*
////   
////   char szEvent[128];
////   
////   ·zero(szEvent);
////   
////   if([theEvent type] == NSLeftMouseDown)
////   {
////   
////      strcpy(szEvent, "NSLeftMouseDown");
////      
////   }
////   else if([theEvent type] == NSLeftMouseUp)
////   {
////     
////      strcpy(szEvent, "NSLeftMouseUp");
////      
////   }
////   
////   if(strlen(szEvent) > 0)
////   {
////   
////      char szEventCopy[128];
////   
////      strcpy(szEventCopy, szEvent);
////      
////      printf("\n%s", szEventCopy);
////      
////   }
////   
////   */
////   
////   [super sendEvent:theEvent];
////   
////}
//- (void)handleGetURLEvent:(NSAppleEventDescriptor *)event
//           withReplyEvent:(NSAppleEventDescriptor *)replyEvent {
//   
//   // Extract the URL from the Apple event and handle it here.
//   NSString* url = [[event paramDescriptorForKeyword:keyDirectObject] stringValue];
//   
//   defer_run_system([url UTF8String]);
//   
//}
//-(NSMenu *) applicationDockMenu:(NSApplication*)sender
//{
//
//   
//   return m_menu;
//   
//}
//
////[appDelegate->m_menu setDelegate:NSApp];
//
//
//@end


void ensure_edit_menu(::apex::menu * pmenu)
{
   
   auto iEdit = pmenu->find_child_with_name("Edit");
   
   if(iEdit >= 0)
   {
    
      return;
      
   }

   auto iFile = pmenu->find_child_with_name("File");
   
   if(iFile >= 0)
   {
      
      iEdit = iFile + 1;
      
   }
   else if(pmenu->has_element())
   {
      
      iEdit = 1;
      
   }
   else
   {
    
      iEdit = 0;
      
   }
    
   pmenu->insert_at(iEdit, __new(::apex::menu("Edit", popup_flag_t{})));
      
}


NSMenu * ns_create_menu(::apex::menu * pmenu, bool bMainMenu)
{
   
   NSMenu * menu = nil;
   
   if(pmenu->m_strName.has_char())
   {
      
      menu = [ [ NSMenu alloc ] initWithTitle:__nsstring(pmenu->m_strName)];
      
   }
   else
   {
      
      menu = [ NSMenu alloc ];
      
   }
   
   ns_create_menu(menu, pmenu, bMainMenu);
   
   return menu;
   
}


void ns_create_menu(NSMenu * menu, ::apex::menu * pmenu, bool bMainMenu)
{
   
//   if(bMainMenu)
//   {
//      
//      ensure_edit_menu(pmenu);
//      
//   }
   
   for(auto pitem : *pmenu)
   {
      
      NSMenuItem * menuitem = nil;
      
      if(pitem->is_popup())
      {
         
         menuitem = [ NSMenuItem alloc ];
         
         id menuSub = ns_create_menu(pitem, false);
       
         [ menuSub setDelegate: [ [NSApplication sharedApplication] delegate ] ];
         
         [ menuitem setSubmenu: menuSub];

      }
      else if(pitem->m_strName == "separator")
      {
         
         menuitem = [NSMenuItem separatorItem];
         
      }
      else
      {
         
         id strTitle = __nsstring(pitem->m_strName);
         id strAcc = __nsstring(pitem->m_strMacosAccelerator);
         id strId = __nsstring(pitem->m_strId);
         
         menuitem = [[NSMenuItem alloc] initWithTitle:strTitle
                                                            action:@selector(on_command:) keyEquivalent:strAcc];
         
         [menuitem setRepresentedObject: strId];
         
      }

      [menu addItem: menuitem];

   }
   
}


//NSMenu * ns_create_application_menu(application_menu * pmenu)
//{
//   
//   
//   id menu = [NSMenu alloc];
//   
////   {
////      
////      id menuitemApp = [NSMenuItem alloc];
////      
////      [menuMain addItem: menuitemApp];
////      
////      id menuApp = [NSMenu alloc];
////      
////      [menuitemApp setSubmenu: menuApp];
////      
////      id strAppName = [[NSProcessInfo processInfo] processName];
////      
////      id strQuitTitle = __nsstring("Quit " + ::string([strAppName UTF8String]));
////      
////      id menuitemQuit = [[NSMenuItem alloc] initWithTitle:strQuitTitle
////                                                   action:@selector(terminate:) keyEquivalent:@"q"];
////      
////      [menuApp addItem: menuitemQuit];
////      
////   }
//
//   for(auto & item : *papplicationmenu)
//   {
//      
//      id menuitem = [ NSMenuItem alloc ];
//      
//      [ menu addItem: menuitem];
//      
//      if(item.has_element())
//      {
//      
//         id menuView = [[NSMenu alloc] initWithTitle:__nsstring(item."View")];
//      
//      [menuView setDelegate: [ [NSApplication sharedApplication] delegate ] ];
//      
//      [menuitemView setSubmenu: menuView];
//      
//      id strFxxTitle = __nsstring("Trasparentt(snowballeffect_smallerror>>>)Fxx");
//      
//      NSMenuItem * menuitemFxx = [[NSMenuItem alloc] initWithTitle:strFxxTitle
//                                                            action:@selector(on_command:) keyEquivalent:@"f"];
//      
//      [menuitemFxx setRepresentedObject: @"transparent_frame"];
//      
//      [menuView addItem: menuitemFxx];
//      
//   }
//   
//   [NSApp setMainMenu:menuMain];
//   
//   
//}


//void ns_create_main_menu()
//{
//   
//   
//   id menuMain = [NSMenu alloc];
//   
//   {
//      
//      id menuitemApp = [NSMenuItem alloc];
//      
//      [menuMain addItem: menuitemApp];
//      
//      id menuApp = [NSMenu alloc];
//      
//      [menuitemApp setSubmenu: menuApp];
//      
//      id strAppName = [[NSProcessInfo processInfo] processName];
//      
//      id strQuitTitle = __nsstring("Quit " + ::string([strAppName UTF8String]));
//      
//      id menuitemQuit = [[NSMenuItem alloc] initWithTitle:strQuitTitle
//                                                   action:@selector(terminate:) keyEquivalent:@"q"];
//      
//      [menuApp addItem: menuitemQuit];
//      
//   }
//   
//   {
//      
//      id menuitemView = [NSMenuItem alloc];
//      
//      [menuMain addItem: menuitemView];
//      
//      id menuView = [[NSMenu alloc] initWithTitle:__nsstring("View")];
//      
//      [menuView setDelegate: [ [NSApplication sharedApplication] delegate ] ];
//      
//      [menuitemView setSubmenu: menuView];
//      
//      id strFxxTitle = __nsstring("Trasparentt(snowballeffect_smallerror>>>)Fxx");
//      
//      NSMenuItem * menuitemFxx = [[NSMenuItem alloc] initWithTitle:strFxxTitle
//                                                            action:@selector(on_command:) keyEquivalent:@"f"];
//      
//      [menuitemFxx setRepresentedObject: @"transparent_frame"];
//      
//      [menuView addItem: menuitemFxx];
//      
//   }
//   
//   [NSApp setMainMenu:menuMain];
//   
//   
//}
//



//void apex_application_main(int argc, char *argv[])
//{
//
//   NSApplication * application = [NSApplication sharedApplication];
//
//   macOSApp * appDelegate = [[macOSApp alloc] init];
//
//   [application setDelegate:appDelegate];
//
//   [NSApplication sharedApplication];
//
//   bool bNoDock = argcargv_contains_paramater(argc, argv, "no_dock");
//
//   if(bNoDock)
//   {
//
//      nsapp_activation_policy_accessory();
//
//   }
////   else
////   {
////
////      nsapp_activation_policy_regular();
////
////   }
//
//
//   [NSApp activateIgnoringOtherApps:YES];
//
//   [NSApp run];
//
//}
//
//
//


//
//namespace user
//{
//
//
//
//
//   bool is_dark_mode()
//   {
//      
//         
//      return g_bMacosDarkMode;
//      
//   }
//
//
//} // namespace user





//void windowing_macos_application_main(void * pApplication, int argc, char *argv[])
//{
//
//   NSApplication * application = [NSApplication sharedApplication];
//
//   macos_app * appDelegate = [[macos_app alloc] init];
//
//   appDelegate->m_pApp = pApplication;
//
//   [application setDelegate:appDelegate];
//
//   [appDelegate fetch_dark_mode];
//
//   //[m_statusitem setEnabled:YES];
//
//   [NSApplication sharedApplication];
//
//   bool bNoDock = argcargv_contains_parameter(argc, argv, "no_dock");
////
////   if(bNoDock)
////   {
////
////      nsapp_activation_policy_accessory();
////
////   }
//
//   [NSApp activateIgnoringOtherApps:YES];
//
//   [NSApp run];
//
//}


void ns_application_handle(long long l, void * p)
{
   
   ns_main_async(^{

      macOSApp * papp = nullptr;
      
      papp = [ [NSApplication sharedApplication] delegate ] ;
      
      [papp application_handle: l withPointer:p];

   });
   
}



