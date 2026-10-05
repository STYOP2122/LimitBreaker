# LimitBreaker

Экспериментальный ASI-плагин для SA-MP, который изменяет проверки ID моделей транспорта в клиенте. Дополнительные ID задаются в `vehicleModelPool` в исходном коде.

## Технологии

C++17, CMake, kthook, Xbyak, ktsignal и memwrapper.

## Сборка

Понадобятся Windows, Git, CMake 3.15+ и инструменты Visual Studio для C++. Зависимости загружаются через CMake FetchContent.

```bash
git clone https://github.com/STYOP2122/LimitBreaker.git
cd LimitBreaker
cmake -S . -B build -A Win32
cmake --build build --config Release
```

Для генератора Visual Studio результат — `build/Release/RemoveLimits.asi`.

## Настройка и совместимость

- Добавляемые ID моделей находятся в `src/main.cpp`.
- Хуки используют фиксированные смещения в `samp.dll`, поэтому совместимость зависит от конкретной версии клиента.
- В коде также заданы разрешённые адреса сервера и изменяется строка версии клиента. Перед использованием в другом проекте проверьте `InitializeConnectHook` и `ChangeSAMPVersion`.
- Для загрузки плагина требуется ASI Loader.

## Файлы

- `src/main.cpp` — установка хуков и настройка моделей.
- `src/main.hpp` — объявления плагина.
- `CMakeLists.txt` — сборка и зависимости.
