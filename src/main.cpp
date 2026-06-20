#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

#include "sv/core/Theme.hpp"
#include "sv/core/Visualizer.hpp"
#include "sv/sorting/BubbleSort.hpp"

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

    // --- Inicjalizacja algorytmu ---
    sv::sorting::BubbleSort bubbleSort;
    
    // Dane testowe (na razie zahardkodowane)
    std::vector<int> testData = {45, 12, 89, 33, 2, 67, 90, 15, 23, 77, 56, 8, 99, 41, 62};
    bubbleSort.init(testData);

    bool isSorting = false;
    double lastStepTime = 0.0;
    const double stepDelay = 0.05; // Opóźnienie między krokami (50ms)

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // --- Logika aktualizacji kroków ---
        if (isSorting && !bubbleSort.isFinished()) {
            double currentTime = ImGui::GetTime();
            if (currentTime - lastStepTime >= stepDelay) {
                bubbleSort.step();
                lastStepTime = currentTime;
            }
        } else if (bubbleSort.isFinished()) {
            isSorting = false;
        }

        // --- Interfejs użytkownika ---
        ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_FirstUseEver);
        ImGui::SetNextWindowSize(ImVec2(1000, 600), ImGuiCond_FirstUseEver);
        ImGui::Begin("Panel Wizualizacji", nullptr, ImGuiWindowFlags_NoCollapse);

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
            bubbleSort.init(testData); // Reset do stanu początkowego
        }

        ImGui::Text("Algorytm: %s | Porownania: %d | Zamiany: %d", 
            bubbleSort.getName().c_str(), 
            bubbleSort.getComparisonsCount(), 
            bubbleSort.getSwapsCount()
        );

        ImGui::Separator();

        // Rysowanie słupków
        sv::core::Visualizer::drawBars(bubbleSort.getData(), bubbleSort.getHighlightedIndices());

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