#include <iostream>
#include <filesystem>
#include "Downloader.h"
#include "UserProgressRecorder.h"

const std::string API_ENDPOINT = "https://api.mangadex.org";
const std::string TEMP_DIR = "temp";
const std::string OUTPUT_DIR = "manga";
const std::string PROGRESS_FILE = "progress.csv";


bool imagesToPDF(const std::string &input_dir, const std::string &output_dir, const std::string &output_name) {
    // just call img2pdf on the input directory. EZPZ
    std::filesystem::create_directories(output_dir);

    std::cout << output_dir << std::endl;
    std::cout << output_name << std::endl;
    std::cout << "Creating PDF..." << std::endl;
    std::string command = "img2pdf --rotation=ifvalid '" + input_dir + "'/* -o '" + output_dir + "/" + output_name +
                          //                          ".pdf' 2>/dev/null";
                          ".pdf'";
    // Some files have invalid rotation data. There is no way for me to fix this, so I have to suppress the error.

    std::cout << command << std::endl;
    try {
        std::system(command.c_str());
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
        return false;
    }
    return true;
}


std::vector<std::string> splitString(const std::string &str) {
    std::vector<std::string> words;
    std::istringstream iss(str);
    std::string word;
    while (iss >> word) {
        words.push_back(word);
    }
    return words;
}


void welcomeUser() {
    std::cout << "Welcome to MangaMania!" << std::endl;
    std::cout << "This app lets you download and read your favorite manga, and keep track of your progress."
              << std::endl;
    std::cout << "Enjoy your reading!" << std::endl;
}

Manga getManga(Downloader &downloader) {
    // Ask the user to enter the name of the manga they want to download.
    std::string mangaName;
    std::cout << "Enter the name of the manga you want to download: ";
    std::cin.ignore(); // Clear input buffer
    std::getline(std::cin, mangaName);

    // Replace spaces with plus signs.
    std::replace(mangaName.begin(), mangaName.end(), ' ', '+');

    std::vector<std::string> includeTagsVector;
    std::vector<std::string> excludeTagsVector;

    std::string searchByTag;
    std::cout << "Do you want to search by tag? (y/n): ";
    std::cin >> searchByTag;

    // If they do, take input for include tags and exclude tags.
    if (searchByTag == "y") {
        std::string includeTags;
        std::string excludeTags;

        std::cout << "Enter the tags you want to include (separated by spaces): " << std::endl;
        std::cin >> includeTags;
        std::cout << "Enter the tags you want to exclude (separated by spaces): " << std::endl;
        std::cin >> excludeTags;

        // Make every tag lowercase.
        std::transform(includeTags.begin(), includeTags.end(), includeTags.begin(), ::tolower);
        std::transform(excludeTags.begin(), excludeTags.end(), excludeTags.begin(), ::tolower);


        includeTagsVector = splitString(includeTags);
        excludeTagsVector = splitString(excludeTags);

        // Get the manga from the API.

    }
    std::vector<Manga> manga_list = downloader.searchManga(mangaName, includeTagsVector, excludeTagsVector);

    // Early return if the manga list is empty.
    if (manga_list.empty()) {
        std::cout << "No manga found." << std::endl;
        return {};
    }


    // Define colour escape sequences.
    const std::string GREEN = "\033[32m";
    const std::string RESET = "\033[0m";

    for (int i = 0; i < manga_list.size(); i++) {
        std::cout << GREEN << i + 1 << ". " << manga_list[i].getTitle() << RESET << GREEN << std::endl;
        std::cout << RESET << "" << manga_list[i].getDescription() << std::endl;
    }

    // Ask the user to select a manga.
    int choice;
    std::cout << "Enter the number of the manga you want to download: ";
    std::cin >> choice;

    return manga_list[choice - 1];
}

Manga::Chapter getChapter(Downloader &downloader, Manga &manga) {
    // Search for the chapter
    std::vector<Manga::Chapter> chapter_list = downloader.searchChapter(manga.getUuid());

// Early return if the chapter list is empty.
    if (chapter_list.empty()) {
        std::cout << "No chapters found. This manga will not be downloaded or saved." << std::endl;
        return {};
    }

    for (int i = 0; i < chapter_list.size(); i++) {
        std::cout << i + 1 << ". " << chapter_list[i].title << std::endl;
    }
    // Ask the user to select a chapter.
    int choice;
    std::cout << "Enter the number of the chapter you want to download: ";
    std::cin >> choice;

    return chapter_list[choice - 1];
}

void downloadManga(Downloader &downloader, UserProgressRecorder &progressRecorder) {
    Manga manga_choice = getManga(downloader);

    // Check if the manga_choice is empty
    if (manga_choice.getUuid().empty()) {
        return;
    }

    Manga::Chapter chapter_choice = getChapter(downloader, manga_choice);


    std::cout << "Manga: " << manga_choice.getTitle() << std::endl;
    std::cout << "Chapter: " << chapter_choice.title << std::endl;

    // Download the images.
    std::cout << "Downloading images..." << std::endl;
    downloader.downloadChapter(chapter_choice, TEMP_DIR);
    // Convert the images to a PDF.
    std::cout << "Converting images to PDF..." << std::endl;
    std::string saveDirectory = OUTPUT_DIR + "/" + manga_choice.getTitle();
    imagesToPDF(TEMP_DIR, saveDirectory, chapter_choice.title);

    // Ask the user if they want to add this to their progress.
    std::string addToProgress;
    std::cout << "Do you want to add this to your progress? (y/n): ";
    std::cin >> addToProgress;

    if (addToProgress == "y") {
        // Add the chapter to the user's progress.
        progressRecorder.addProgress(manga_choice, chapter_choice);
    }


}

    void manageMangaProgress(Downloader &downloader, UserProgressRecorder &progressRecorder) {
        std::cout << "Manage manga progress" << std::endl;
        std::cout << "1. View progress" << std::endl;
        std::cout << "2. Add progress" << std::endl;
        std::cout << "3. Remove progress" << std::endl;

        int choice;
        std::cin >> choice;

        if (choice == 1) {
            // View progress
            progressRecorder.viewAllProgress();
        }

        if (choice == 2) {
            // Add progress
            Manga manga_choice = getManga(downloader);

            // Check if the manga_choice is empty
            if (manga_choice.getUuid().empty()) {
                return;
            }
            Manga::Chapter chapter_choice = getChapter(downloader, manga_choice);

            if (chapter_choice.uuid.empty()) {
                return;
            }

            progressRecorder.addProgress(manga_choice, chapter_choice);
        }

        if (choice == 3) {
            std::cout << "Enter the UUID of the manga you want to remove progress for: ";
            std::string mangaUuid;
            std::cin >> mangaUuid;

            progressRecorder.removeProgress(mangaUuid);
        }
    }


int main() {
    std::filesystem::remove_all(TEMP_DIR);
    Downloader downloader(API_ENDPOINT);
    UserProgressRecorder progressRecorder(PROGRESS_FILE);

    welcomeUser();

    int choice;
    do {
        std::cout << "Please choose an option:" << std::endl;
        std::cout << "1. Download manga" << std::endl;
        std::cout << "2. Manage library" << std::endl;
        std::cout << "3. Exit" << std::endl;
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cout << "Invalid input. Please try again." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else if (choice < 1 || choice > 3) {
            std::cout << "Invalid input. Please try again." << std::endl;
        } else {
            switch (choice) {
                case 1:
                    downloadManga(downloader, progressRecorder);
                    break;
                case 2:
                    manageMangaProgress(downloader, progressRecorder);
                    break;
                case 3:
                    std::cout << "Exiting..." << std::endl;
                    break;
            }
        }
    } while (choice != 3);


    std::filesystem::remove_all(TEMP_DIR);    // clean up

    return 0;
}
