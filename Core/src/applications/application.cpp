﻿#include "applications/application.hpp"

using namespace XnorCore;

Application::Application()
{
    m_ApplicationInstance = this;
    coreInput.InitCallBacks(window);
}