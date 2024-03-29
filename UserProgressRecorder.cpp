//
// Created by ethan on 10/04/2023.
//

#include <sstream>
#include <iomanip>
#include <iostream>
#include "UserProgressRecorder.h"
#include "Manga.h"

// Define colour escape sequences.
const std::string GREEN = "\033[32m";
const std::string RESET = "\033[0m";

void printWithBorders(const std::string &mangaUuid,
                      const std::string &mangaTitle,
                      const std::string &chapterUuid,
                      const std::string &chapterTitle,
                      const std::string &timestamp) {
    // Output top border
    std::cout << std::setfill('=') << std::setw(70) << "" << std::endl;
    std::cout << std::setfill(' ');

    // Output fields with green color
    std::cout << std::left << std::setw(15) << "Manga UUID:" << std::setw(30) << mangaUuid << '\n';
    std::cout << std::left << GREEN << std::setw(15) << "Manga Title:" << RESET << GREEN << std::setw(30)
              << mangaTitle << RESET << '\n';
    std::cout << std::left << std::setw(15) << "Chapter UUID:" << std::setw(30) << chapterUuid << '\n';
    std::cout << std::left << GREEN << std::setw(15) << "Chapter Title:" << RESET << GREEN << std::setw(30)
              << chapterTitle << RESET << '\n';
    std::cout << std::left << std::setw(15) << "Timestamp:" << std::setw(30) << timestamp << '\n';

    // Output bottom border
    std::cout << std::setfill('=') << std::setw(70) << "" << std::endl;

    // Reset fill character
    std::cout << std::setfill(' ');
}

UserProgressRecorder::UserProgressRecorder(const std::string &csvPath) {
    this->csvPath = csvPath;

    std::ifstream file(csvPath);
    bool fileExists = file.good();
    file.close();

    csvFile.open(csvPath, std::ios::app);

    if (!fileExists) {
        csvFile << "manga_uuid,manga_name,chapter_uuid,chapter_name,timestamp" << std::endl;
    }
}

UserProgressRecorder::~UserProgressRecorder() {
    if (csvFile.is_open()) {
        csvFile.close();
    }
}

void UserProgressRecorder::addProgress(Manga &manga, Manga::Chapter &chapter) {
    removeProgress(manga.getUuid());

    // Move the file pointer to the end of the file
    csvFile.seekp(0, std::ios::end);

    // Check if the last character in the file is a newline
    bool lastCharIsNewline = false;
    if (csvFile.tellp() > 0) {
        std::ifstream infile(csvPath);
        infile.seekg(-1, std::ios::end);
        char lastChar;
        infile.get(lastChar);
        lastCharIsNewline = (lastChar == '\n');
    }

    // If the last character in the file is not a newline, add a newline character
    if (!lastCharIsNewline) {
        csvFile << std::endl;
    }

    // Append the new content to the file
    csvFile << manga.getUuid() << "," << manga.getTitle() << ","
            << chapter.uuid << "," << chapter.title << ","
            << getCurrentTime() << std::endl;
}


void UserProgressRecorder::removeProgress(const std::string &mangaUUID) {
    std::ifstream inFile(csvPath);
    std::vector<std::string> rows;
    std::string line;
    while (std::getline(inFile, line)) {
        std::istringstream ss(line);
        std::string uuid;
        std::getline(ss, uuid, ',');
        if (uuid != mangaUUID) {
            rows.push_back(line);
        }
    }
    inFile.close();

    std::ofstream outFile(csvPath);
    for (const auto &row: rows) {
        outFile << row << std::endl;
    }
    outFile.close();
}

void UserProgressRecorder::viewAllProgress() {
    std::ifstream file(csvPath);
    std::string line;
    std::string currentMangaUuid;
    std::string currentMangaName;

    if (!file.good()) {
        std::cerr << "Error: could not open file." << std::endl;
        return;
    }

    // Read and discard the first line.
    std::getline(file, line);

    while (std::getline(file, line)) {
        // Split the line into its CSV fields.
        std::stringstream ss(line);
        std::string field;
        std::vector<std::string> fields;
        while (std::getline(ss, field, ',')) {
            fields.push_back(field);
        }

        // Extract the fields.
        std::string mangaUuid = fields[0];
        std::string mangaTitle = fields[1];
        std::string chapterUuid = fields[2];
        std::string chapterTitle = fields[3];
        std::string timestamp = fields[4];

        printWithBorders(mangaUuid, mangaTitle, chapterUuid, chapterTitle, timestamp);

    }
    file.close();
}

std::string UserProgressRecorder::getCurrentTime() {
    std::time_t now = std::time(nullptr);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&now), "%Y-%m-%d %H:%M:%S");
    return ss.str();
}
