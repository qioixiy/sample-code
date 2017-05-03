/* ref: https://github.com/winlinvip/go-fdkaac */

#include <stdio.h>
#include <stdlib.h>
#include <fdk-aac/aacdecoder_lib.h>

typedef struct {
    HANDLE_AACDECODER dec;
    // Whether use ADTS mode.
    int is_adts;
    // Init util the first frame decoded.
    CStreamInfo* info;
    // The bits of sample, always 16 for fdkaac.
    int sample_bits;
    // Total filled bytes.
    UINT filled_bytes;
} aacdec_t;

static void _aacdec_init(aacdec_t* h) {
    // For lib-fdkaac, always use 16bits sample.
    // avctx->sample_fmt = AV_SAMPLE_FMT_S16;
    h->sample_bits = 16;
    h->is_adts = 0;
    h->filled_bytes = 0;

    h->dec = NULL;
    h->info = NULL;
}

static int aacdec_init_adts(aacdec_t* h) {
    _aacdec_init(h);

    h->is_adts = 1;

    h->dec = aacDecoder_Open(TT_MP4_ADTS, 1);
    if (!h->dec) {
        return -1;
    }

    return 0;
}

static int aacdec_init_raw(aacdec_t* h, char* asc, int nb_asc) {
    _aacdec_init(h);

    h->dec = aacDecoder_Open(TT_MP4_RAW, 1);
    if (!h->dec) {
        return -1;
    }

    UCHAR* uasc = (UCHAR*)asc;
    UINT unb_asc = (UINT)nb_asc;
    AAC_DECODER_ERROR err = aacDecoder_ConfigRaw(h->dec, &uasc, &unb_asc);
    if (err != AAC_DEC_OK) {
        return err;
    }

    return 0;
}

static void aacdec_close(aacdec_t* h) {
    if (h->dec) {
        aacDecoder_Close(h->dec);
    }
    h->dec = NULL;
}

static int aacdec_fill(aacdec_t* h, char* data, int nb_data, int* pnb_left) {
    h->filled_bytes += nb_data;

    UCHAR* udata = (UCHAR*)data;
    UINT unb_data = (UINT)nb_data;
    UINT unb_left = unb_data;
    AAC_DECODER_ERROR err = aacDecoder_Fill(h->dec, &udata, &unb_data, &unb_left);
    if (err != AAC_DEC_OK) {
        return err;
    }

    if (pnb_left) {
        *pnb_left = (int)unb_left;
    }

    return 0;
}

static int aacdec_sample_bits(aacdec_t* h) {
    return h->sample_bits;
}

static int aacdec_pcm_size(aacdec_t* h) {
    if (!h->info) {
        return 0;
    }
    return (int)(h->info->numChannels * h->info->frameSize * h->sample_bits / 8);
}

static int aacdec_decode_frame(aacdec_t* h, char* pcm, int nb_pcm, int* pnb_valid) {
    // when buffer left bytes not enough, directly return not-enough-bits.
    // we requires atleast 7bytes header for adts.
    if (h->is_adts && h->info && h->filled_bytes - h->info->numTotalBytes <= 7) {
        return AAC_DEC_NOT_ENOUGH_BITS;
    }

    INT_PCM* upcm = (INT_PCM*)pcm;
    INT unb_pcm = (INT)nb_pcm;
    AAC_DECODER_ERROR err = aacDecoder_DecodeFrame(h->dec, upcm, unb_pcm, 0);

    // user should fill more bytes then decode.
    if (err == AAC_DEC_NOT_ENOUGH_BITS) {
        return err;
    }
    if (err != AAC_DEC_OK) {
        return err;
    }

    // when decode ok, retrieve the info.
    if (!h->info) {
        h->info = aacDecoder_GetStreamInfo(h->dec);
    }

    // the actual size of pcm.
    if (pnb_valid) {
        *pnb_valid = aacdec_pcm_size(h);
    }

    return 0;
}

static int aacdec_sample_rate(aacdec_t* h) {
    if (!h->info) {
        return 0;
    }
    return h->info->sampleRate;
}

static int aacdec_frame_size(aacdec_t* h) {
    if (!h->info) {
        return 0;
    }
    return h->info->frameSize;
}

static int aacdec_num_channels(aacdec_t* h) {
    if (!h->info) {
        return 0;
    }
    return h->info->numChannels;
}

static int aacdec_aac_sample_rate(aacdec_t* h) {
    if (!h->info) {
        return 0;
    }
    return h->info->aacSampleRate;
}

static int aacdec_profile(aacdec_t* h) {
    if (!h->info) {
        return 0;
    }
    return h->info->profile;
}

static int aacdec_audio_object_type(aacdec_t* h) {
    if (!h->info) {
        return 0;
    }
    return h->info->aot;
}

static int aacdec_channel_config(aacdec_t* h) {
    if (!h->info) {
        return 0;
    }
    return h->info->channelConfig;
}

static int aacdec_bitrate(aacdec_t* h) {
    if (!h->info) {
        return 0;
    }
    return h->info->bitRate;
}

static int aacdec_aac_samples_per_frame(aacdec_t* h) {
    if (!h->info) {
        return 0;
    }
    return h->info->aacSamplesPerFrame;
}

static int aacdec_aac_num_channels(aacdec_t* h) {
    if (!h->info) {
        return 0;
    }
    return h->info->aacNumChannels;
}

static int aacdec_extension_audio_object_type(aacdec_t* h) {
    if (!h->info) {
        return 0;
    }
    return h->info->extAot;
}

static int aacdec_extension_sampling_rate(aacdec_t* h) {
    if (!h->info) {
        return 0;
    }
    return h->info->extSamplingRate;
}

static int aacdec_num_lost_access_units(aacdec_t* h) {
    if (!h->info) {
        return 0;
    }
    return h->info->numLostAccessUnits;
}

static int aacdec_num_total_bytes(aacdec_t* h) {
    if (!h->info) {
        return 0;
    }
    return h->info->numTotalBytes;
}

static int aacdec_num_bad_bytes(aacdec_t* h) {
    if (!h->info) {
        return 0;
    }
    return h->info->numBadBytes;
}

static int aacdec_num_total_access_units(aacdec_t* h) {
    if (!h->info) {
        return 0;
    }
    return h->info->numTotalAccessUnits;
}

static int aacdec_num_bad_access_units(aacdec_t* h) {
    if (!h->info) {
        return 0;
    }
    return h->info->numBadAccessUnits;
}

void dump_data(char *data, int size)
{
    for(int count = 0; count < size; count++) {
        printf("0x%02x ", data[count]);
    }
    printf("\n");
}

aacdec_t _aacdec_t;
int decode(char *data, int size)
{
    /* fill */
    int leftSize = 0;
    int dataSize = size;
    int ret = 0;

    if (size != 0) {
        ret = aacdec_fill(&_aacdec_t, data, dataSize, &leftSize);
        if (ret != 0) {
            printf("aacdec_fill error\n");
        } else {
            printf("aacdec_fill success\n");
        }
    }

    int pcm_size = aacdec_pcm_size(&_aacdec_t);
    if (pcm_size == 0) {
        pcm_size = 50 * 1024;
        printf("set pcm_size:%d\n", pcm_size);
    }

    char *pcm_data = malloc(pcm_size);
    int validSize = 0;

    /* decode frame#0 */
    ret = aacdec_decode_frame(&_aacdec_t, pcm_data, pcm_size, &validSize);

    if (ret != 0) {
        printf("decode frame failed, code is %d\n", ret);
    } else {
        printf("decode frame success\n");
        printf("validSize:%d\n", validSize);

        //dump_data(pcm_data, validSize);
    }
}

int main()
{
    aacdec_init_adts(&_aacdec_t);

    char data[] = {
        // frame#0
        0xff, 0xf1, 0x50, 0x80, 0x0e, 0x60, 0xfc,
        0x21, 0x17, 0x55, 0x45, 0x0d, 0x88, 0x90, 0x13, 0x04, 0x2c, 0xa4, 0x01, 0x01, 0xd0, 0x20, 0x3e,
        0x27, 0x6d, 0x38, 0x35, 0x4a, 0x0b, 0x59, 0xb5, 0xde, 0x8d, 0xad, 0x72, 0x7b, 0xa6, 0xe4, 0xd7,
        0xbe, 0x0c, 0xfa, 0xe8, 0x0e, 0x1d, 0xaa, 0xc7, 0x0a, 0x44, 0xd2, 0x33, 0x81, 0xd8, 0x24, 0x81,
        0xd4, 0xc1, 0x76, 0x9b, 0x5b, 0x88, 0x58, 0x9c, 0x23, 0x82, 0xf5, 0x2c, 0x26, 0x04, 0x94, 0x80,
        0xab, 0x7b, 0x28, 0x0a, 0x66, 0x30, 0x90, 0x0a, 0x6a, 0x02, 0x16, 0xb0, 0x50, 0x06, 0x83, 0x6e,
        0xfa, 0xea, 0xe1, 0xd7, 0x30, 0xf0, 0x9b, 0x18, 0x25, 0xfc, 0x6b, 0x42, 0x5a, 0x3c, 0x5e, 0x3c,
        0x18, 0xe7, 0xad, 0xda, 0xc2, 0xcc, 0x09, 0x04, 0xa6, 0x90, 0x91, 0xc0,
        // frame#1
        0xff, 0xf1, 0x50, 0x80,
    };

    printf("frame#0\n");
    decode(data, sizeof(data)/sizeof(data[0]));
    printf("frame#1\n");
    decode(data, 0);

    char data1[] = {
        // frame#1 continue
        0x0d, 0x40, 0xfc, 0x21, 0x17, 0x55, 0x45, 0x95, 0x18, 0x2c, 0x05, 0x44, 0x10, 0x00, 0xd6, 0x97,
        0x40, 0x7b, 0xe4, 0xb1, 0xcb, 0xcb, 0xd1, 0xa8, 0xc6, 0x40, 0x7d, 0x7c, 0xb3, 0x64, 0xd1, 0x4a,
        0xdc, 0x48, 0x53, 0xfc, 0x32, 0xaa, 0x0a, 0xe9, 0x25, 0xca, 0x7b, 0x4e, 0x5a, 0xa7, 0x4b, 0x52,
        0x96, 0xce, 0xee, 0x5a, 0xe8, 0xde, 0xe6, 0x0c, 0x7f, 0xc0, 0x70, 0x10, 0x6d, 0x54, 0x10, 0x12,
        0x0c, 0xc0, 0x52, 0x4b, 0x04, 0xe0, 0x31, 0x18, 0x08, 0x44, 0x00, 0x00, 0x3a, 0x5e, 0x82, 0xff,
        0xc8, 0xe9, 0x6b, 0x77, 0x18, 0xdd, 0x64, 0xe6, 0x00, 0x15, 0x88, 0x02, 0x62, 0x74, 0x3d, 0xd3,
        0x90, 0x02, 0x65, 0x98, 0x80, 0x1c,
        // frame#2, decoded
        0xff, 0xf1, 0x50, 0x80, 0x0e, 0x60, 0xfc,
        0x21, 0x17, 0x55, 0x45, 0x0d, 0x88, 0x90, 0x13, 0x04, 0x2c, 0xa4, 0x01, 0x01, 0xd0, 0x20, 0x3e,
        0x27, 0x6d, 0x38, 0x35, 0x4a, 0x0b, 0x59, 0xb5, 0xde, 0x8d, 0xad, 0x72, 0x7b, 0xa6, 0xe4, 0xd7,
        0xbe, 0x0c, 0xfa, 0xe8, 0x0e, 0x1d, 0xaa, 0xc7, 0x0a, 0x44, 0xd2, 0x33, 0x81, 0xd8, 0x24, 0x81,
        0xd4, 0xc1, 0x76, 0x9b, 0x5b, 0x88, 0x58, 0x9c, 0x23, 0x82, 0xf5, 0x2c, 0x26, 0x04, 0x94, 0x80,
        0xab, 0x7b, 0x28, 0x0a, 0x66, 0x30, 0x90, 0x0a, 0x6a, 0x02, 0x16, 0xb0, 0x50, 0x06, 0x83, 0x6e,
        0xfa, 0xea, 0xe1, 0xd7, 0x30, 0xf0, 0x9b, 0x18, 0x25, 0xfc, 0x6b, 0x42, 0x5a, 0x3c, 0x5e, 0x3c,
        0x18, 0xe7, 0xad, 0xda, 0xc2, 0xcc, 0x09, 0x04, 0xa6, 0x90, 0x91, 0xc0,
    };

    printf("frame#1\n");
    decode(data1, sizeof(data1)/sizeof(data1[0]));
    printf("frame#2\n");
    decode(data1, 0);
}
