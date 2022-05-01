#include "binding-util.h"
#include "binding-types.h"
#include "sharedstate.h"
#include "eventthread.h"
#include "display.h"
#include "debugwriter.h"

RB_METHOD(getScreenWidth)
{
    return rb_int_new(Display::getScreenWidth());
}

RB_METHOD(getScreenHeight) 
{
    return rb_int_new(Display::getScreenHeight());
}

RB_METHOD(isWayland)
{
    return rb_bool_new(Display::isWayland());
}

RB_METHOD(isX)
{
    return rb_bool_new(Display::isX());
}

void displayBindingInit()
{
    VALUE module = rb_define_module("Display");
    _rb_define_module_function(module, "getScreenWidth", getScreenWidth);
    _rb_define_module_function(module, "getScreenHeight", getScreenHeight);
    _rb_define_module_function(module, "isWayland?", isWayland);
    _rb_define_module_function(module, "isX?", isX);
}