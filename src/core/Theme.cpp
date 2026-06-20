#include "sv/core/Theme.hpp"
#include "imgui.h"

namespace sv::core {
    void applyDarkTheme() {
        ImGuiStyle& style = ImGui::GetStyle();
        
        // Kolory (ciemny motyw z niebiesko-fioletowym akcentem)
        ImVec4* colors = style.Colors;
        colors[ImGuiCol_WindowBg]       = ImVec4(0.10f, 0.10f, 0.12f, 1.00f);
        colors[ImGuiCol_TitleBg]        = ImVec4(0.08f, 0.08f, 0.09f, 1.00f);
        colors[ImGuiCol_TitleBgActive]  = ImVec4(0.08f, 0.08f, 0.09f, 1.00f);
        colors[ImGuiCol_Button]         = ImVec4(0.15f, 0.30f, 0.60f, 1.00f);
        colors[ImGuiCol_ButtonHovered]  = ImVec4(0.20f, 0.40f, 0.80f, 1.00f);
        colors[ImGuiCol_ButtonActive]   = ImVec4(0.10f, 0.20f, 0.40f, 1.00f);
        colors[ImGuiCol_FrameBg]        = ImVec4(0.15f, 0.15f, 0.17f, 1.00f);
        colors[ImGuiCol_FrameBgHovered] = ImVec4(0.20f, 0.20f, 0.22f, 1.00f);
        colors[ImGuiCol_FrameBgActive]  = ImVec4(0.25f, 0.25f, 0.27f, 1.00f);

        // Zaokrąglenia (nowoczesny wygląd)
        style.WindowRounding = 8.0f;
        style.FrameRounding = 6.0f;
        style.GrabRounding = 6.0f;
        style.PopupRounding = 6.0f;
        style.ScrollbarRounding = 6.0f;
        
        // Odstępy
        style.WindowPadding = ImVec2(12.0f, 12.0f);
        style.ItemSpacing = ImVec2(8.0f, 6.0f);
    }
}