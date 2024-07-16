#ifndef BATCNRENAME_RENAME_H
#define BATCNRENAME_RENAME_H

#include <QString>
#include <QDir>
#include <QException>

#include "enums.h"

namespace br_utils {

    QString findAndReplace(
            QString &str,
            br_enums::ApplyTo applyTo,
            const QString &find,
            const QString &replace,
            bool regex,
            bool caseSensitive = false,
            bool firstMatch = false
    );

    namespace os {
        using DirectoryEntry = std::tuple<QString, QStringList, QStringList>;

        /**
         * Rename a file or directory
         *
         * @param root: The root directory
         * @param oldName: The old name of the file or directory
         * @param newName: The new name of the file or directory
         * @return bool: True if the file or directory was renamed successfully, false otherwise
         */
        bool rename(
                QString &root,
                const QString &oldName,
                const QString &newName
        );

        bool rename(
                QString &absPath,
                const QString &newName
        );

        bool rename(
                QFileInfo &file,
                const QString &newName
        );

        /**
         * Directory tree generator.
         * <p>
         * Modified from `os.walk` in Python 3.12.4.
         * See <a href="https://docs.python.org/3/library/os.html#os.walk">os.walk</a> from Python documentation.
         * </p>
         *
         * @param top: The root directory
         */
        void walk(
                QString &top,
                std::function<void(const DirectoryEntry &)> process = nullptr,
                bool topDown = true,
                std::function<void(QException)> onError = nullptr,
                bool followLinks = false
        );

        /**
         * Add an extension to a file name if it does not already have it
         *
         * @param root: The root directory
         * @param filename: The string to add the extension to
         * @param ext: The extension to add
         * @return bool: True if the extension was added successfully, false otherwise
         */
        bool addExtension(
                QString &root,
                QString &filename,
                const QString &ext
        );

    }

    namespace str {

        /**
         * Replace a string in a string by a string
         *
         * @param str: The string to replace in
         * @param from: The string to replace
         * @param to: The string to replace with
         * @return bool: True if the string was replaced successfully, false otherwise
         */
        QString replaceByRegex(
                QString &str,
                const QString &pattern,
                const QString &repl
        );
    }

}


#endif //BATCNRENAME_RENAME_H
