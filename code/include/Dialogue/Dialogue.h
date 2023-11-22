#pragma once

#include "json.hpp"
#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>

using json = nlohmann::json;

class Dialogue {
public:
    struct Choice {
        std::string text;
        std::string next;
    };

    struct DialogueNode {
        std::string text;
        std::vector<Choice> choices;
    };

    Dialogue(const std::string& filename);

    void start();
    std::string display();
    void next();

    void option(const std::string& a, const std::string& b, const std::string& c = "", const std::string& d = "");
    std::string displayOption(int index);
    void answer(int choiceIndex);

private:
    void loadDialogueFromFile(const std::string& filename);
    std::unordered_map<std::string, DialogueNode> dialogues;
    std::string currentDialogue;

    // New members for handling options
    std::vector<std::string> currentOptions;
};
