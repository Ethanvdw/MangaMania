//
// Created by ethan on 09/04/2023.
//

#include "Downloader.h"
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <utility>
#include <curl/curl.h>
#include "Manga.h"

std::map<std::string, std::string> Downloader::tagMap;

Downloader::Downloader(std::string apiEndpoint) : m_apiEndpoint(std::move(apiEndpoint)) {
    // Generate the tag map when the class is instantiated.
    Downloader::tagMap = generateTagMap();
}

// A function that writes the received data to a string.
size_t WriteData(char *ptr, size_t element_size, size_t num_elements, std::string &data) {
    size_t size_of_data = element_size * num_elements;
    data.append(ptr, size_of_data);
    return size_of_data;
}

// A function that makes a request to an API endpoint and returns the response.
std::string Downloader::makeRequest(const std::string &endpoint) {
    // Combine the base API endpoint with the provided endpoint.
    std::string url = m_apiEndpoint + endpoint;

    // std::cout << url << std::endl;

    // Create a string to store the response.
    std::string response;

    // Initialize a curl object.
    CURL *curl = curl_easy_init();
    if (!curl) {
        std::cerr << "Failed to initialize curl" << std::endl;
        return "";
    }

    // Set the options for the curl object.
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteData);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    // Perform the request.
    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        std::cerr << "Failed to make request to " << url << ": " << curl_easy_strerror(res) << std::endl;
        response.clear();
    }

    // Cleanup and return the response.
    curl_easy_cleanup(curl);
    return response;
}

std::vector<Manga> Downloader::searchManga(const std::string &mangaTitle) {
    return {searchManga(mangaTitle, {}, {})};
}

std::vector<Manga> Downloader::searchManga(const std::string &mangaTitle, const std::vector<std::string> &includeTags) {
    return {searchManga(mangaTitle, includeTags, {})};
}

std::vector<Manga> Downloader::searchManga(const std::string &mangaTitle, const std::vector<std::string> &includeTags,
                                           const std::vector<std::string> &excludeTags) {
    std::string requestUrl = "/manga?title=" + mangaTitle;

    // Convert tags to their IDs and add them to the request URL.
    for (const auto &tag: includeTags) {
        requestUrl += "&includedTags[]=" + Downloader::tagMap[tag];
    }
    for (const auto &tag: excludeTags) {
        requestUrl += "&excludedTags[]=" + Downloader::tagMap[tag];
    }


    std::string response = makeRequest(requestUrl);


    // Parse the response as JSON.
    nlohmann::json json_object;
    try {
        json_object = nlohmann::json::parse(response);
    }
    catch (nlohmann::json::parse_error &e) {
        std::cerr << "json parse error: " << e.what() << std::endl;
        return {};
    }

    // Return a vector of Manga objects.
    std::vector<Manga> mangaList;
    for (auto &element: json_object["data"]) {

        Manga manga;

        std::string title;


        try {
            title = element["attributes"]["title"]["en"];
        }
        catch (nlohmann::json::type_error &e) {
            title = "No description available.";
        }

        manga.setTitle(title);


        // You'd hope this would actually keep it to just english, but some manga uploaders clearly can't read.
        // See e82504346f6-44f6-9436-e33c4fc6aece for an example.
//        std::string description = element["attributes"]["description"]["en"];

        // Try to get the english description. If it doesn't exist, say "No description available."
        std::string description;
        try {
            description = element["attributes"]["description"]["en"];
        }
        catch (nlohmann::json::type_error &e) {
            description = "No description available.";
        }

        std::replace(description.begin(), description.end(), '\n', ' ');
        manga.setDescription(description);
        manga.setUuid(element["id"]);

        mangaList.push_back(manga);
    }
    return mangaList;
}

std::map<std::string, std::string> Downloader::generateTagMap() {
    std::string response = makeRequest("/manga/tag");

    // Parse the response as JSON.
    nlohmann::json json_object;
    try {
        json_object = nlohmann::json::parse(response);
    }
    catch (nlohmann::json::parse_error &e) {
        std::cerr << "json parse error: " << e.what() << std::endl;
        return {};
    }

    // Return a map of tag names to tag IDs.
    std::map<std::string, std::string> tagMap;
    for (auto &element: json_object["data"]) {
        std::string tag_name = element["attributes"]["name"]["en"];
        std::transform(tag_name.begin(), tag_name.end(), tag_name.begin(), [](unsigned char c){ return std::tolower(c); });
        tagMap[tag_name] = element["id"];
    }

    return tagMap;
}

std::tuple<std::string, std::string, std::vector<std::string>> Downloader::getImageLinks(Manga::Chapter &chapter){
    std::vector<std::string> imageNames;
    std::string response = makeRequest("/at-home/server/" + chapter.uuid);

    nlohmann::json json_object = nlohmann::json::parse(response);

    std::string server, hash;

    try {
        server = json_object["baseUrl"];
        hash = json_object["chapter"]["hash"];
    } catch (const std::exception& e) {
        std::cout << "Sorry! This chapter is unavailable through Mangadex. Try something else" << std::endl;
        return {};
    }


    for (auto &element: json_object["chapter"]["data"]){
        imageNames.push_back(element);
    }

    return {
        server,
        hash,
        imageNames
    };


};


bool Downloader::downloadChapter(Manga::Chapter &chapter, const std::string &directory) {
    // Check if the directory exists and delete it if it does.
    if (std::filesystem::exists(directory)) {
        std::filesystem::remove_all(directory);
    }


    // Make the directory
    std::filesystem::create_directories(directory);



    // Call downloadImage for each image in the chapter.
    auto [server, hash, imageNames] = getImageLinks(chapter);

    // If no images were found, return false.
    if (imageNames.empty()) {
        std::cout << "No images found for chapter " << chapter.title << std::endl;
        return false;
    }


    bool success = true;
    int imageCount = 1;
    for (const auto& imageName : imageNames) {
        std::string url = server + "/data/" + hash + "/" + imageName;
        std::ostringstream ss;
        ss << std::setw(3) << std::setfill('0') << imageCount;
        std::string filename = directory + "/" + ss.str() + ".jpg";
        success = downloadImage(url, filename) && success;
        imageCount++;
    }

    return success;
}

bool Downloader::downloadImage(const std::string &url, const std::string &filename) {

    // initialize curl
    CURL *curl = curl_easy_init();
    if (!curl) {
        // failed to initialize curl
        return false;
    }

    // set the URL to download from
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

    // open the file for writing
    FILE *fp = fopen(filename.c_str(), "wb");
    if (!fp) {
        // failed to open file for writing
        curl_easy_cleanup(curl);
        return false;
    }

    // set the file handle for curl to write to
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);

    // perform the download
    CURLcode res = curl_easy_perform(curl);

    // cleanup
    curl_easy_cleanup(curl);
    fclose(fp);

    // check if download was successful
    if (res != CURLE_OK) {
        // failed to download image
        return false;
    }

    return true;
}

std::vector<Manga::Chapter> Downloader::searchChapter(const std::string &mangaUuid) {
    std::string offset = "0";
    std::vector<Manga::Chapter> chapters;

    // The api has a limit of 100 chapters per request,
    // so we make multiple requests until we get less than 100 chapters in a request.
    while (true) {
        // Using stringstreams to avoid making a load of temporary strings.
        std::stringstream url;
        url << "/manga/" << mangaUuid << "/feed?translatedLanguage[]=en&limit=100&order[chapter]=asc&offset=" << offset;
        std::string requestUrl = url.str();

        std::string response = makeRequest(requestUrl);

        // Parse the response as JSON.
        nlohmann::json json_object;
        try {
            json_object = nlohmann::json::parse(response);
        }
        catch (nlohmann::json::parse_error &e) {
            std::cerr << "json parse error: " << e.what() << std::endl;
            return {};
        }

        // Add the chapters to the vector.
        for (auto &element: json_object["data"]) {
            Manga::Chapter chapter;
            chapter.uuid = element["id"];
            chapter.title = element["attributes"]["title"].is_null() ? "" : element["attributes"]["title"];
            chapter.chapter = element["attributes"]["chapter"].is_null() ? "" : element["attributes"]["chapter"];
            chapter.date = element["attributes"]["publishAt"].is_null() ? "" : element["attributes"]["publishAt"];
            chapter.volume = element["attributes"]["volume"].is_null() ? "" : element["attributes"]["volume"];
            chapter.pageCount = element["attributes"]["chapter"].is_null() ? "" : element["attributes"]["chapter"];


            // Add the chapter to the vector.
            chapters.push_back(chapter);
        }
        // If the response has less than 100 elements, we've reached the end.
        if (json_object["data"].size() < 100) {
            break;
        }

        // Increase the offset.
        offset = std::to_string(std::stoi(offset) + 100);
    }

    // Check if the vector is empty.
    if (chapters.empty()) {
        return {};
    }

    std::cout << "Found " << chapters.size() << " chapters." << std::endl;
    return chapters;
}
