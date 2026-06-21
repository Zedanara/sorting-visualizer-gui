#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <memory>
#include <random>
#include <numeric>
#include <algorithm>

#include "sv/core/Theme.hpp"
#include "sv/core/Visualizer.hpp"
#include "sv/core/Localization.hpp"
#include "sv/utils/AlgorithmInfo.hpp"
#include "sv/sorting/BubbleSort.hpp"
#include "sv/sorting/InsertionSort.hpp"
#include "sv/sorting/MergeSort.hpp"
#include "sv/sorting/QuickSort.hpp"
#include "sv/sorting/HeapSort.hpp"
#include "sv/sorting/CountingSort.hpp"
#include "sv/math_algs/BinarySearch.hpp"
#include "sv/math_algs/SieveOfEratosthenes.hpp"
#include "sv/database/HistoryDatabase.hpp"

using namespace sv::core;

void generateData(std::vector<int>& data, int size, int presetType) {
    data.resize(size);
    if (presetType == 0) { // Losowe (Random)
        std::mt19937 rng(std::random_device{}());
        std::uniform_int_distribution<int> dist(10, 100);
        for (int& x : data) x = dist(rng);
    } else if (presetType == 1) { // Posortowane (Sorted)
        std::iota(data.begin(), data.end(), 10);
    } else if (presetType == 2) { // Odwrotnie (Reversed)
        std::iota(data.begin(), data.end(), 10);
        std::reverse(data.begin(), data.end());
    } else if (presetType == 3) { // Z duplikatami (Duplicates)
        std::mt19937 rng(std::random_device{}());
        std::uniform_int_distribution<int> dist(10, 20); // Mały zakres = dużo duplikatów
        for (int& x : data) x = dist(rng);
    }
}

int main() {
    if (!glfwInit()) {
        std::cerr << "Blad inicjalizacji GLFW!\n";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    GLFWwindow* window = glfwCreateWindow(1280, 720, "Sorting Visualizer", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); 

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.IniFilename = nullptr; 
    
    sv::core::applyDarkTheme();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    // --- Inicjalizacja Danych i Bazy ---
    std::vector<int> testData;
    int currentArraySize = 15;
    generateData(testData, currentArraySize, 0); 
    
    sv::database::HistoryDatabase historyDb("history.txt");
    bool showStartupPopup = historyDb.load();
    bool popupOpened = false;
    bool wasRecorded = false; 

    std::unique_ptr<sv::sorting::ISortAlgorithm> currentAlgorithm = std::make_unique<sv::sorting::BubbleSort>();
    currentAlgorithm->init(testData);

    bool isSorting = false;
    double lastStepTime = 0.0;
    int speedDelayMs = 50;

    const char* algorithmNames[] = { 
        "Bubble Sort", "Insertion Sort", "Merge Sort", 
        "Quick Sort", "Heap Sort", "Counting Sort",
        "Binary Search", "Sito Eratostenesa"
    };
    static int currentAlgoIndex = 0;

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // --- Logika aktualizacji kroków i zapisu do bazy ---
        if (isSorting && !currentAlgorithm->isFinished()) {
            double currentTime = ImGui::GetTime();
            if (currentTime - lastStepTime >= (speedDelayMs / 1000.0)) {
                currentAlgorithm->step();
                lastStepTime = currentTime;
            }
        } else if (isSorting && currentAlgorithm->isFinished()) {
            isSorting = false;
            if (!wasRecorded) {
                historyDb.addEntry(currentAlgorithm->getName(), testData.size());
                wasRecorded = true;
            }
        }

        // --- Popup startowy (Modal) ---
        if (showStartupPopup && !popupOpened) {
            ImGui::OpenPopup("Zapisy");
            popupOpened = true;
        }

        if (ImGui::BeginPopupModal("Zapisy", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
            ImGui::Text("W pliku history.txt znajduja sie wczesniejsze zapisy.");
            ImGui::Separator();
            if (ImGui::Button("Kontynuuj", ImVec2(120, 0))) {
                ImGui::CloseCurrentPopup();
                showStartupPopup = false;
            }
            ImGui::SameLine();
            if (ImGui::Button("Wyczysc", ImVec2(120, 0))) {
                historyDb.clearAll();
                ImGui::CloseCurrentPopup();
                showStartupPopup = false;
            }
            ImGui::EndPopup();
        }

        // =========================================================
        // 1. GŁÓWNE OKNO WIZUALIZACJI
        // =========================================================
        ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_FirstUseEver);
        ImGui::SetNextWindowSize(ImVec2(850, 690), ImGuiCond_FirstUseEver);
        ImGui::Begin(Localization::tr("window_main").c_str(), nullptr, ImGuiWindowFlags_NoCollapse);

        // --- Zmiana Języka ---
        if (ImGui::Button(Localization::getLanguage() == Language::PL ? "Jezzyk: Polski (Zmien na EN)" : "Language: English (Change to PL)")) {
            Localization::setLanguage(Localization::getLanguage() == Language::PL ? Language::EN : Language::PL);
        }
        ImGui::Separator();
        ImGui::Spacing();

        // --- Wybór Algorytmu ---
        ImGui::SetNextItemWidth(250);
        if (ImGui::Combo(Localization::tr("combo_algo").c_str(), &currentAlgoIndex, algorithmNames, IM_ARRAYSIZE(algorithmNames))) {
            if (currentAlgoIndex == 0) currentAlgorithm = std::make_unique<sv::sorting::BubbleSort>();
            else if (currentAlgoIndex == 1) currentAlgorithm = std::make_unique<sv::sorting::InsertionSort>();
            else if (currentAlgoIndex == 2) currentAlgorithm = std::make_unique<sv::sorting::MergeSort>();
            else if (currentAlgoIndex == 3) currentAlgorithm = std::make_unique<sv::sorting::QuickSort>();
            else if (currentAlgoIndex == 4) currentAlgorithm = std::make_unique<sv::sorting::HeapSort>();
            else if (currentAlgoIndex == 5) currentAlgorithm = std::make_unique<sv::sorting::CountingSort>();
            else if (currentAlgoIndex == 6) currentAlgorithm = std::make_unique<sv::math_algs::BinarySearch>();
            else if (currentAlgoIndex == 7) currentAlgorithm = std::make_unique<sv::math_algs::SieveOfEratosthenes>();
            
            currentAlgorithm->init(testData);
            isSorting = false;
            wasRecorded = false; 
        }

        // KONTROLKI SPECJALNE (Binary Search / Sieve)
        if (auto bs = dynamic_cast<sv::math_algs::BinarySearch*>(currentAlgorithm.get())) {
            int target = bs->getTarget();
            ImGui::SetNextItemWidth(150);
            if (ImGui::InputInt(Localization::tr("input_target").c_str(), &target)) {
                bs->setTarget(target);
                bs->init(testData); 
                isSorting = false;
                wasRecorded = false;
            }
            if (bs->isFinished()) {
                if (bs->isFound()) ImGui::TextColored(ImVec4(0, 1, 0, 1), "%s %d!", Localization::tr("msg_found").c_str(), bs->getHighlightedIndices().first);
                else ImGui::TextColored(ImVec4(1, 0, 0, 1), "%s", Localization::tr("msg_not_found").c_str());
            }
        }
        else if (auto sieve = dynamic_cast<sv::math_algs::SieveOfEratosthenes*>(currentAlgorithm.get())) {
            int limit = sieve->getLimit();
            ImGui::SetNextItemWidth(150);
            if (ImGui::InputInt(Localization::tr("input_limit").c_str(), &limit)) {
                if (limit < 2) limit = 2;
                if (limit > 500) limit = 500; 
                sieve->setLimit(limit);
                sieve->init(testData);
                isSorting = false;
                wasRecorded = false;
            }
        }
        ImGui::Spacing();

        // --- Ustawienia Wizualizacji (Suwaki) ---
        ImGui::SetNextItemWidth(250);
        ImGui::SliderInt(Localization::getLanguage() == Language::PL ? "Predkosc animacji (ms)" : "Animation Speed (ms)", &speedDelayMs, 1, 500);
        
        ImGui::SetNextItemWidth(250);
        if (ImGui::SliderInt(Localization::getLanguage() == Language::PL ? "Rozmiar tablicy" : "Array Size", &currentArraySize, 5, 100)) {
            generateData(testData, currentArraySize, 0);
            currentAlgorithm->init(testData);
            isSorting = false;
            wasRecorded = false;
        }
        ImGui::Spacing();

        // --- Presety Danych ---
        ImGui::Text("%s", Localization::getLanguage() == Language::PL ? "Szybkie generowanie danych:" : "Data presets:");
        if (ImGui::Button(Localization::getLanguage() == Language::PL ? "Losowe" : "Random")) {
            generateData(testData, currentArraySize, 0);
            currentAlgorithm->init(testData);
            isSorting = false;
            wasRecorded = false;
        }
        ImGui::SameLine();
        if (ImGui::Button(Localization::getLanguage() == Language::PL ? "Posortowane" : "Sorted")) {
            generateData(testData, currentArraySize, 1);
            currentAlgorithm->init(testData);
            isSorting = false;
            wasRecorded = false;
        }
        ImGui::SameLine();
        if (ImGui::Button(Localization::getLanguage() == Language::PL ? "Odwrotnie" : "Reversed")) {
            generateData(testData, currentArraySize, 2);
            currentAlgorithm->init(testData);
            isSorting = false;
            wasRecorded = false;
        }
        ImGui::SameLine();
        if (ImGui::Button(Localization::getLanguage() == Language::PL ? "Z duplikatami" : "Duplicates")) {
            generateData(testData, currentArraySize, 3);
            currentAlgorithm->init(testData);
            isSorting = false;
            wasRecorded = false;
        }
        
        ImGui::Separator();
        ImGui::Spacing();

        // --- Sterowanie Głównym Cyklem (Start/Pauza) ---
        if (ImGui::Button(Localization::tr("btn_start").c_str(), ImVec2(120, 0))) {
            isSorting = true;
            if (currentAlgorithm->isFinished()) {
                currentAlgorithm->init(testData);
                wasRecorded = false;
            }
            lastStepTime = ImGui::GetTime();
        }
        ImGui::SameLine();
        if (ImGui::Button(Localization::tr("btn_pause").c_str(), ImVec2(100, 0))) {
            isSorting = false;
        }
        ImGui::SameLine();
        if (ImGui::Button(Localization::tr("btn_reset").c_str(), ImVec2(100, 0))) {
            isSorting = false;
            currentAlgorithm->init(testData);
            wasRecorded = false;
        }
        ImGui::Spacing();

        // --- Statystyki ---
        ImGui::Text("%s: %s | %s: %s", 
            Localization::tr("lbl_active").c_str(), currentAlgorithm->getName().c_str(), 
            Localization::tr("lbl_complexity").c_str(), currentAlgorithm->getComplexityAverage().c_str());
            
        ImGui::Text("%s: %d | %s: %d", 
            Localization::tr("lbl_comparisons").c_str(), currentAlgorithm->getComparisonsCount(), 
            Localization::tr("lbl_swaps").c_str(), currentAlgorithm->getSwapsCount());

        ImGui::Separator();

        // --- Rysowanie ---
        if (currentAlgoIndex == 7) {
            sv::core::Visualizer::drawGrid(currentAlgorithm->getData(), currentAlgorithm->getHighlightedIndices());
        } else {
            sv::core::Visualizer::drawBars(currentAlgorithm->getData(), currentAlgorithm->getHighlightedIndices());
        }
        ImGui::End();

        // =========================================================
        // 2. OKNO BAZY DANYCH (Góra Prawa)
        // =========================================================
        ImGui::SetNextWindowPos(ImVec2(870, 10), ImGuiCond_FirstUseEver);
        ImGui::SetNextWindowSize(ImVec2(390, 300), ImGuiCond_FirstUseEver);
        ImGui::Begin(Localization::tr("window_db").c_str(), nullptr, ImGuiWindowFlags_NoCollapse);

        if (ImGui::Button(Localization::tr("btn_del_last").c_str())) historyDb.removeLast();
        ImGui::SameLine();
        if (ImGui::Button(Localization::tr("btn_clear_all").c_str())) historyDb.clearAll();

        ImGui::Separator();

        if (ImGui::BeginTable("TabelaHistorii", 3, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg | ImGuiTableFlags_ScrollY)) {
            ImGui::TableSetupColumn("ID", ImGuiTableColumnFlags_WidthFixed, 20.0f);
            ImGui::TableSetupColumn(Localization::tr("tbl_algo").c_str());
            ImGui::TableSetupColumn(Localization::tr("tbl_time").c_str());
            ImGui::TableHeadersRow();

            for (const auto& entry : historyDb.getEntries()) {
                ImGui::TableNextRow();
                ImGui::TableNextColumn(); ImGui::Text("%d", entry.index);
                ImGui::TableNextColumn(); ImGui::Text("%s", entry.algorithmName.c_str());
                ImGui::TableNextColumn(); ImGui::Text("%s", entry.timestamp.c_str());
            }
            ImGui::EndTable();
        }
        ImGui::End();

        // =========================================================
        // 3. OKNO TEORII ALGORYTMU (Dół Prawa)
        // =========================================================
        ImGui::SetNextWindowPos(ImVec2(870, 320), ImGuiCond_FirstUseEver);
        ImGui::SetNextWindowSize(ImVec2(390, 380), ImGuiCond_FirstUseEver);
        std::string infoTitle = Localization::getLanguage() == Language::PL ? "Opis Algorytmu" : "Algorithm Details";
        ImGui::Begin(infoTitle.c_str(), nullptr, ImGuiWindowFlags_NoCollapse);

        sv::utils::AlgoDetails details = sv::utils::AlgorithmInfo::getDetails(currentAlgorithm->getName(), Localization::getLanguage());

        ImGui::TextWrapped("%s", details.description.c_str());
        ImGui::Separator();
        
        ImGui::TextColored(ImVec4(0.4f, 1.0f, 0.4f, 1.0f), Localization::getLanguage() == Language::PL ? "Zalety:" : "Pros:");
        ImGui::TextWrapped("%s", details.pros.c_str());
        
        ImGui::TextColored(ImVec4(1.0f, 0.4f, 0.4f, 1.0f), Localization::getLanguage() == Language::PL ? "Wady:" : "Cons:");
        ImGui::TextWrapped("%s", details.cons.c_str());
        
        ImGui::Separator();
        ImGui::TextColored(ImVec4(0.4f, 0.8f, 1.0f, 1.0f), Localization::getLanguage() == Language::PL ? "Najlepszy przypadek:" : "Best Case:");
        ImGui::TextWrapped("%s", details.bestCase.c_str());
        
        ImGui::TextColored(ImVec4(1.0f, 0.8f, 0.4f, 1.0f), Localization::getLanguage() == Language::PL ? "Najgorszy przypadek:" : "Worst Case:");
        ImGui::TextWrapped("%s", details.worstCase.c_str());

        ImGui::Spacing();
        ImGui::Separator();
        
        if (ImGui::CollapsingHeader(Localization::getLanguage() == Language::PL ? "Przyklad krok po kroku" : "Step-by-step example")) {
            ImGui::TextWrapped("%s", details.stepByStepExample.c_str());
        }
        
        if (ImGui::CollapsingHeader(Localization::getLanguage() == Language::PL ? "Kod w C++" : "C++ Code")) {
            ImGui::TextUnformatted(details.cppCode.c_str()); // Używamy Unformatted aby nie popsuć spacji i formatowania
        }

        ImGui::End();

        // ---------------------------------------------------------
        // RENDEROWANIE
        // ---------------------------------------------------------
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}