﻿#include "windows/performance.hpp"

#include <format>

#include <windows.h>
#undef min
#undef max
#include <psapi.h>

#include "GLFW/glfw3.h"
#include "imgui/imgui.h"
#include "Maths/calc.hpp"

using namespace XnorEditor;

Performance::Performance()
{
    frameRateArray.resize(50);
    memoryArray.resize(50);
}

void Performance::Update(const double currentTime)
{
    if (Calc::OnInterval(static_cast<float>(currentTime), static_cast<float>(totalTime), UpdateInterval))
    {
        const double deltaTime = currentTime - totalTime;
        
        lastFps = static_cast<float>(1.0 / deltaTime);
        frameRateArray[arrayIndex] = lastFps;
        highestArrayFps = std::max(*std::ranges::max_element(frameRateArray), MinHighestArrayFps);

        PROCESS_MEMORY_COUNTERS memory;
        GetProcessMemoryInfo(GetCurrentProcess(), &memory, sizeof(memory));
        
        lastMemory = static_cast<float>(memory.WorkingSetSize) / 0x100000;
        memoryArray[arrayIndex] = lastMemory;
        highestArrayMemory = std::max(*std::ranges::max_element(memoryArray), MinHighestArrayMemory);

        arrayIndex = static_cast<int32_t>((arrayIndex + 1) % frameRateArray.size());
        if (totalSamples < MaxSamples)
            totalSamples++;
    }
    
    totalTime = currentTime;
}

void Performance::Display()
{
    ImGui::Begin("Performance Summary");

    std::string format = std::format("FPS: {:.0f}", lastFps);
    ImGui::PlotLines("##fps", frameRateArray.data(), static_cast<int32_t>(std::min(totalSamples, frameRateArray.size())), arrayIndex,
        format.c_str(), 0, highestArrayFps, ImVec2(ImGui::GetContentRegionAvail().x, 50));

    format = std::format("Memory: {:.2f}MB", lastMemory);
    ImGui::PlotLines("##memory", memoryArray.data(), static_cast<int32_t>(std::min(totalSamples, memoryArray.size())), arrayIndex,
        format.c_str(), 0, highestArrayMemory, ImVec2(ImGui::GetContentRegionAvail().x, 50));

    ImGui::End();
}