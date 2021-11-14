#include "../platform.h"
#include "io_window.h"
#include "../../environment.h"
using namespace kengine;

bool Platform::init() {
    Env.io= new IOWindow();
    return true;
}