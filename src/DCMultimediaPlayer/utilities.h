#ifndef UTILITIES_H // OK
#define UTILITIES_H

#include <QString>
#include <QIcon>

/**
 * @brief The FileType enum
 */
enum FileType {
    Music, Video, Other
};

/**
 * @brief getFilenameFromPath
 * @param mPath
 * @param separator
 * @return filename
 */
QString getFilenameFromPath(const QString &mPath,
    const QString &separator);

/**
 * @brief getFileType
 * @param fileExtension
 * @return file type
 */
FileType getFileType(const QString &fileExtension);

/**
 * @brief getFileExtension
 * @param mFilepath
 * @return file extension
 */
QString getFileExtension(const QString &mFilepath);

/**
 * @brief getIconType
 * @param fileType
 * @return icon
 */
QIcon getIconType(const FileType fileType);

/**
 * @brief reverseString
 * @param str
 * @return string
 */
QString reverseString(const QString &str);

/**
 * @brief getPathSeparator
 * @param path
 * @return separator string
 */
static inline QString getPathSeparator(const QString &path) {
    return path.contains("/") ? "/" : "\\";
}

#endif // UTILITIES_H
