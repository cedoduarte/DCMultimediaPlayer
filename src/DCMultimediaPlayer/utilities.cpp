#include <utilities.h>

QString getFilenameFromPath(const QString &mPath, const QString &separator) {
    QString path = mPath;
    path = reverseString(path);
    path = path.mid(0, path.indexOf(separator));
    return reverseString(path);
}

QString reverseString(const QString &str) {
    QString reverse;
    for (int x = str.size() - 1; x >= 0; --x)
        reverse.append(str.at(x));
    return reverse;
}

QIcon getIconType(const FileType fileType) {
    QString iconfile;
    switch (fileType) {
    case Music:
        iconfile = ":audiofile.png";
        break;
    case Video:
        iconfile = ":videofile.png";
        break;
    case Other:
        iconfile = ":unknown.png";
        break;
    }
    return QIcon(iconfile);
}

FileType getFileType(const QString &fileExtension) {
    QStringList audioExtensions;
    QStringList videoExtensions;
    audioExtensions << "aif" << "AIF"
        << "iff" << "IFF"
        << "m3u" << "M3U"
        << "m4a" << "M4A"
        << "mid" << "MID"
        << "mp3" << "MP3"
        << "mpa" << "MPA"
        << "ra" << "RA"
        << "wav" << "WAV"
        << "wma" << "WMA";
    videoExtensions << "3g2" << "3G2"
        << "3gp" << "3GP"
        << "asf" << "ASF"
        << "asx" << "ASX"
        << "avi" << "AVI"
        << "flv" << "FLV"
        << "mov" << "MOV"
        << "mp4" << "MP4"
        << "mpg" << "MPG"
        << "mpeg" << "MPEG"
        << "rm" << "RM"
        << "wmv" << "WMV"
        << "mkv" << "MKV"
        << "divx" << "DIVX";
    foreach (QString ext, audioExtensions)
        if (fileExtension == ext)
            return Music;
    foreach (QString ext, videoExtensions)
        if (fileExtension == ext)
            return Video;
    return Other;
}

QString getFileExtension(const QString &mFilepath) {
    QString filepath = mFilepath;
    filepath = reverseString(filepath);
    return reverseString(filepath.mid(0, filepath.indexOf(".")));
}
