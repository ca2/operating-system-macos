#pragma once


namespace multimedia
{


   namespace audio_mixer_core_audio
   {


      class CLASS_DECL_AUDIO_MIXER_CORE_AUDIO destination :
         virtual public ::multimedia::audio_mixer_core_audio::source,
         virtual public ::multimedia::audio_mixer::destination
      {
      public:


         destination();
         destination(const destination & destination);
         ~destination() override;


         uint32_t get_component_type() override;
         void update_all_controls() override;
         void initialize_all_controls() override;
         void initialize_source_info() override;

         ::multimedia::audio_mixer::source_array & get_source_info() override;
         //void operator delete(void *);

         destination & operator = (const destination & device);

         ::multimedia::audio_mixer::device * get_device() override;
         void set_device(::multimedia::audio_mixer::device * pdevice) override;


         virtual uint32_t get_mixer_line_id() override;

      };


   } // namespace audio_mixer_core_audio



} // namespace multimedia




