#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

#include "sv/core/Theme.hpp"
#include "sv/core/Visualizer.hpp"
#include "sv/sorting/BubbleSort.hpp"
#include "sv/sorting/InsertionSort.hpp"
#include "sv/sorting/MergeSort.hpp"
#include "sv/sorting/QuickSort.hpp"
#include "sv/sorting/HeapSort.hpp"
#include "sv/sorting/CountingSort.hpp"
#include <memory>

int main() {
    if (!glfwInit()) {
        std::cerr << "Blad inicjalizacji GLFW!\n";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    GLFWwindow* window = glfwCreateWindow(1280, 720, "Wizualizator Algorytmow", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); 

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    
    sv::core::applyDarkTheme();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

// --- Inicjalizacja ---
    std::vector<int> testData = {45, 12, 89, 33, 2, 67, 90, 15, 23, 77, 56, 8, 99, 41, 62};
    
    // Używamy unikalnego wskaźnika do trzymania aktywnego algorytmu
    std::unique_ptr<sv::sorting::ISortAlgorithm> currentAlgorithm = std::make_unique<sv::sorting::BubbleSort>();
    currentAlgorithm->init(testData);

    bool isSorting = false;
    double lastStepTime = 0.0;
    const double stepDelay = 0.05;

// Lista dostępnych algorytmów do menu
const char* algorithmNames[] = { 
            "Bubble Sort", "Insertion Sort", "Merge Sort", 
            "Quick Sort", "Heap Sort", "Counting Sort" 
        };
        static int currentAlgoIndex = 0;

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // --- Logika aktualizacji kroków ---
        if (isSorting && !currentAlgorithm->isFinished()) {
            double currentTime = ImGui::GetTime();
            if (currentTime - lastStepTime >= stepDelay) {
                currentAlgorithm->step();
                lastStepTime = currentTime;
            }
        } else if (currentAlgorithm->isFinished()) {
            isSorting = false;
        }

        // --- Interfejs użytkownika ---
        ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_FirstUseEver);
        ImGui::SetNextWindowSize(ImVec2(1000, 600), ImGuiCond_FirstUseEver);
        ImGui::Begin("Panel Wizualizacji", nullptr, ImGuiWindowFlags_NoCollapse);

        // Wybór algorytmu
ImGui::SetNextItemWidth(200);
        if (ImGui::Combo("Wybierz algorytm", &currentAlgoIndex, algorithmNames, IM_ARRAYSIZE(algorithmNames))) {
            if (currentAlgoIndex == 0) {
                currentAlgorithm = std::make_unique<sv::sorting::BubbleSort>();
            } else if (currentAlgoIndex == 1) {
                currentAlgorithm = std::make_unique<sv::sorting::InsertionSort>();
            } else if (currentAlgoIndex == 2) {
                currentAlgorithm = std::make_unique<sv::sorting::MergeSort>();
            } else if (currentAlgoIndex == 3) {
                currentAlgorithm = std::make_unique<sv::sorting::QuickSort>();
            } else if (currentAlgoIndex == 4) {
                currentAlgorithm = std::make_unique<sv::sorting::HeapSort>();
            } else if (currentAlgoIndex == 5) {
                currentAlgorithm = std::make_unique<sv::sorting::CountingSort>();
            }
            currentAlgorithm->init(testData);
            isSorting = false;
        }

        ImGui::Separator();

        // Panel sterowania
        if (ImGui::Button("Start / Wznow")) {
            isSorting = true;
            lastStepTime = ImGui::GetTime();
        }
        ImGui::SameLine();
        if (ImGui::Button("Pauza")) {
            isSorting = false;
        }
        ImGui::SameLine();
        if (ImGui::Button("Reset")) {
            isSorting = false;
            currentAlgorithm->init(testData);
        }

        ImGui::Text("Aktywny: %s | Zlozonosc (Srednia): %s", 
            currentAlgorithm->getName().c_str(),
            currentAlgorithm->getComplexityAverage().c_str()
        );
        ImGui::Text("Porownania: %d | Zamiany: %d", 
            currentAlgorithm->getComparisonsCount(), 
            currentAlgorithm->getSwapsCount()
        );

        ImGui::Separator();

        // Rysowanie
        sv::core::Visualizer::drawBars(currentAlgorithm->getData(), currentAlgorithm->getHighlightedIndices());

        ImGui::End();
        // -----------------------------

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