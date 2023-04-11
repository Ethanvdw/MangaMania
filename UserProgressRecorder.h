//
// Created by ethan on 10/04/2023.
//

#ifndef MANGAMANIA_USERPROGRESSRECORDER_H
#define MANGAMANIA_USERPROGRESSRECORDER_H


#include <string>
#include <fstream>
#include <chrono>
#include <vector>
#include "Manga.h"

class UserProgressRecorder {
public:
    UserProgressRecorder(const std::string& csvPath);
    // Destructor
    ~UserProgressRecorder();
    void addProgress(Manga &manga, Manga::Chapter &chapter);
    void removeProgress(const std::string& mangaUUID);
    void viewAllProgress();

private:
    std::string csvPath;
    std::ofstream csvFile;
    std::string getCurrentTime();

};


#endif //MANGAMANIA_USERPROGRESSRECORDER_H
