#ifndef FILE_OPERATION_H
#define FILE_OPERATION_H
#include <QObject>
#include <QString>

/******************************************************
 * Write access token of mapbox in /etc/mapAccessToken
 ******************************************************/
#define MAP_ACCESS_TOKEN_FILEPATH "/etc/mapAccessToken"

class File_Operation: public QObject{

    Q_OBJECT
public:
    Q_INVOKABLE QString getMapAccessToken() {
        char buf[512];
        QString mapAccessToken = "";

        FILE* filep = fopen(qPrintable(MAP_ACCESS_TOKEN_FILEPATH), "r");
        if (!filep) {
            fprintf(stderr,"Failed to open mapAccessToken file \"%s\": %m", qPrintable(MAP_ACCESS_TOKEN_FILEPATH));
            return mapAccessToken;
        }
        if (!fgets(buf, 512, filep)) {
            fprintf(stderr,"Failed to read mapAccessToken from mapAccessToken file \"%s\"", qPrintable(MAP_ACCESS_TOKEN_FILEPATH));
            fclose(filep);
            return mapAccessToken;
        }
        if (strlen(buf) > 0 && buf[strlen(buf)-1] == '\n') {
            buf[strlen(buf)-1] = '\0';
        }
        mapAccessToken = QString(buf);

        fclose(filep);

        return mapAccessToken;
    }
};

#endif // FILE_OPERATION_H
