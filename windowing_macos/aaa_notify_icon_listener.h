#pragma once


namespace user
{


   class CLASS_DECL_BASE notify_icon_listener
   {
   public:


      class CLASS_DECL_BASE item :
         virtual public object
      {
      public:

         string m_strName;
         string m_strId;
         string m_strLabel;
         string m_strAccelerator;
         string m_strDescription;

         item();

         item(string strName, string strId = "", string strLabel = "", string strAccelerator = "", string strDescription = "");

         virtual ~item();

      };


      __pointer_array(item)      m_notifyiconitema;


      notify_icon_listener();
      virtual ~notify_icon_listener();


      virtual void OnNotifyIconMessage(unsigned int uNotifyIcon, unsigned int message);
      virtual void OnNotifyIconContextMenu(unsigned int uNotifyIcon);
      virtual void OnNotifyIconLButtonDblClk(unsigned int uNotifyIcon);
      virtual void OnNotifyIconLButtonDown(unsigned int uNotifyIcon);


      virtual int _get_notification_area_action_count();
      virtual const char * _get_notification_area_action_name(int iIndex);
      virtual const char * _get_notification_area_action_id(int iIndex);
      virtual const char * _get_notification_area_action_label(int iIndex);
      virtual const char * _get_notification_area_action_accelerator(int iIndex);
      virtual const char * _get_notification_area_action_description(int iIndex);
      virtual void call_notification_area_action(const char * pszId);


      virtual bool notify_icon_insert_item(index & iIndex, string strName, string strId = "", string strLabel = "", string strAccelerator = "", string strDescription = "");


   };


} // namespace user



