// Created by camilo on 2024-02-09 20:50 <3ThomasBorregaardSorensen!!
#include <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
//#import <MediaPlayer/MediaPlayer.h>
//
//void ns_main_async(dispatch_block_t block);
//
void macos_play_media_item(void * pMPMediaItem)
{
//ns_main_async(^()
//              {
//   
//   
//   NSError * perror = nil;
//   //   [[AVAudioSession sharedInstance ] setCategory:AVAudioSessionCategoryPlayback
//   //
//   //
//   //   error:&perror];
//   MPMediaItem * itemRequest=(__bridge MPMediaItem*)pMPMediaItem;
//   MPMusicPlayerController *controller = [MPMusicPlayerController systemMusicPlayer];
//   NSArray * arrayOfMediaItems=[[NSArray alloc] initWithObjects: itemRequest, nil];
//   MPMediaItemCollection *collection = [[MPMediaItemCollection alloc] initWithItems:arrayOfMediaItems];
//   MPMediaItem *item = [collection representativeItem];
//   
//   [controller setQueueWithItemCollection:collection];
//   [controller setNowPlayingItem:item];
//   [controller setVolume:1.0f];
//   [controller prepareToPlay];
//   [controller play];
//   
//});
}




void macos_av_session_initialize()
{
 
   //NSError *setCategoryErr = nil;
   //NSError *activationErr  = nil;
   //[[AVAudioSession sharedInstance] setCategory: AVAudioSessionCategoryPlayback error:&setCategoryErr];
   //[[AVAudioSession sharedInstance] setActive:YES error:&activationErr];
   
}




