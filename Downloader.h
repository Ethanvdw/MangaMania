//
// Created by ethan on 09/04/2023.
//

#ifndef MANGAMANIA_DOWNLOADER_H
#define MANGAMANIA_DOWNLOADER_H

#include <string>
#include <vector>
#include <curl/curl.h>
#include <map>
#include "Manga.h"

class Downloader {
public:
    Downloader(std::string apiEndpoint);
    std::vector<Manga> searchManga(const std::string& mangaTitle);
    std::vector<Manga> searchManga(const std::string& mangaTitle, const std::vector<std::string>& includeTags);
    std::vector<Manga> searchManga(const std::string& mangaTitle, const std::vector<std::string>& includeTags, const std::vector<std::string>& excludeTags);


    static bool downloadImage(const std::string &url, const std::string &filename);

    std::vector<Manga::Chapter> searchChapter(const std::string &mangaUuid);

    bool downloadChapter(Manga::Chapter &chapter, const std::string &directory);

private:
    static std::map<std::string, std::string> tagMap;
    std::string m_apiEndpoint;
    std::string makeRequest(const std::string& endpoint);
    std::map<std::string, std::string> generateTagMap();

    std::tuple<std::string, std::string, std::vector<std::string>> getImageLinks(Manga::Chapter &chapter);

};



#endif //MANGAMANIA_DOWNLOADER_H
