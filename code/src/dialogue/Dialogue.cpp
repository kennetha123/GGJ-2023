#include "Dialogue/Dialogue.h"

Dialogue::Dialogue(const std::string& filename) 
{
    loadDialogueFromFile(filename);
}

void Dialogue::loadDialogueFromFile(const std::string& filename) 
{
    std::ifstream file(filename);
    if (!file.is_open()) 
    {
        throw std::runtime_error("Unable to open file: " + filename);
    }

    json j;
    try 
    {
        file >> j;
    }
    catch (const json::parse_error& e) 
    {
        throw std::runtime_error("JSON parsing error: " + std::string(e.what()));
    }

    for (auto& [key, value] : j["dialogues"].items()) 
    {
        DialogueNode node;
        node.text = value["text"].get<std::string>();

        for (auto& choice : value["choices"]) 
        {
            node.choices.push_back({
                choice["text"].get<std::string>(),
                choice["next"].get<std::string>()
                });
        }

        dialogues[key] = node;
    }
}

void Dialogue::start() 
{
    currentDialogue = "start";
}

std::string Dialogue::display() 
{
    if (dialogues.find(currentDialogue) != dialogues.end()) 
    {
        return dialogues[currentDialogue].text;
    }
    return "End of dialogue.";
}

void Dialogue::next() 
{
    if (!dialogues[currentDialogue].choices.empty()) 
    {
        currentDialogue = dialogues[currentDialogue].choices[0].next;
    }
}

std::string Dialogue::displayOption(int index) 
{
    if (index >= 0 && index < dialogues[currentDialogue].choices.size()) 
    {
        return dialogues[currentDialogue].choices[index].text;
    }
    return "";
}

void Dialogue::answer(int choiceIndex) 
{
    if (choiceIndex >= 0 && choiceIndex < dialogues[currentDialogue].choices.size()) 
    {
        currentDialogue = dialogues[currentDialogue].choices[choiceIndex].next;
    }
}