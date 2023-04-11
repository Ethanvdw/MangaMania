//
// Created by ethan on 09/04/2023.
//

#ifndef MANGAMANIA_MANGA_H
#define MANGAMANIA_MANGA_H


#include <string>
#include <optional>

#include <string>

class Manga {
public:
    class Chapter {
    public:
        std::string uuid;
        std::string title;
        std::string volume;
        std::string chapter;
        std::string date;
        std::string pageCount;
    };

    // Constructors
    Manga(){};
    Manga(std::string title, std::string uuid) : m_title(std::move(title)), m_uuid(std::move(uuid)) {};

    // Getters and setters
    std::string getTitle() const;
    void setTitle(std::string title);
    std::string getUuid() const;
    void setUuid(std::string uuid);
    std::string getDescription() const;
    void setDescription(std::string description);
    Chapter getLastChapter() const;
    void setLastChapter(Chapter lastChapter);

private:
    std::string m_title;
    std::string m_uuid;
    std::string m_description;
    Chapter m_lastChapter;
};



#endif //MANGAMANIA_MANGA_H
