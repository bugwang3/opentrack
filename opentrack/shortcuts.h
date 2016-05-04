/* Copyright (c) 2014-2015, Stanislaw Halik <sthalik@misaki.pl>

 * Permission to use, copy, modify, and/or distribute this
 * software for any purpose with or without fee is hereby granted,
 * provided that the above copyright notice and this permission
 * notice appear in all copies.
 */

#pragma once
#include <QObject>
#include <tuple>
#include <vector>
#include <functional>

#ifdef BUILD_api
#   include "opentrack-compat/export.hpp"
#else
#   include "opentrack-compat/import.hpp"
#endif

#include "qxt-mini/QxtGlobalShortcut"
#include "opentrack-compat/options.hpp"
#include "opentrack/main-settings.hpp"

#ifdef _WIN32
#   include "keybinding-worker.hpp"
#endif

#ifdef __GNUC__
#   define unused(t, i) t __attribute__((unused)) i
#else
#   define unused(t, i) t i
#endif

using namespace options;

struct OPENTRACK_EXPORT Shortcuts : public QObject {
    Q_OBJECT

public:
    using K =
#ifndef _WIN32
    mem<QxtGlobalShortcut>
#else
    Key
#endif
    ;
    
    using fun = std::function<void(bool)>;
    using tt = std::tuple<K, fun, bool>;
    std::vector<tt> keys;
#ifdef _WIN32
    KeybindingWorker::Token key_token;
#endif

    Shortcuts()
#ifdef _WIN32
        : key_token([&](const Key& k) { receiver(k); })
#endif
    {}

    void reload(std::vector<std::tuple<key_opts&, fun, bool>> &keys_);
private:
    void bind_keyboard_shortcut(K &key, const key_opts& k, bool held);
#ifdef _WIN32
    void receiver(const Key& k);
#endif
};
