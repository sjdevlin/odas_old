    
    #include "mod_classify.h"

    mod_classify_obj * mod_classify_construct(const mod_classify_cfg * mod_classify_config, const msg_hops_cfg * msg_hops_config, const msg_categories_cfg * msg_categories_config) {

        mod_classify_obj * obj;

        obj = (mod_classify_obj *) malloc(sizeof(mod_classify_obj));

        obj->hop2frame = hop2frame_construct_zero(msg_hops_config->hopSize, 
                                                  mod_classify_config->frameSize,
                                                  msg_hops_config->nChannels);

        obj->frames = frames_construct_zero(msg_hops_config->nChannels, 
                                            mod_classify_config->frameSize);

        obj->frame2freq = frame2freq_construct_zero(mod_classify_config->frameSize, 
                                                    (mod_classify_config->frameSize)/2+1);

        obj->freqs = freqs_construct_zero(msg_hops_config->nChannels, 
                                          (mod_classify_config->frameSize)/2+1);

        obj->freq2acorr = freq2acorr_construct_zero(msg_hops_config->nChannels, 
                                                    (mod_classify_config->frameSize)/2+1);

        obj->acorrs = acorrs_construct_zero(msg_hops_config->nChannels, 
                                            (mod_classify_config->frameSize)/2+1);

        obj->acorr2pitch = acorr2pitch_construct_zero(msg_hops_config->nChannels, 
                                                      (mod_classify_config->frameSize)/2+1, 
                                                      mod_classify_config->winSize);

        obj->pitches = pitches_construct_zero(msg_hops_config->nChannels);

        obj->pitch2category = pitch2category_construct_zero(msg_hops_config->nChannels, 
                                                            mod_classify_config->tauMin, 
                                                            mod_classify_config->tauMax, 
                                                            mod_classify_config->deltaTauMax, 
                                                            mod_classify_config->alpha, 
                                                            mod_classify_config->gamma, 
                                                            mod_classify_config->phiMin, 
                                                            mod_classify_config->r0);

        return obj;

    }

    void mod_classify_destroy(mod_classify_obj * obj) {

        hop2frame_destroy(obj->hop2frame);
        frames_destroy(obj->frames);
        frame2freq_destroy(obj->frame2freq);
        freqs_destroy(obj->freqs);
        freq2acorr_destroy(obj->freq2acorr);
        acorrs_destroy(obj->acorrs);
        acorr2pitch_destroy(obj->acorr2pitch);
        pitches_destroy(obj->pitches);
        pitch2category_destroy(obj->pitch2category);

        free((void *) obj);

    }

    int mod_classify_process(mod_classify_obj * obj) {

        int rtnValue;

        if (msg_hops_isZero(obj->in) == 0) {

            hop2frame_process(obj->hop2frame, obj->in->hops, obj->frames);
            frame2freq_process(obj->frame2freq, obj->frames, obj->freqs);
            freq2acorr_process(obj->freq2acorr, obj->freqs, obj->acorrs);
            acorr2pitch_process(obj->acorr2pitch, obj->acorrs, obj->pitches);
            pitch2category_process(obj->pitch2category, obj->pitches, obj->out->categories);

            obj->out->timeStamp = obj->in->timeStamp;

            rtnValue = 0;

        }
        else {

            msg_categories_zero(obj->out);

            rtnValue = -1;

        }

        return rtnValue;

    }

    void mod_classify_connect(mod_classify_obj * obj, msg_hops_obj * in, msg_categories_obj * out) {

        obj->in = in;
        obj->out = out;

    }

    void mod_classify_disconnect(mod_classify_obj * obj) {

        obj->in = (msg_hops_obj *) NULL;
        obj->out = (msg_categories_obj *) NULL;

    }

    mod_classify_cfg * mod_classify_cfg_construct(void) {

        mod_classify_cfg * cfg;

        cfg = (mod_classify_cfg *) malloc(sizeof(mod_classify_cfg));

        return cfg;

    }

    void mod_classify_cfg_destroy(mod_classify_cfg * cfg) {

        free((void *) cfg);

    }

    void mod_classify_cfg_printf(const mod_classify_cfg * cfg) {

    }