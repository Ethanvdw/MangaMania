//
// Created by ethan on 09/04/2023.
//

#include "Manga.h"

#include <utility>




// Getters and setters
std::string Manga::getTitle() const {
    return m_title;
}

void Manga::setTitle(std::string title) {
    m_title = std::move(title);
}

std::string Manga::getUuid() const {
    return m_uuid;
}

void Manga::setUuid(std::string uuid) {
    m_uuid = std::move(uuid);
}

std::string Manga::getDescription() const {
    return m_description;
}

void Manga::setDescription(std::string description){
    m_description = std::move(description);
};

Manga::Chapter Manga::getLastChapter() const {
    return m_lastChapter;
}

void Manga::setLastChapter(Chapter lastChapter){
    m_lastChapter = std::move(lastChapter);
};