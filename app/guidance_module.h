#include <sys/stat.h>
#include <QObject>
#include <QString>

#define SYS_LANGUAGE_INIT 0
#define SYS_LANGUAGE_JP   1
#define SYS_LANGUAGE_EN   2
#define TTSMAX (2048)

#if defined(AGL)
//**************************************************************************
// ■AGL operation
// Local operation Comment out the following definitions and
// then cancel the following comment out
//**************************************************************************
#define NAVI_AGL_DEFAULT_PATH_JAPAN	"/var/mapdata/navi_data/japan_TR9"
#define NAVI_AGL_DEFAULT_PATH_UK	"/var/mapdata/navi_data_UK/UnitedKingdom_TR9"

#else
//**************************************************************************
// ■Local operation
// To output the audio file, please place the following file
// under [build-navigation-Desktop_Qt_5_9_6_GCC_64bit-Release/package/root/bin]
// · For Japanese output: japan_TR 9
// · For English output: UnitedKingdom_TR 9
//**************************************************************************
#define NAVI_AGL_DEFAULT_PATH_JAPAN	"japan_TR9"
#define NAVI_AGL_DEFAULT_PATH_UK	"UnitedKingdom_TR9"

#endif

class Guidance_Module : public QObject
{
    Q_OBJECT
public:
    int g_voicelanguage = SYS_LANGUAGE_INIT;
    Q_INVOKABLE void guidance(const QString &text){
        char tts_voice[TTSMAX];
        int len = 0;
        memset(tts_voice,0,TTSMAX);

        if(search_map_data() == 0) {
            //**************************************************************************
            // Please copy the following files.
            // [workspace_agl_FF_5.99.6/build/tmp/work/aarch64-agl-linux/navigation/git-r0/build]
            // ・jtalk
            // ・flite
            //
            // Please place the copied file below.
            // [build-navigation-Desktop_Qt_5_9_6_GCC_64bit-Release/package/root/bin]
            //**************************************************************************
            if(g_voicelanguage == SYS_LANGUAGE_JP) {
                strncat(tts_voice, "sh jtalk '", (TTSMAX - len - 1));
            } else if(g_voicelanguage == SYS_LANGUAGE_EN)  {
                strncat(tts_voice, "sh flite '", (TTSMAX - len - 1));
            }

            len = strlen(tts_voice);
            strncat(tts_voice, text.toUtf8().data(), (TTSMAX - len - 1));

            len = strlen(tts_voice);
            strncat(tts_voice, "'&", (TTSMAX - len - 1));

            system(tts_voice);
        }
    }

    Q_INVOKABLE int search_map_data(){
        int ret = -1;
        struct stat sb;

        ret = stat(NAVI_AGL_DEFAULT_PATH_UK, &sb);
        if (ret == 0) {
            g_voicelanguage = SYS_LANGUAGE_EN;

            return ret;
        }

        ret = stat(NAVI_AGL_DEFAULT_PATH_JAPAN, &sb);
        if (ret == 0) {
            g_voicelanguage = SYS_LANGUAGE_JP;

            return ret;
        }

        return ret;
    }
};
