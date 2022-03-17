#include "sharedstate.h"
#include "binding-util.h"
#include "filesystem.h"

RB_METHOD(pathCacheMount) {
    RB_UNUSED_PARAM;
    
    VALUE path, mountpoint, reload;
    rb_scan_args(argc, argv, "12", &path, &mountpoint, &reload);
    SafeStringValue(path);
    if (mountpoint != Qnil) SafeStringValue(mountpoint);
    
    const char *mp = (mountpoint == Qnil) ? 0 : RSTRING_PTR(mountpoint);
    
    try {
        bool rl = true;
        if (reload != Qnil)
            rb_bool_arg(reload, &rl);
        
        shState->fileSystem().addPath(RSTRING_PTR(path), mp, rl);
    } catch (Exception &e) {
        raiseRbExc(e);
    }

    return path;
}

RB_METHOD(pathCacheUnmount) {
    RB_UNUSED_PARAM;
    
    VALUE path, reload;
    rb_scan_args(argc, argv, "11", &path, &reload);
    SafeStringValue(path);
    
    try {
        bool rl = true;
        if (reload != Qnil)
            rb_bool_arg(reload, &rl);
        
        shState->fileSystem().removePath(RSTRING_PTR(path), rl);
    } catch (Exception &e) {
        raiseRbExc(e);
    }
    return path;
}


RB_METHOD(pathCacheReload) {
    RB_UNUSED_PARAM;
    
    shState->fileSystem().reloadPathCache();
    return Qnil;
}

RB_METHOD(pathCacheDesensitize) {
    RB_UNUSED_PARAM;
    
    VALUE filename;
    rb_scan_args(argc, argv, "1", &filename);
    SafeStringValue(filename);
    
    return rb_utf8_str_new_cstr(
                           shState->fileSystem().desensitize(RSTRING_PTR(filename)));
}

void pathCacheBindingInit() {
    VALUE module = rb_define_module("PathCache");
    _rb_define_module_function(module, "mount", pathCacheMount);
    _rb_define_module_function(module, "unmount", pathCacheUnmount);
    _rb_define_module_function(module, "reload", pathCacheReload);
    _rb_define_module_function(module, "desensitize", pathCacheDesensitize);
}