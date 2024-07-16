#include "utils.h"

#include <QRegularExpression>
#include <QStack>
#include <QFileInfoList>
#include <QStringList>

#include <dirent.h>

bool br_utils::os::rename(
        QString &root,
        const QString &oldName,
        const QString &newName
) {
    return QDir(root).rename(
            oldName,
            newName
    );
}

bool br_utils::os::rename(
        QString &absPath,
        const QString &newName
) {
    QFileInfo info(absPath);
    return info.dir().rename(
            info.fileName(),
            newName
    );
}

bool br_utils::os::rename(
        QFileInfo &file,
        const QString &newName
) {
    return file.dir().rename(
            file.fileName(),
            newName
    );
}

//void br_utils::os::walk(
//        QDir &root,
//        QStringList &dirs,
//        QStringList &files,
//        bool recursive
//) {
//    QFileInfoList entries = root.entryInfoList();
//
//    for (const QFileInfo &entry: entries) {
//        if (entry.isDir()) {
//            // Ignore the current and parent directories
//            if (entry.fileName() == "." || entry.fileName() == "..") continue;
//
//            dirs.append(entry.fileName());
//            if (recursive) {
//                // Recursively walk the subdirectory
//                QDir subDir(entry.filePath());
//                walk(subDir, dirs, files, recursive);
//            }
//        } else if (entry.isFile()) {
//            files.append(entry.fileName());
//        }
//    }
//}

void br_utils::os::walk(
        QString &top,
        std::function<void(const DirectoryEntry &)> process,
        bool topDown,
        std::function<void(QException)> onError,
        bool followLinks
) {
    QStack<QVariant> stack;
    QStack<bool> isTupleStack;

    stack.push(top);
    isTupleStack.push(false);

    while (!stack.isEmpty()) {
        // assert(stack.size() == isTupleStack.size());

        QVariant topVariant = stack.pop();
        QString currTop = topVariant.toString();

        if (isTupleStack.pop()) {
            QList<QVariant> tuple = topVariant.toList();

            QString dirpath = tuple[0].toString();
            QStringList dirs = tuple[1].toStringList();
            QStringList nondirs = tuple[2].toStringList();

            if (process) {
                process(br_utils::os::DirectoryEntry(dirpath, dirs, nondirs));
            }

            continue;
        }

        QStringList dirs;
        QStringList nonDirs;
        QStringList walkDirs;

        QDir dir(currTop);
        try {
            if (!dir.exists()) throw QException();
            if (!dir.isReadable()) throw QException();
        } catch (QException &e) {
            if (onError) onError(e);
            continue;
        }

        QFileInfoList list = dir.entryInfoList(
                QDir::AllEntries | QDir::NoDotAndDotDot, // Everything but '.' and '..'
                QDir::Name | QDir::DirsFirst // Sort by name, directories first
        );

        bool cont = false;
        for (const QFileInfo &entry: list) {
            try {
                bool isDir = entry.isDir();

                if (isDir) {
                    dirs.append(entry.fileName());
                } else {
                    nonDirs.append(entry.fileName());
                }

                if (!topDown && isDir) {
                    bool walk_into = true;
                    if (!followLinks) {
                        walk_into = !entry.isSymLink();
                    }

                    if (walk_into) {
                        walkDirs.append(entry.filePath());
                    }
                }
            } catch (QException &e) {
                if (onError) onError(e);

                cont = true;
                break;
            }
        }

        if (cont) continue;

        if (topDown) {
            if (process) process(br_utils::os::DirectoryEntry(currTop, dirs, nonDirs));

            // for dirname in reversed(dirs):
            for (const QString &dirName: dirs) {
                // new_path = join(top, dirname)
                QString newPath = dir.filePath(dirName);

                if (followLinks || !QFileInfo(newPath).isSymLink()) {
                    stack.push(newPath);
                    isTupleStack.push(false);
                }
            }
        } else {
            stack.push(QVariantList() << currTop << dirs << nonDirs);
            isTupleStack.push(true);

            for (const QString &walkDir: walkDirs) {
                stack.push(walkDir);
                isTupleStack.push(false);
            }
        }
    }
}

bool br_utils::os::addExtension(
        QString &root,
        QString &filename,
        const QString &ext
) {
    if (filename.endsWith(ext))
        // Do nothing
        return true;
    else if (filename.endsWith('.'))
        // Add extension only
        return br_utils::os::rename(
                root,
                filename,
                filename + ext
        );
    else
        // Add extension with a dot
        return br_utils::os::rename(
                root,
                filename,
                filename + "." + ext
        );
}

QString br_utils::str::replaceByRegex(
        QString &str,
        const QString &pattern,
        const QString &repl
) {
    QRegularExpression re(pattern);
    QString result = str;
    return result.replace(re, repl);
}

QString br_utils::findAndReplace(
        QString &str,
        br_enums::ApplyTo applyTo,
        const QString &find,
        const QString &replace,
        bool regex,
        bool caseSensitive,
        bool firstMatch
) {
    QString prefix = "";
    QString main = "";
    QString suffix = "";

    if (applyTo == br_enums::ApplyTo::Name) {
        main = str.section('.', 0, 0);
        suffix = str.section('.', 1);
    } else if (applyTo == br_enums::ApplyTo::NameAndExtension) {
        main = str;
    } else if (applyTo == br_enums::ApplyTo::Extension) {
        main = str.section('.', 1);
        prefix = str.section('.', 0, 0);
    }

    if (regex) {
        main = br_utils::str::replaceByRegex(main, find, replace);
    } else {
        Qt::CaseSensitivity caseSensitivity = caseSensitive ? Qt::CaseSensitive : Qt::CaseInsensitive;

        if (firstMatch) {
            int index = main.indexOf(find, 0, caseSensitivity);
            if (index != -1)main.replace(index, find.length(), replace);
        } else {
            main.replace(find, replace, caseSensitivity);
        }
    }

    return prefix + main + suffix;
}