QT += core gui widgets

CONFIG += c++17
CONFIG += console
CONFIG -= app_bundle

HEADERS += \
    Controller/Controller.h \
    Model/Builders/AudioBuilder.h \
    Model/Builders/EBookBuilder.h \
    Model/Builders/IBuilder.h \
    Model/Builders/ImageBuilder.h \
    Model/Builders/VideoBuilder.h \
    Model/Library/Command/EditCommand.h \
    Model/Library/Command/IAbstractCommand.h \
    Model/Library/Command/InsertCommand.h \
    Model/Library/Command/RemoveCommand.h \
    Model/Library/Library.h \
    Model/Library/Manager.h \
    Model/Library/MediaFactory.h \
    Model/Library/SearchQuery.h \
    Model/Loggers/IConsoleLogger.h \
    Model/Loggers/IFileLogger.h \
    Model/Loggers/IMediaLogger.h \
    Model/Loggers/LogLevel.h \
    Model/Media/AbstractFile.h \
    Model/Media/AbstractMedia.h \
    Model/Media/Audio.h \
    Model/Media/EBook.h \
    Model/Media/Image.h \
    Model/Media/Video.h \
    Model/Utilities/IMediaLength.h \
    Model/Utilities/IMediaResolution.h \
    Model/Visitors/ConcisePrinter.h \
    Model/Visitors/DetailedPrinter.h \
    Model/Visitors/IConstVisitor.h \
    Model/Visitors/IVisitor.h \
    Model/Visitors/MediaEditor.h \
    Model/Visitors/MediaValidator.h \
    Model/Visitors/ScoreVisitor.h \
    Model/Visitors/SearchVisitor.h \
    View/Creator/AudioCreator.h \
    View/Creator/EBookCreator.h \
    View/Creator/ImageCreator.h \
    View/Creator/MediaCreatorFactory.h \
    View/Creator/TypeSelectorWidget.h \
    View/Creator/VideoCreator.h \
    View/Editor/AudioEditor.h \
    View/Editor/EBookEditor.h \
    View/Editor/ImageEditor.h \
    View/Editor/MediaEditorFactory.h \
    View/Editor/VideoEditor.h \
    View/Search/SearchWidget.h \
    View/Viewer/AudioViewer.h \
    View/Viewer/ConciseViewer.h \
    View/Viewer/EBookViewer.h \
    View/Viewer/ImageViewer.h \
    View/Viewer/MediaViewerFactory.h \
    View/Viewer/VideoViewer.h \
    View/Window.h

SOURCES += \
    Controller/Controller.cpp \
    Model/Builders/AudioBuilder.cpp \
    Model/Builders/EBookBuilder.cpp \
    Model/Builders/ImageBuilder.cpp \
    Model/Builders/VideoBuilder.cpp \
    Model/Library/Command/EditCommand.cpp \
    Model/Library/Command/InsertCommand.cpp \
    Model/Library/Command/RemoveCommand.cpp \
    Model/Library/Library.cpp \
    Model/Library/Manager.cpp \
    Model/Library/MediaFactory.cpp \
    Model/Media/AbstractFile.cpp \
    Model/Media/AbstractMedia.cpp \
    Model/Media/Audio.cpp \
    Model/Media/EBook.cpp \
    Model/Media/Image.cpp \
    Model/Media/Video.cpp \
    Model/Visitors/ConcisePrinter.cpp \
    Model/Visitors/DetailedPrinter.cpp \
    Model/Visitors/MediaEditor.cpp \
    Model/Visitors/MediaValidator.cpp \
    Model/Visitors/ScoreVisitor.cpp \
    Model/Visitors/SearchVisitor.cpp \
    View/Creator/AudioCreator.cpp \
    View/Creator/EBookCreator.cpp \
    View/Creator/ImageCreator.cpp \
    View/Creator/MediaCreatorFactory.cpp \
    View/Creator/TypeSelectorWidget.cpp \
    View/Creator/VideoCreator.cpp \
    View/Editor/AudioEditor.cpp \
    View/Editor/EBookEditor.cpp \
    View/Editor/ImageEditor.cpp \
    View/Editor/MediaEditorFactory.cpp \
    View/Editor/VideoEditor.cpp \
    View/Search/SearchWidget.cpp \
    View/Viewer/AudioViewer.cpp \
    View/Viewer/ConciseViewer.cpp \
    View/Viewer/EBookViewer.cpp \
    View/Viewer/ImageViewer.cpp \
    View/Viewer/MediaViewerFactory.cpp \
    View/Viewer/VideoViewer.cpp \
    View/Window.cpp \
    main.cpp

RESOURCES += \
    Resource/Resource.qrc
